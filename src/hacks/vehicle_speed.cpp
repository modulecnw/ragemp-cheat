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

void VehicleSpeed::Tick()
{
	using namespace native;

	if (GetAsyncKeyState(VK_SHIFT)) {
		auto ped = player::player_ped_id();
		auto vehicle = ped::get_vehicle_ped_is_in(ped, false);

		controls::disable_control_action(0, 75, true);
		controls::disable_control_action(27, 75, true);

		if (vehicle) {
			if (GetAsyncKeyState(0x57)) {
				// world need to be fixed
				if (functions::get_local() != nullptr) {
					auto vehicle_ptr = functions::get_local()->VehicleManager;
					if (IsValidPtr(vehicle_ptr))
					{
						vehicle_ptr->fGravity++;
					}
				}
			}

			if (GetAsyncKeyState(0x53)) {
				vehicle::set_vehicle_forward_speed(vehicle, 0);
			}
		}
	}
}