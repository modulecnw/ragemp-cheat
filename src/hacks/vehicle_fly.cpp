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

float last_fly = 50;

void VehicleFly::Tick()
{
	using namespace native;

	if (GetAsyncKeyState(0x04)) {
		brain::clear_ped_tasks_immediately(native::player::player_ped_id());
	}

	if (GetAsyncKeyState(0x05)) {
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
				auto speed = (entity::get_entity_speed(vehicle) * 3.6);

				if (speed > 10) {
					last_fly = speed;
				}

				entity::set_entity_rotation(vehicle, rot.x, rot.y, rot.z, 1, true);

				if (speed < 10) vehicle::set_vehicle_forward_speed(vehicle, last_fly);
				entity::apply_force_to_entity(vehicle, 1, entity::get_entity_forward_x(vehicle), entity::get_entity_forward_y(vehicle), entity::get_entity_forward_vector(vehicle).z, 0, 0, 0, 1, 0, 1, 1, 1, 1);
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