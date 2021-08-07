#pragma once
#include "imports.hpp"

#define RAGEMP
using namespace std;

class Nemo : public Singleton<Nemo>
{
public:
    HMODULE hModule = nullptr;
    HWND hWindow = nullptr;
    Vector2 vScreen = Vector2(1920, 1080);
    string sProcessName = "RAGE Multiplayer";

    void Run(HMODULE hModule);
    void Shutdown();
};