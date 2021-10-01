#include "nemo.hpp"
#include "memory/memory.hpp"
#include "memory/patterns.hpp"
#include "hooks/hooks.hpp"
#include "hooks/renderer.hpp"
#include "handlers/key_handler.hpp"
#include <utils.hpp>

void Nemo::Run(HMODULE hModule)
{
	this->hModule = hModule;
	
	Patterns::Instance().Initialize();
	Memory::Instance().Initialize();
	Hooks::Instance().Initialize();
	
	KeyHandler::Instance().add_keybind(KeyHandler::key_binding(VK_BACK, [] {
		Log::Debug(_xor_("KeyHandler Test"));
	}, true));

	Log::Info(_xor_("nemo:V RAGEMP started."));
}


void Nemo::Shutdown()
{
	Log::Error(_xor_("nemo:V RAGEMP shutdown."));

	do {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	} while (!Renderer::Instance().bInitialized);

	MH_DisableHook(MH_ALL_HOOKS);
	MH_Uninitialize();

	Hooks::Instance().vthDirectHook->detach(8);
	Hooks::Instance().vthDirectHook->disable();

	SetWindowLongPtrW(this->hWindow, GWLP_WNDPROC, reinterpret_cast<long long>(this->wWndproc));
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}