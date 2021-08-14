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
		if (param_w == VK_BACK)
		{
			Gui::Instance().bMenuOpen ^= 1;
		}

		if (param_w == VK_NUMPAD9) Config::Instance().self.noclip = !Config::Instance().self.noclip;

		/* VEHICLE STEALER, need to be ported into hack module */
		if (param_w == VK_NUMPAD1) {
			tick::thread_invoker::queue([=]
				{
					auto ped = native::player::player_ped_id();
					auto coords = native::entity::get_entity_coords(ped, false);

					savedPos.x = coords.x;
					savedPos.y = coords.y;
					savedPos.z = coords.z;

					Log::Info(savedPos.x, savedPos.y, savedPos.z);
					auto vehicle = native::vehicle::get_closest_vehicle(coords.x, coords.y, coords.z, 200.0f, 0, 71);
					auto model = native::entity::get_entity_model(vehicle);
					auto model_name = native::vehicle::get_display_name_from_vehicle_model(model);

					Log::Info(model_name);
					if (native::vehicle::is_vehicle_seat_free(vehicle, -1))
					{
						native::ped::set_ped_into_vehicle(native::player::player_ped_id(), vehicle, -1);
					}
					else {
						native::ped::set_ped_into_vehicle(native::player::player_ped_id(), vehicle, 0);
						native::ped::_0xe6ca85e7259ce16b(native::player::player_ped_id());
						auto driver = native::vehicle::get_ped_in_vehicle_seat(vehicle, -1);
						native::ped::set_ped_can_be_knocked_off_vehicle(driver, 0);
						native::ped::knock_ped_off_vehicle(driver);
						native::entity::set_entity_coords_no_offset(driver, 0, 0, 0, false, false, false);
						native::ped::set_ped_into_vehicle(native::player::player_ped_id(), vehicle, -1);
					}

				}
			);
		}

		if (param_w == VK_NUMPAD2) {
			tick::thread_invoker::queue([=]
				{
					native::ped::set_ped_coords_keep_vehicle(native::player::player_ped_id(), 229.9559, -981.7928, -99.66071 + 0.4f);
					native::ped::set_ped_coords_keep_vehicle(native::player::player_ped_id(), 229.9559, -981.7928, -99.66071 + 0.4f);
					native::ped::set_ped_coords_keep_vehicle(native::player::player_ped_id(), 229.9559, -981.7928, -99.66071 + 0.4f);
					native::ped::set_ped_coords_keep_vehicle(native::player::player_ped_id(), 229.9559, -981.7928, -99.66071 + 0.4f);
					native::ped::set_ped_coords_keep_vehicle(native::player::player_ped_id(), 229.9559, -981.7928, -99.66071 + 0.4f);
					native::ped::set_ped_coords_keep_vehicle(native::player::player_ped_id(), 229.9559, -981.7928, -99.66071 + 0.4f);
					native::ped::set_ped_coords_keep_vehicle(native::player::player_ped_id(), 229.9559, -981.7928, -99.66071 + 0.4f);


					native::entity::set_entity_health(native::player::player_ped_id(), 200);
				}
			);
		}

		if (param_w == VK_NUMPAD3) {
			tick::thread_invoker::queue([=]
				{
					native::brain::clear_ped_tasks_immediately(native::player::player_ped_id());
				}
			);
		}

		if (param_w == VK_NUMPAD4) {
			tick::thread_invoker::queue([=]
				{
					native::ped::set_ped_coords_keep_vehicle(native::player::player_ped_id(), savedPos.x, savedPos.y, savedPos.z + 1.f);
				}
			);
		}

		if (param_w == VK_NUMPAD5) {
			tick::thread_invoker::queue([=]
				{
					native::ped::set_ped_coords_keep_vehicle(native::player::player_ped_id(), 0, 0, 72 + 1.f);
				}
			);
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