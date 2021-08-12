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
	auto vehicle = ped::get_vehicle_ped_is_in(ped, false);

	if (!vehicle) return;

	if (Config::Instance().vehicle.auto_repair)
		vehicle::set_vehicle_fixed(vehicle);
}