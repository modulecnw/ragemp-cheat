#include "hacks/vehicle_speed.hpp"
#include "hacks/replayinterface.hpp"

#include "gta/natives/database.hpp"

#include "memory/memory.hpp"
#include "utils.hpp"
#include "config.hpp"
#include "functions.hpp"

using namespace native;

std::string VehicleSpeed::getCategory()
{
	return std::string("Vehicle");
}

std::string VehicleSpeed::getName()
{
	return std::string("Speed");
}

inline float vehicleGravity = 0;
void VehicleSpeed::Tick()
{
	if (GetAsyncKeyState(VK_SHIFT)) {
		auto ped = player::player_ped_id();
		auto vehicle = ped::get_vehicle_ped_is_in(ped, false);

		auto cam = functions::get_cam_directions();

		controls::disable_control_action(0, 75, true);
		controls::disable_control_action(27, 75, true);

		if (vehicle) {
			vehicle::set_vehicle_fixed(vehicle);

			if (functions::get_local() == nullptr) return;

			auto vehicle_ptr = functions::get_local()->vehicle();
			if (!IsValidPtr(vehicle_ptr)) return;

			if (GetAsyncKeyState(0x57)) {
				float rotation = cam::get_gameplay_cam_rot(2).z;

				if ((entity::get_entity_speed(vehicle) * 3.6) < 280) {
					entity::apply_force_to_entity(vehicle, 1, cam.x, cam.y, cam.z, 0, 0, 0, 1, 0, 1, 1, 1, 1);
				}
				else {
					entity::apply_force_to_entity(vehicle, 0, cam.x, cam.y, cam.z, 0, 0, 0, 1, 0, 1, 1, 1, 1);
				}

				entity::set_entity_heading(vehicle, rotation);
			}

			if (GetAsyncKeyState(0x53)) {
				vehicle::set_vehicle_forward_speed(vehicle, 0);
			}

			vehicle_ptr->setGravity(60); // may add this to config
			vehicleGravity = 60;
		}
	}
	else {
		if (vehicleGravity != 9.800000191f) {
			if (functions::get_local() == nullptr) return;

			auto vehicle_ptr = functions::get_local()->vehicle();
			if (!IsValidPtr(vehicle_ptr)) return;

			vehicle_ptr->setGravity(9.800000191f);
			vehicleGravity = 9.800000191f;
		}
	}
}