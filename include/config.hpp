#pragma once
#include "imports.hpp"

using namespace std;

class Config : public Singleton<Config>
{
public:
	struct Self {
		bool noclip = false;
	} self;

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