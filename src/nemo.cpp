#include "nemo.hpp"
#include "memory/memory.hpp"
#include "memory/patterns.hpp"
#include "hooks/hooks.hpp"
#include <utils.hpp>

void Nemo::Run(HMODULE hModule)
{
	this->hModule = hModule;

	Patterns::Instance().Initialize();
	Memory::Instance().Initialize();
	Hooks::Instance().Initialize();

	Log::Info(_xor_("nemo:V RAGEMP started."));
}


void Nemo::Shutdown()
{
	MH_DisableHook(MH_ALL_HOOKS);
	MH_Uninitialize();
	
	Hooks::Instance().vthDirectHook->detach(8);
	Hooks::Instance().vthDirectHook->disable();

	SetWindowLongPtrW(this->hWindow, GWLP_WNDPROC, reinterpret_cast<long long>(this->wWndproc));

	Log::Error(_xor_("nemo:V RAGEMP shutdown."));
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}