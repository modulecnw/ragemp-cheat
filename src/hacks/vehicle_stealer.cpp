#include "hacks/vehicle_stealer.hpp"
#include "hacks/replayinterface.hpp"

#include "gta/natives/database.hpp"

#include "memory/memory.hpp"
#include "utils.hpp"
#include "config.hpp"
#include "functions.hpp"

std::string VehicleStealer::getCategory()
{
	return std::string("Vehicle");
}

std::string VehicleStealer::getName()
{
	return std::string("Stealer");
}
using namespace native;

void VehicleStealer::Tick()
{
	if (Config::Instance().vehicle.stealer) {
		if (Config::Instance().vehicle.want_steal) {
			auto res = functions::get_entity_by_raycast();
			if (entity::is_entity_a_vehicle(res)) {
				auto model = entity::get_entity_model(res);
				auto model_name = vehicle::get_display_name_from_vehicle_model(model);
				auto veh_pos = native::entity::get_entity_coords(res, false);

				Config::Instance().vehicle.request_stealed_vehicle = { model_name, Vector3(veh_pos.x, veh_pos.y, veh_pos.z) };

				if (GetAsyncKeyState(VK_XBUTTON2) & 0x8000) {
					Config::Instance().vehicle.request_stealed_vehicle = { 0, Vector3() };

					auto ped = native::player::player_ped_id(); 
					auto coords = native::entity::get_entity_coords(ped, false);
					native::entity::set_entity_health(native::player::player_ped_id(), 200);

					if (native::vehicle::is_vehicle_seat_free(res, -1))
					{
						native::ped::set_ped_into_vehicle(native::player::player_ped_id(), res, -1);
					}
					else {
						native::ped::set_ped_into_vehicle(native::player::player_ped_id(), res, 0);
						native::ped::_0xe6ca85e7259ce16b(native::player::player_ped_id());

						auto driver = native::vehicle::get_ped_in_vehicle_seat(res, -1);
						native::ped::set_ped_can_be_knocked_off_vehicle(driver, 0);
						native::ped::knock_ped_off_vehicle(driver);
						native::entity::set_entity_coords_no_offset(driver, 0, 0, 0, false, false, false);

						native::ped::set_ped_into_vehicle(native::player::player_ped_id(), res, -1);
					}
				}
			}
		}
	}
}