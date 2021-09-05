#include "hacks/vehicle_options.hpp"
#include "hacks/replayinterface.hpp"

#include "gta/natives/database.hpp"

#include "memory/memory.hpp"
#include "utils.hpp"
#include "config.hpp"
#include "functions.hpp"

std::string VehicleOptions::getCategory()
{
	return std::string("Vehicle");
}

std::string VehicleOptions::getName()
{
	return std::string("Options");
}

void VehicleOptions::Tick()
{
	using namespace native;

	auto ped = player::player_ped_id();

	/* anti death gvmp */
	if (graphics::animpostfx_is_running("DeathFailOut")) {
		brain::clear_ped_tasks_immediately(player::player_ped_id());
		controls::enable_control_action(0, 31, true);
		controls::enable_control_action(0, 30, true);

		controls::enable_control_action(0, 22, true);
		controls::enable_control_action(0, 23, true);
		controls::enable_control_action(0, 25, true);
		controls::enable_control_action(0, 44, true);
		controls::enable_control_action(0, 75, true);
		controls::enable_control_action(0, 140, true);
		controls::enable_control_action(0, 141, true);
		entity::freeze_entity_position(ped, false);

		controls::enable_all_control_actions(0);

		graphics::animpostfx_stop("DeathFailOut");
	}


	auto vehicle = ped::get_vehicle_ped_is_in(ped, false);

	if (!vehicle) return;

	if (Config::Instance().vehicle.auto_repair)
		vehicle::set_vehicle_fixed(vehicle);
}