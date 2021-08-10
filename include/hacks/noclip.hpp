#pragma once
#include "imports.hpp"
#include "hack.hpp"

using namespace std;

class Noclip : public Singleton<Noclip>, Hack
{
public:
    void Tick();

    // Geerbt über Hack
    virtual std::string getCategory() override;
    virtual std::string getName() override;
};