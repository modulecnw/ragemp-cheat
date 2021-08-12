#include "hacks/vehicle_speed.hpp"
#include "hacks/replayinterface.hpp"

#include "gta/natives/database.hpp"

#include "memory/memory.hpp"
#include "utils.hpp"
#include "config.hpp"
#include "functions.hpp"

std::string VehicleSpeed::getCategory()
{
	return std::string("Vehicle");
}

std::string VehicleSpeed::getName()
{
	return std::string("Speed");
}

float last_speed = 50;

void VehicleSpeed::Tick()
{
	if (!Config::Instance().vehicle.speed.enabled) return;

	using namespace native;

	if (GetAsyncKeyState(VK_SHIFT)) {
		auto ped = player::player_ped_id();
		auto vehicle = ped::get_vehicle_ped_is_in(ped, false);

		auto cam = functions::get_cam_directions();

		controls::disable_control_action(0, 75, true);
		controls::disable_control_action(27, 75, true);

		if (vehicle) {

			vehicle::set_vehicle_fixed(vehicle); // for testings

			if (functions::get_local() == nullptr) return;

			auto vehicle_ptr = functions::get_local()->vehicle();
			if (!IsValidPtr(vehicle_ptr)) return;

			if (GetAsyncKeyState(0x57)) {
				auto rot = cam::get_gameplay_cam_rot(1);
				auto pos = entity::get_entity_coords(vehicle, true);
				auto speed = (entity::get_entity_speed(vehicle) * 3.6);

				if (speed > 10) {
					last_speed = speed;
				}

				if (Config::Instance().vehicle.speed.set_rotation)
					entity::set_entity_rotation(vehicle, rot.x, rot.y, rot.z, 1, true);

				if (Config::Instance().vehicle.speed.only_ground)
				{
					float z = 0.0f;

					if (gameplay::get_ground_z_for_3d_coord(pos.x, pos.y, pos.z, &z, false)) {
						entity::set_entity_coords_no_offset(vehicle, pos.x, pos.y, z, false, false, false);
					}
				}


				if (speed < 1) vehicle::set_vehicle_forward_speed(vehicle, last_speed);
					entity::apply_force_to_entity(vehicle, 1, cam.x, cam.y, cam.z, 0, 0, 0, 1, 0, 1, 1, 1, 1);
			}

			if (GetAsyncKeyState(VK_SPACE)) {
				entity::apply_force_to_entity(vehicle, 1, 0 + entity::get_entity_forward_x(vehicle), 0 + entity::get_entity_forward_y(vehicle), 7, 0, 0, 0, 1, 0, 1, 1, 1, 1);
			}

			if (GetAsyncKeyState(0x53)) {
				vehicle::set_vehicle_forward_speed(vehicle, 0);
			}
		}
	}
}