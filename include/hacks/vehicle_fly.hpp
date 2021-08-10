#pragma once
#include "imports.hpp"
#include "hack.hpp"

using namespace std;

class VehicleFly : public Singleton<VehicleFly>, Hack
{
public:
    void Tick();

    // Geerbt über Hack
    virtual std::string getCategory() override;
    virtual std::string getName() override;
};