#include "hooks/hooks.hpp"
#include "hooks/renderer.hpp"
#include "hooks/thread.hpp"
#include "gui/gui.hpp"

// needs rework
HRESULT call_renderer_hook(IDXGISwapChain* this_swapchain_pointer, unsigned int sync_interval, unsigned int flags)
{
	Renderer::Instance().Render(this_swapchain_pointer, sync_interval, flags);
	return Hooks::Instance().vthDirectHook->fetch(call_renderer_hook, 8)(this_swapchain_pointer, sync_interval, flags);
}

uintptr_t hooked_native_thread(game_thread* this_ptr, int ops_to_execute) {
	Thread::Instance().Call(this_ptr, ops_to_execute);
	return Hooks::Instance().original_native_thread(this_ptr, ops_to_execute);
}


void Hooks::Render() {
	this->vthDirectHook = std::make_unique<hooks::virtual_table_hook>(_xor_("Swapchain").c_str(), Memory::Instance().ptr_gta_swapchain, 0x12);
	this->vthDirectHook->attach(8, call_renderer_hook);
	this->vthDirectHook->enable();

	Gui::Instance().bMenuOpen = true;
}

void Hooks::Thread() {
	int ingame_inject = true;

	while (*Memory::Instance().ptr_gta_game_state != game_state_t::playing) ingame_inject = false;

	if (!ingame_inject)
		std::this_thread::sleep_for(std::chrono::milliseconds(10000));

	Memory::Instance().InitializeIngame();

	std::this_thread::sleep_for(std::chrono::milliseconds(5000));

	MH_Initialize();

	MH_CreateHook(Memory::Instance().ptr_gta_script_thread_tick, hooked_native_thread, reinterpret_cast<void**>(&Hooks::Instance().original_native_thread));
	if (MH_EnableHook(Memory::Instance().ptr_gta_script_thread_tick) == MH_OK) {
		Log::Debug(_xor_("[+] Hooks >>"), _xor_("Game-Thread"), _xor_("enabled."));
	}

	this->MH_Initialized = true;
}

void Hooks::Initialize() {
	Log::Warning("[+] Hooks >> Initializing hooks...");

	this->Render();
	this->Thread();
}