#pragma once
#include "imports.hpp"
#include "hack.hpp"

using namespace std;

class VehicleOptions : public Singleton<VehicleOptions>, Hack
{
public:
    void Tick();

    // Geerbt �ber Hack
    virtual std::string getCategory() override;
    virtual std::string getName() override;
};