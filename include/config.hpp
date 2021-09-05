#pragma once
#include "imports.hpp"

using namespace std;

class Config : public Singleton<Config>
{
private:
	struct StealedVehicle {
		const char* stealed_vehicle = "";
		Vector3 stealed_pos = Vector3(0, 0, 0);
	};

	struct RequestStealedVehicle {
		const char* stealed_vehicle = "";
		Vector3 stealed_pos = Vector3(0, 0, 0);
	};
public:
	struct Self {
		bool noclip = false;
	} self;

	struct Vehicle {
		bool auto_repair = false;
		bool stealer = false;

		bool want_steal = false;
		StealedVehicle stealed_vehicle = { 0, Vector3() };
		RequestStealedVehicle request_stealed_vehicle = { 0, Vector3() };

		struct Speed {
			bool enabled = false;
			bool set_rotation = false;
			bool only_ground = false;
		} speed;

		struct Fly {
			bool enabled = false;
			bool set_rotation = false;
		} fly;
	} vehicle;

	struct Aimings {
		struct Aimbot {
			bool enabled = false;
			bool showFOV = false;

			int boneId = 0;
			int aim_key = 0;
			float fov = 90.0f;
		} aimbot;
	} aiming;

	struct Visuals {
		struct Players {
			bool enabled = true;
			bool name = false;
			bool skeleton = false;

			struct Skeletons {
				bool HEAD = true;
				bool NECK = true;
				bool RIGHT_HAND = true;
				bool RIGHT_FOREARM = true;
				bool RIGHT_UPPER_ARM = true;
				bool RIGHT_CLAVICLE = true;
				bool LEFT_HAND = true;
				bool LEFT_FOREARM = true;
				bool LEFT_UPPER_ARM = true;
				bool LEFT_CLAVICLE = true;
				bool PELVIS = true;
				bool SPINE_ROOT = true;
				bool SPINE0 = true;
				bool SPINE1 = true;
				bool SPINE2 = true;
				bool SPINE3 = true;
				bool RIGHT_TOE = true;
				bool RIGHT_FOOT = true;
				bool RIGHT_CALF = true;
				bool RIGHT_THIGH = true;
				bool LEFT_TOE = true;
				bool LEFT_FOOT = true;
				bool LEFT_CALF = true;
				bool LEFT_THIGH = true;
			} active_skeletons;
		} player;
	} visuals;
};