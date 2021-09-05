#include "hacks/noclip.hpp"
#include "hacks/replayinterface.hpp"

#include "gta/natives/database.hpp"

#include "memory/memory.hpp"
#include "utils.hpp"
#include "config.hpp"
#include "functions.hpp"

std::string Noclip::getCategory()
{
	return std::string("Self");
}

std::string Noclip::getName()
{
	return std::string("Noclip");
}

void Noclip::Tick()
{
	if (!Config::Instance().self.noclip) return;

	using namespace native;

	int noclip_speed = 1;

	bool is_in_vehicle = ped::is_ped_in_any_vehicle(player::player_ped_id(), false);
	type::any entity;
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	auto pos = Memory::Instance().ptr_gta_world_factory->world->pLocalPlayer->fPosition;

	if (!is_in_vehicle) {
		entity = player::get_player_ped(-1);
		x = pos.x;
		y = pos.y;
		z = pos.z;
	}
	else
	{
		entity = ped::get_vehicle_ped_is_in(player::get_player_ped(-1), false);
		x = pos.x;
		y = pos.y;
		z = pos.z;
	}

	auto cam_direction = functions::get_cam_directions();

	float dx = cam_direction.x;
	float dy = cam_direction.y;
	float dz = cam_direction.z;

	if (GetAsyncKeyState(VK_LSHIFT))
		noclip_speed = 3;

	if (!GetAsyncKeyState(VK_LSHIFT))
		noclip_speed = 1;

	if (noclip_speed == NULL) noclip_speed = 1;

	if (GetAsyncKeyState(0x57))
	{
		x = x + noclip_speed * dx;
		y = y + noclip_speed * dy;
		z = z + noclip_speed * dz;
	}

	if (GetAsyncKeyState(0x53))
	{
		x = x - noclip_speed * dx;
		y = y - noclip_speed * dy;
		z = z - noclip_speed * dz;
	}

	if (GetAsyncKeyState(VK_SPACE))
		z = z + noclip_speed;

	entity::set_entity_coords_no_offset(entity, x, y, z, true, true, true);
}