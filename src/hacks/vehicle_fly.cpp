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

void VehicleFly::Tick()
{
	//soon
}