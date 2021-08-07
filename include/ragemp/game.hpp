#pragma once
#include "gta/game.hpp"

class CPedLink
{
public:
    char pad_0x0000[0x18]; //0x0000
    CObject* pPed; //0x0018 
    char pad_0x0020[0x28]; //0x0020
}; //Size=0x0048

class CRemotePlayer
{
public:
    char pad_0x0000[0x8]; //0x0000
    __int16 iHandle; //0x0008 
    char pad_0x000C[0x7C]; //0x000C
    CPedLink* pPedLink; //0x0088 
    char pad_0x0090[0x378]; //0x0090

}; //Size=0x0408

class CRagePlayerPool
{
public:
    CRemotePlayer* N0000000B; //0x0000 
    char pad_0x0008[0x10]; //0x0008
}; //Size=0x0018


class CRagePool
{
public:
    CRagePlayerPool* PlayerPool; //0x0000 
    char pad_0x0008[0x38]; //0x0008
}; //Size=0x0040
