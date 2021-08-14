#include "hooks/hooks.hpp"
#include "hooks/renderer.hpp"
#include "hooks/thread.hpp"
#include "gui/gui.hpp"
#include "gta/fiber.hpp"

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
}

void Hooks::Thread() {
	Fiber::Instance().Call();

	MH_CreateHook(Memory::Instance().ptr_gta_script_thread_tick, hooked_native_thread, reinterpret_cast<void**>(&Hooks::Instance().original_native_thread));
	if (MH_EnableHook(Memory::Instance().ptr_gta_script_thread_tick) == MH_OK) {
		Log::Debug(_xor_("[+] Hooks >>"), _xor_("Game-Thread"), _xor_("enabled."));
	}
}

void Hooks::Initialize() {
	Log::Warning("[+] Hooks >> Initializing hooks...");

	do {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		Log::Warning("[+] Hooks >> Waiting for game...");
	} while (*Memory::Instance().ptr_gta_game_state != game_state_t::playing);

	MH_Initialize();

	this->Render();
	this->Thread();
}