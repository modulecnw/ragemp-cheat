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

			vehicle::set_vehicle_fixed(vehicle); // for testings

			if (functions::get_local() == nullptr) return;

			auto vehicle_ptr = functions::get_local()->vehicle();
			if (!IsValidPtr(vehicle_ptr)) return;

			Log::Debug("Gravity: ", vehicle_ptr->fGravity);
			Log::Debug("fAcceleration: ", vehicle_ptr->handling()->fAcceleration);
			Log::Debug("fDriveInertia: ", vehicle_ptr->handling()->fDriveInertia);
			Log::Debug("fMass: ", vehicle_ptr->handling()->fMass);

			if (GetAsyncKeyState(0x57)) {
				//not ready now
			}

			if (GetAsyncKeyState(0x53)) {
				vehicle::set_vehicle_forward_speed(vehicle, 0);
			}
		}
	}
}