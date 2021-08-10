#pragma once
#include "imports.hpp"
#include "hack.hpp"
#include "memory/memory.hpp"

using namespace std;

class Replayinterface : public Singleton<Replayinterface>, Hack
{
public:
    struct NPed {
        CRemotePlayer* player;
        CObject* ped;
        CPlayerBones bones;
    };
    NPed peds[256];

    unsigned int local_player;

    void Tick();

    // Geerbt über Hack
    virtual std::string getCategory() override;
    virtual std::string getName() override;
};