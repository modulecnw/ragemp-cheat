#include "imports.hpp"
#include "nemo.hpp"

HMODULE g_hModule = nullptr;
DWORD WINAPI startThread(LPVOID lParameter)
{
	Log::Push(new Log::ConsoleStream());
	Nemo::Instance().Run(g_hModule);

	while (true)
	{
		if (GetAsyncKeyState(VK_PRIOR) & 0x8000)
			break;

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		std::this_thread::yield();
	}

	Nemo::Instance().Shutdown();

	fclose(stdin);
	fclose(stdout);

	FreeConsole();

	FreeLibraryAndExitThread(g_hModule, 0);

	return TRUE;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) {

		g_hModule = hModule;
		AllocConsole();

		SetConsoleTitleA("NEMO | Developer-Output Console");

		freopen_s((FILE**)stdin, "conin$", "r", stdin);
		freopen_s((FILE**)stdout, "conout$", "w", stdout);

		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)startThread, nullptr, 0, nullptr);
	}

	return TRUE;
}