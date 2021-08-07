#include "nemo.hpp"
#include "memory/memory.hpp"
#include "memory/patterns.hpp"
#include "hooks/hooks.hpp"
#include <utils.hpp>

void Nemo::Run(HMODULE hModule)
{
	this->hModule = hModule;
	this->hWindow = utils::find_main_window(GetCurrentProcessId());

	Patterns::Instance().Initialize();
	Memory::Instance().Initialize();
	Hooks::Instance().Initialize();

	Log::Info(_xor_("nemo:V RAGEMP started."));
}


void Nemo::Shutdown()
{
	Log::Error(_xor_("nemo:V RAGEMP shutdown."));
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}