#include "hacks/vehicle_fly.hpp"
#include "hacks/replayinterface.hpp"

#include "gta/natives/database.hpp"

#include "memory/memory.hpp"
#include "utils.hpp"
#include "config.hpp"
#include "functions.hpp"

std::string VehicleFly::getCategory()
{
	return std::string("Vehicle");
}

std::string VehicleFly::getName()
{
	return std::string("Fly");
}

using namespace native;

inline float vehicleGravity = 0;
void VehicleFly::Tick()
{
	if (true) { // config

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
				entity::apply_force_to_entity(vehicle, 1, cam.x, cam.y, cam.z, 0, 0, 0, 1, 1, 1, 1, 1, 1);

				entity::set_entity_heading(vehicle, cam::get_gameplay_cam_rot(2).z);
			}

			if (GetAsyncKeyState(0x53)) {
				vehicle::set_vehicle_forward_speed(vehicle, 0);
			}

			if (GetAsyncKeyState(VK_SPACE)) {
				entity::apply_force_to_entity(vehicle, 1, cam.x, cam.y, cam.z + 10, 0, 0, 0, 1, 1, 1, 1, 1, 1);
			}

			if (GetAsyncKeyState(VK_SHIFT)) {
				entity::apply_force_to_entity(vehicle, 1, cam.x, cam.y, cam.z - 10, 0, 0, 0, 1, 1, 1, 1, 1, 1);
			}

			// didnt tested it, maybe force values wrong lel

			vehicle_ptr->setGravity(-0.5);
			vehicleGravity = -0.5;
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