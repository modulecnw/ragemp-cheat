#pragma once
#include "imports.hpp"

#define RAGEMP
using namespace std;

class Nemo : public Singleton<Nemo>
{
public:
    HMODULE hModule = nullptr;
    string sProcessName = "RAGE Multiplayer";


    void Run(HMODULE hModule);
    void Shutdown();
};