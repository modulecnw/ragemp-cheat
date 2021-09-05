#include "hooks/wndproc.hpp"
#include "gta/natives/database.hpp"
#include <queue>
#include "gta/tick.hpp"
#include "config.hpp"

Vector3 savedPos = Vector3(0, 0, 0);
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT Wndproc::call_wndproc(HWND hwnd, unsigned int message_u, WPARAM param_w, LPARAM param_l)
{
	if (message_u == WM_KEYUP)
	{
		if (param_w == VK_F9)
		{
			Gui::Instance().bMenuOpen ^= 1;
		}

		if (param_w == VK_NUMPAD9) Config::Instance().self.noclip = !Config::Instance().self.noclip;

		/* VEHICLE STEALER, need to be ported into hack module */
		if (param_w == VK_NUMPAD1) {
			if (Config::Instance().vehicle.stealer) Config::Instance().vehicle.want_steal = !Config::Instance().vehicle.want_steal;
		}
	}

	if (ImGui::GetIO().MouseDrawCursor)
	{
		if (ImGui_ImplWin32_WndProcHandler(hwnd, message_u, param_w, param_l))
			return true;

		return 1l;
	}

	return CallWindowProc(Nemo::Instance().wWndproc, hwnd, message_u, param_w, param_l);
}