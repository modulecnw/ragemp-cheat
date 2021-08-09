#pragma once
#include "imports.hpp"
#include "memory/memory.hpp"
#include "ragemp/ragemp_shift.hpp"
#include <utils.hpp>

namespace functions {
	inline bool world_to_screen(Vector3 pos, ImVec2* out) {
		Vector3	tmp;

		tmp.x = (Memory::Instance().ptr_gta_viewport->fViewMatrix[1] * pos.x) + (Memory::Instance().ptr_gta_viewport->fViewMatrix[5] * pos.y) + (Memory::Instance().ptr_gta_viewport->fViewMatrix[9] * pos.z) + Memory::Instance().ptr_gta_viewport->fViewMatrix[13];
		tmp.y = (Memory::Instance().ptr_gta_viewport->fViewMatrix[2] * pos.x) + (Memory::Instance().ptr_gta_viewport->fViewMatrix[6] * pos.y) + (Memory::Instance().ptr_gta_viewport->fViewMatrix[10] * pos.z) + Memory::Instance().ptr_gta_viewport->fViewMatrix[14];
		tmp.z = (Memory::Instance().ptr_gta_viewport->fViewMatrix[3] * pos.x) + (Memory::Instance().ptr_gta_viewport->fViewMatrix[7] * pos.y) + (Memory::Instance().ptr_gta_viewport->fViewMatrix[11] * pos.z) + Memory::Instance().ptr_gta_viewport->fViewMatrix[15];

		if (tmp.z < 0.001f)
			return false;

		tmp.z = 1.0f / tmp.z;

		tmp.x *= tmp.z;
		tmp.y *= tmp.z;

		int w = ImGui::GetIO().DisplaySize.x;
		int h = ImGui::GetIO().DisplaySize.y;

		out->x = ((w / 2.f) + (.5f * tmp.x * w + 1.f));
		out->y = ((h / 2.f) - (.5f * tmp.y * h + 1.f));

		return true;
	}

	inline Vector2 world_to_screen_vec(Vector3 vWorldPos)
	{
		Vector2 pos = Vector2{ 0, 0 };
		if (Memory::Instance().ptr_gta_world_to_screen)
		{
			if (Memory::Instance().ptr_gta_world_to_screen(&vWorldPos, &pos.x, &pos.y))
			{
				pos.x = pos.x * ImGui::GetIO().DisplaySize.x;
				pos.y = pos.y * ImGui::GetIO().DisplaySize.y;
				return pos;
			}
		}
		return Vector2{ 0, 0 };
	}

	inline CObject* get_local() {
		CWorld* world = Memory::Instance().ptr_gta_world;
		return world->getLocalPlayer();
	}

	inline Vector3 get_bone_position(CObject* ped, int32_t bone)
	{
		__m128 result;
		reinterpret_cast<void* (__fastcall*)(CObject*, __m128*, int32_t)>(Memory::Instance().ptr_gta_get_bone_position)(ped, &result, bone);

		return Vector3::FromM128(result);
	}

	inline float get_distance(Vector3 to, Vector3 from) {
		return (sqrt(
			((to.x - from.x) * (to.x - from.x)) +
			((to.y - from.y) * (to.y - from.y)) +
			((to.z - from.z) * (to.z - from.z))
		));
	}

	inline float screen_distance(float Xx, float Yy, float xX, float yY)
	{
		return sqrt((yY - Yy) * (yY - Yy) + (xX - Xx) * (xX - Xx));
	}

	inline std::string get_name_from_index(WORD i)
	{
		if (i < std::size(ragemp::ragemp_player_shift)) {
			auto id = ~__ROR2__(i + ((0x0 - 0x198) & 0x3FF), 8);
			return *reinterpret_cast<std::string*>(Memory::Instance().ptr_rage037_get_rage_name(Memory::Instance().ptr_rage037_get_name_verify(), ragemp::ragemp_player_shift[(WORD)id]));
		}

		return "Not found";
	}
}