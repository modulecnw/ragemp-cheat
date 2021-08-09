#pragma once
#include "imports.hpp"
#include "hack.hpp"

using namespace std;

class VisualsPlayer : public Singleton<VisualsPlayer>, Hack
{
public:
    struct vector3_active_assignment {
        Vector3 pos;
        bool active;
    };

    void Tick();

    // Geerbt über Hack
    virtual std::string getCategory() override;
    virtual std::string getName() override;
};