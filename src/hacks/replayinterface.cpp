#include "functions.hpp"

#include "gta/natives/database.hpp"

#include "hacks/replayinterface.hpp"

std::string Replayinterface::getCategory()
{
	return std::string("System");
}

std::string Replayinterface::getName()
{
	return std::string("Replayinterface");
}

const int MAX_PLAYERS = 255;
const int MAX_VEHICLES = 255;
const int MAX_OBJECTS = 255;

void Replayinterface::Tick()
{
	if (Memory::Instance().multiplayer_framework == MultiplayerFrameworks::RAGEMP_037) {
		// get called in fiber
		/* players*/
		for (int i = 0; i < MAX_PLAYERS; i++) {
			this->peds[i].player = nullptr;
			this->peds[i].ped = nullptr;

			auto* pRemotePlayer = *reinterpret_cast<CRemotePlayer**>((DWORD64)Memory::Instance().ptr_rage037_pool + (i * 0x8));
			if (pRemotePlayer == NULL) continue;

			if (!IsValidPtr(pRemotePlayer) || !IsValidPtr(pRemotePlayer->pPedLink) || !IsValidPtr(pRemotePlayer->pPedLink->pPed)) continue;

			CObject* ped = pRemotePlayer->pPedLink->pPed;
			if (ped == NULL || !IsValidPtr(ped)) continue;

			this->peds[i].player = pRemotePlayer;
			this->peds[i].ped = ped;

			peds[i].bones.HEAD = functions::get_bone_position(ped, HEAD);
			peds[i].bones.NECK = functions::get_bone_position(ped, NECK);

			peds[i].bones.RIGHT_HAND = functions::get_bone_position(ped, RIGHT_HAND);
			peds[i].bones.RIGHT_FOREARM = functions::get_bone_position(ped, RIGHT_FOREARM);
			peds[i].bones.RIGHT_UPPER_ARM = functions::get_bone_position(ped, RIGHT_UPPER_ARM);
			peds[i].bones.RIGHT_CLAVICLE = functions::get_bone_position(ped, RIGHT_CLAVICLE);

			peds[i].bones.LEFT_HAND = functions::get_bone_position(ped, LEFT_HAND);
			peds[i].bones.LEFT_FOREARM = functions::get_bone_position(ped, LEFT_FOREARM);
			peds[i].bones.LEFT_UPPER_ARM = functions::get_bone_position(ped, LEFT_UPPER_ARM);
			peds[i].bones.LEFT_CLAVICLE = functions::get_bone_position(ped, LEFT_CLAVICLE);

			peds[i].bones.PELVIS = functions::get_bone_position(ped, PELVIS);
			peds[i].bones.SPINE_ROOT = functions::get_bone_position(ped, SPINE_ROOT);
			peds[i].bones.SPINE0 = functions::get_bone_position(ped, SPINE0);
			peds[i].bones.SPINE1 = functions::get_bone_position(ped, SPINE1);
			peds[i].bones.SPINE2 = functions::get_bone_position(ped, SPINE2);
			peds[i].bones.SPINE3 = functions::get_bone_position(ped, SPINE3);

			peds[i].bones.RIGHT_TOE = functions::get_bone_position(ped, RIGHT_TOE);
			peds[i].bones.RIGHT_FOOT = functions::get_bone_position(ped, RIGHT_FOOT);
			peds[i].bones.RIGHT_CALF = functions::get_bone_position(ped, RIGHT_CALF);
			peds[i].bones.RIGHT_THIGH = functions::get_bone_position(ped, RIGHT_THIGH);

			peds[i].bones.LEFT_TOE = functions::get_bone_position(ped, LEFT_TOE);
			peds[i].bones.LEFT_FOOT = functions::get_bone_position(ped, LEFT_FOOT);
			peds[i].bones.LEFT_CALF = functions::get_bone_position(ped, LEFT_CALF);
			peds[i].bones.LEFT_THIGH = functions::get_bone_position(ped, LEFT_THIGH);
		}
	}
	else {
		for (int i = 0; i < Memory::Instance().ptr_gta_replay_interface->ped_interface->max_peds; i++) {
			this->peds[i].player = nullptr;
			this->peds[i].ped = nullptr;

			auto pRemotePed = Memory::Instance().ptr_gta_replay_interface->ped_interface->get_ped(i);
			if (pRemotePed == NULL || !IsValidPtr(pRemotePed)) continue;

			this->peds[i].ped = pRemotePed;

			peds[i].bones.HEAD = functions::get_bone_position(pRemotePed, HEAD);
			peds[i].bones.NECK = functions::get_bone_position(pRemotePed, NECK);

			peds[i].bones.RIGHT_HAND = functions::get_bone_position(pRemotePed, RIGHT_HAND);
			peds[i].bones.RIGHT_FOREARM = functions::get_bone_position(pRemotePed, RIGHT_FOREARM);
			peds[i].bones.RIGHT_UPPER_ARM = functions::get_bone_position(pRemotePed, RIGHT_UPPER_ARM);
			peds[i].bones.RIGHT_CLAVICLE = functions::get_bone_position(pRemotePed, RIGHT_CLAVICLE);

			peds[i].bones.LEFT_HAND = functions::get_bone_position(pRemotePed, LEFT_HAND);
			peds[i].bones.LEFT_FOREARM = functions::get_bone_position(pRemotePed, LEFT_FOREARM);
			peds[i].bones.LEFT_UPPER_ARM = functions::get_bone_position(pRemotePed, LEFT_UPPER_ARM);
			peds[i].bones.LEFT_CLAVICLE = functions::get_bone_position(pRemotePed, LEFT_CLAVICLE);

			peds[i].bones.PELVIS = functions::get_bone_position(pRemotePed, PELVIS);
			peds[i].bones.SPINE_ROOT = functions::get_bone_position(pRemotePed, SPINE_ROOT);
			peds[i].bones.SPINE0 = functions::get_bone_position(pRemotePed, SPINE0);
			peds[i].bones.SPINE1 = functions::get_bone_position(pRemotePed, SPINE1);
			peds[i].bones.SPINE2 = functions::get_bone_position(pRemotePed, SPINE2);
			peds[i].bones.SPINE3 = functions::get_bone_position(pRemotePed, SPINE3);

			peds[i].bones.RIGHT_TOE = functions::get_bone_position(pRemotePed, RIGHT_TOE);
			peds[i].bones.RIGHT_FOOT = functions::get_bone_position(pRemotePed, RIGHT_FOOT);
			peds[i].bones.RIGHT_CALF = functions::get_bone_position(pRemotePed, RIGHT_CALF);
			peds[i].bones.RIGHT_THIGH = functions::get_bone_position(pRemotePed, RIGHT_THIGH);

			peds[i].bones.LEFT_TOE = functions::get_bone_position(pRemotePed, LEFT_TOE);
			peds[i].bones.LEFT_FOOT = functions::get_bone_position(pRemotePed, LEFT_FOOT);
			peds[i].bones.LEFT_CALF = functions::get_bone_position(pRemotePed, LEFT_CALF);
			peds[i].bones.LEFT_THIGH = functions::get_bone_position(pRemotePed, LEFT_THIGH);
		}
	}
}