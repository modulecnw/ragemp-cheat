#pragma once
#include "imports.hpp"

using namespace std;

class Config : public Singleton<Config>
{
public:
    struct Visuals {
        struct Players {
            bool enabled = false;
            bool name = false;
        } player;
    } visuals;
};