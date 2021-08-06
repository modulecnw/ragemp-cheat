#include "nemo.hpp"
#include "memory/memory.hpp"

void Nemo::Run(HMODULE hModule)
{
	this->hModule = hModule;
	Memory::Instance().Initialize();

	Log::Info("nemo:V RAGEMP started.");
}


void Nemo::Shutdown()
{
	Log::Info("nemo:V RAGEMP shutdown.");
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}