#pragma once
#include <Windows.h>
#include <stdio.h> 
#include <string> 
#include <sstream> 
#include <iostream>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */


#include <dwmapi.h> 
#include <TlHelp32.h>
#include <xmmintrin.h>

#define IsValidPtr(x) (x && !IsBadReadPtr(&x, sizeof(void*) && x != nullptr && x > nullptr))

using Vehicle = unsigned int;
using Hash = unsigned int;
using Cam = unsigned int;


enum class MultiplayerFrameworks {
	RAGEMP_037,
	RAGEMP_11
};

enum Bones {
	HEAD = 0x796E,
	NECK = 0x9995,
	RIGHT_HAND = 0xDEAD,
	RIGHT_FOREARM = 0x6E5C,
	RIGHT_UPPER_ARM = 0x9D4D,
	RIGHT_CLAVICLE = 0x29D2,

	LEFT_HAND = 0x49D9,
	LEFT_FOREARM = 0xEEEB,
	LEFT_UPPER_ARM = 0xB1C5,
	LEFT_CLAVICLE = 0xFCD9,

	PELVIS = 0x2E28,
	SPINE_ROOT = 0xE0FD,
	SPINE0 = 0x60F2,
	SPINE1 = 0x60F0,
	SPINE2 = 0x60F1,
	SPINE3 = 0x60F2,

	RIGHT_TOE = 0x512D,
	RIGHT_FOOT = 0xCC4D,
	RIGHT_CALF = 0x9000,
	RIGHT_THIGH = 0xCA72,
	LEFT_TOE = 0x083C,
	LEFT_FOOT = 0x3779,
	LEFT_CALF = 0xF9BB,
	LEFT_THIGH = 0xE39F
};


//=======================================
class CObject;
class CVehicle;
//=======================================

struct PVector3
{
	public:
		PVector3() = default;

		PVector3(float x, float y, float z) :
			x(x), y(y), z(z)
		{}
	public:
		float x{};
	private:
		char m_padding1[0x04]{};
	public:
		float y{};
	private:
		char m_padding2[0x04]{};
	public:
		float z{};
	private:
		char m_padding3[0x04]{};
};

struct Vector3
{
	float x;
	float y;
	float z;

	Vector3() {}
	Vector3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}
	static Vector3 FromM128(__m128 in) { return Vector3(in.m128_f32[0], in.m128_f32[1], in.m128_f32[2]); }
	inline Vector3 operator+(Vector3 in) const
	{
		return Vector3(
			x + in.x,
			y + in.y,
			z + in.z
		);
	}


};

struct Vector2
{
	float x;
	float y;

	Vector2() {}
	Vector2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
};

struct Vector4
{
	float x;
	float y;
	float z;
	float w;

	Vector4() {}
	Vector4(float _x, float _y, float _z, float _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

};

class CPlayerCameraData {
public:
	char _0x0000[48];
	float Fov_Zoom; //0x0030 
	char _0x0034[36];
	__int32 m_ZoomState; //0x0058 1 = Normal, 0 = Zoom, 10000+ = FPS

};//Size=0x0548

class CPlayerAngles {
public:
	char pad_0000[16]; //0x0000
	CPlayerCameraData* m_cam_data; //0x0010
	char pad_0018[40]; //0x0018
	Vector3 m_fps_angles; //0x0040
	char pad_004C[20]; //0x004C
	Vector3 m_cam_pos; //0x0060 // for fps and tps
	char pad_006C[212]; //0x006C
	Vector3 m_cam_pos2; //0x0140
	char pad_014C[644]; //0x014C
	Vector3 m_tps_angles; //0x03D0
	char pad_03DC[20]; //0x03DC
	Vector3 m_fps_cam_pos; //0x03F0
	char pad_03FC[88]; //0x03FC
};

//=======================================


class CViewPort {
public:
	char _0x0000[0x24C];
	float fViewMatrix[0x10];
	//D3DXMATRIX fViewMatrix;
};//Size=0x028C

class CWorld {
public:
	char _0x0000[0x8];
	CObject* pLocalPlayer; //0x0008 

	CObject* getLocalPlayer() {
		if (IsValidPtr(pLocalPlayer)) {
			return pLocalPlayer;
		}
		else {
			return nullptr;
		}
	}
};//Size=0x0016

class CWorldFactory {
public:
	CWorld* world;
};


class CModelInfo {
public:
	char pad_0x0000[0x270]; //0x0000
	BYTE Type; //0x0270 
	char pad_0x0271[0xF]; //0x0271

	DWORD GetHash() {
		return (*(DWORD*)((DWORD64)this + 0x18));
	}
}; //Size=0x0280

class CObjectNavigation {
public:
	char pad_0[0x20];
	Vector4 Rotation;
	char pad_1[0x20];
	Vector3 Position;

	void WritePos(Vector3 Pos) {
		*(Vector3*)(((DWORD64)this + 0x50)) = Pos;
	}
};



class CAttacker {
public:
	CObject* CPed0; //0x0000 
	char pad_0x0008[0x10]; //0x0008
	CObject* CPed1; //0x0018 
	char pad_0x0020[0x10]; //0x0020
	CObject* CPed2; //0x0030 

}; //Size=0x0038

//=======================================


class CReplayInterfacePed {
private:
	class CPedList {
	private:
		struct Ped {
			CObject* ped;
			__int32 iHandle; //0x0008 
			char _pad0[0x4];
		};

	public:
		Ped peds[256];
	};

public:
	char _pad0[0x100];			// 0000 - 0100
	CPedList* ped_list;			// 0100 - 0108
	int max_peds;				// 0108 - 010C
	char _pad1[0x4];			// 010C - 0110
	int number_of_peds;		// 0110 - 0114

	CObject* get_ped(const unsigned int& index) {
		return (index <= max_peds && IsValidPtr(ped_list->peds[index].ped) ? ped_list->peds[index].ped : nullptr);
	}
};

class CReplayInterfaceVehicle {
private:
	class VehicleHandle {
	public:
		CVehicle* vehicle; //0x0000 
		__int32 handle; //0x0008
		char _pad0[0x4];
	};//Size=0x0588

	class CVehicleList {
	public:
		VehicleHandle vehicles[0x100];//0x0000 
	};//Size=0x0490

public:
	char _0x0000[0x180];
	CVehicleList* vehicle_list; //0x0180
	__int32 max_vehicles; //0x0188 
	char _0x010C[0x4];
	__int32 number_of_vehicles; //0x0190 
	char _0x0114[0x34];

	CVehicle* get_vehicle(const unsigned int& index) {
		return (index <= max_vehicles && IsValidPtr(vehicle_list->vehicles[index].vehicle) ? vehicle_list->vehicles[index].vehicle : nullptr);
	}
};


class CObjectInterface {
private:
	class CObjectHandle {
	public:
		CObject* pCObject; //0x0000 
		__int32 iHandle; //0x0008 
		char pad_0x000C[0x4]; //0x000C

	}; //Size=0x0010

	class CObjectList {
	public:
		CObjectHandle ObjectList[2300]; //0x0000 

	}; //Size=0x8FC0

public:
	char pad_0x0000[0x158]; //0x0000
	CObjectList* pCObjectList; //0x0158 
	__int32 iMaxObjects; //0x0160 
	char pad_0x0164[0x4]; //0x0164
	__int32 iCurObjects; //0x0168 
	char pad_0x016C[0x5C]; //0x016C

	CObject* get_object(const unsigned int& index) {
		return (IsValidPtr(pCObjectList) && index < iMaxObjects&& IsValidPtr(pCObjectList->ObjectList[index].pCObject) ? pCObjectList->ObjectList[index].pCObject : nullptr);
	}
	bool Remove_object(const unsigned int& index) {
		if (IsValidPtr(pCObjectList) && index < iMaxObjects && IsValidPtr(pCObjectList->ObjectList[index].pCObject) ? pCObjectList->ObjectList[index].pCObject : nullptr) {
			pCObjectList->ObjectList[index].iHandle = 0;
		}
		return true;
	}
	__int32 getHandle(const unsigned int& index) {
		if (IsValidPtr(pCObjectList) && index < iMaxObjects && IsValidPtr(pCObjectList->ObjectList[index].pCObject) ? pCObjectList->ObjectList[index].pCObject : nullptr) {
			return pCObjectList->ObjectList[index].iHandle;
		}
		return NULL;
	}

}; //Size=0x01C8

class CReplayInterface {
public:
	void* game_interface;
	void* camera_interface;
	CReplayInterfaceVehicle* vehicle_interface;
	CReplayInterfacePed* ped_interface;
	void* pickup_interface;
	CObjectInterface* object_interface;
};

//=======================================


class CVehicleHandling {
public:
	char pad_0x0000[0xC]; //0x0000
	float fMass; //0x000C 
	char pad_0x0010[0x10]; //0x0010
	Vector3 v3CentreOfMassOffset; //0x0020 
	char pad_0x002C[0x4]; //0x002C
	Vector3 v3InertiaMult; //0x0030 
	char pad_0x003C[0x4]; //0x003C
	float fPercentSubmerged; //0x0040 
	char pad_0x0044[0x8]; //0x0044
	float fAcceleration; //0x004C 
	BYTE btInitialDriveGears; //0x0050 
	char pad_0x0051[0x3]; //0x0051
	float fDriveInertia; //0x0054 
	float fClutchChangeRateScaleUpShift; //0x0058 
	float fClutchChangeRateScaleDownShift; //0x005C 
	float fInitialDriveForce; //0x0060 
	char pad_0x0064[0x8]; //0x0064
	float fBrakeForce; //0x006C 
	char pad_0x0070[0x4]; //0x0070
	float fBrakeBiasFront; //0x0074 
	char pad_0x0078[0x4]; //0x0078
	float fHandBrakeForce; //0x007C 
	char pad_0x0080[0x8]; //0x0080
	float fTractionCurveMax; //0x0088 
	char pad_0x008C[0x4]; //0x008C
	float fTractionCurveMin; //0x0090 
	char pad_0x0094[0xC]; //0x0094
	float fTractionSpringDeltaMax; //0x00A0 
	char pad_0x00A4[0x4]; //0x00A4
	float fLowSpeedTractionLossMult; //0x00A8 
	float fCamberStiffnesss; //0x00AC 
	float fTractionBiasFront; //0x00B0 
	float fTwoMinus_fTractionBiasFront; //0x00B4 
	float fTractionLossMult; //0x00B8 
	float fSuspensionForce; //0x00BC 
	float fSuspensionCompDamp; //0x00C0 
	float fSuspensionReboundDamp; //0x00C4 
	float fSuspensionUpperLimit; //0x00C8 
	float fSuspensionLowerLimit; //0x00CC 
	char pad_0x00D0[0xC]; //0x00D0
	float fAntiRollBarForce; //0x00DC 
	char pad_0x00E0[0x8]; //0x00E0
	float fRollCentreHeightFront; //0x00E8 
	float fRollCentreHeightRear; //0x00EC 
	float fCollisionDamageMult; //0x00F0 
	float fWeaponDamageMult; //0x00F4 
	float fDeformationDamageMult; //0x00F8 
	float fEngineDamageMult; //0x00FC 
	float fPetrolTankVolume; //0x0100 
	float fOilVolume; //0x0104 



	float getMass() {
		return *(float*)((uintptr_t)this + 0xC);
	}
	void setMass(float v) {
		*(float*)((uintptr_t)this + 0xC) = v;
	}
	float getAcceleration() {
		return *(float*)((uintptr_t)this + 0x4C);
	}
	void setAcceleration(float v) {
		*(float*)((uintptr_t)this + 0x4C) = v;
	}
	float getInitialDriveForce() {
		return *(float*)((uintptr_t)this + 0x60);
	}
	void setInitialDriveForce(float v) {
		*(float*)((uintptr_t)this + 0x60) = v;
	}


	//oBouyancy = 0x40 -- float
	//oAcceleration = 0x4C
	//oDriveInertia = 0x54
	//oInitialDriveForce = 0x60
	//oBrakeForce = 0x6C
	//oHandbrakeForce = 0x7C
	//oTractionCurveMax = 0x88
	//oTractionCurveMin = 0x90
	//oCollisionMult = 0xF0
	//oWeaponMult = 0xF4
	//oDeformationMult = 0xF8
	//oEngineMult = 0xFC
	//oThrust = 0x338
}; //Size=0x0108

//=======================================

class CVehicle {
public:
	char pad_0x0000[0x30]; //0x0000
	CObjectNavigation* pCNavigation; //0x0030  CNavigation
	char pad_0x0038[0x10]; //0x0038
	void* pCVehicleMods; //0x0048  CVehicleMods*
	char pad_0x0050[0x40]; //0x0050
	Vector3 fPosition; //0x0090 
	char pad_0x009C[0x3C]; //0x009C
	BYTE btState; //0x00D8 
	char pad_0x00D9[0xB0]; //0x00D9
	BYTE btGodMode; //0x0189 
	char pad_0x018A[0xF6]; //0x018A
	float fHealth; //0x0280 
	char pad_0x0284[0x1C]; //0x0284
	float fHealthMax; //0x02A0 
	char pad_0x02A4[0x4]; //0x02A4
	CAttacker* pCAttacker; //0x02A8 
	char pad_0x02B0[0x6A]; //0x02B0
	BYTE btVolticRocketState; //0x031A 
	char pad_0x031B[0x1]; //0x031B
	float fVolticRocketEnergy; //0x031C 
	char pad_0x0320[0x430]; //0x0320
	Vector3 v3Velocity; //0x0750 
	char pad_0x075C[0xF0]; //0x075C
	float fHealth2; //0x084C 
	char pad_0x0850[0x28]; //0x0850
	CVehicleHandling* pVehicleHandlingOutdated; //0x0878 
	char pad_0x0880[0x3]; //0x0880
	BYTE btBulletproofTires; //0x0883 
	char pad_0x0884[0x4]; //0x0884
	BYTE btStolen; //0x0888 
	char pad_0x0889[0x11]; //0x0889
	BYTE N00000954; //0x089A 
	char pad_0x089B[0x41]; //0x089B
	float N0000081E; //0x08DC 
	char pad_0x08E0[0x58]; //0x08E0
	CVehicleHandling* pVehicleHandling;
	//float fDirtLevel; //0x0938			max = 15.f
	char pad_0x093C[0xA8]; //0x093C
	DWORD dwCarAlarmLength; //0x09E4 
	char pad_0x09E8[0x148]; //0x09E8
	BYTE btOpenableDoors; //0x0B30 
	char pad_0x0B31[0x4B]; //0x0B31
	float fGravity; //0x0B7C
	BYTE btMaxPassengers; //0x0B80 
	char pad_0x0B81[0x1]; //0x0B81
	BYTE btNumOfPassengers; //0x0B82 
	char pad_0x0B83[0x3D]; //0x0B83

	bool isGod() {
		return (btGodMode & 0x01) ? true : false;
	}

	bool hasBulletproofTires() {
		return (btBulletproofTires & 0x20) ? true : false;
	}

	bool disabledDoors() {
		return (btOpenableDoors == 0) ? true : false;
	}

	void openDoors() {
		btOpenableDoors = 1;
	}




	void giveHealth() {
		if (fHealth < fHealthMax)
			fHealth = fHealthMax;
		if (fHealth2 < fHealthMax)
			fHealth2 = fHealthMax;
	}

	//btState & 7    0 = inside of vehicle, 2 = outside of vehicle, 3 = vehicle blown up
	bool isVehicleDestroyed() {
		return (btState & 7) == 3;
	}

	void set_stolen(bool toggle) {
		this->btStolen &= 0xFEu;
		this->btStolen |= toggle & 1;
	}



	CModelInfo* ModelInfo() {
		return (*(CModelInfo**)((DWORD64)this + 0x20));
	}

	BYTE isUnlocked() {
		return *(BYTE*)((DWORD64)this + 0x1390);
	}

	void setUnlocked(BYTE n) {
		*(BYTE*)((DWORD64)this + 0x1390) = n;
	}

	BYTE getEngine() {
		return *(BYTE*)((DWORD64)this + 0x94A);
	}

	void setEngine(BYTE n) {
		*(BYTE*)((DWORD64)this + 0x94A) = n;
	}

	float getGravity() {
		return *(float*)((DWORD64)this + 0xC5C);
	}

	void setGravity(float v) {
		*(float*)((DWORD64)this + 0xC5C) = v;
	}

	CVehicleHandling* handling() {
		return *(CVehicleHandling**)((uintptr_t)this + 0x938);
	}

}; //Size=0x0BC0

class CPlayerBones {
public:
	Vector3 HEAD;
	Vector3 NECK;

	Vector3 RIGHT_HAND;
	Vector3 RIGHT_FOREARM;
	Vector3 RIGHT_UPPER_ARM;
	Vector3 RIGHT_CLAVICLE;

	Vector3 LEFT_HAND;
	Vector3 LEFT_FOREARM;
	Vector3 LEFT_UPPER_ARM;
	Vector3 LEFT_CLAVICLE;

	Vector3 PELVIS;
	Vector3 SPINE_ROOT;
	Vector3 SPINE0;
	Vector3 SPINE1;
	Vector3 SPINE2;
	Vector3 SPINE3;

	Vector3 RIGHT_TOE;
	Vector3	RIGHT_FOOT;
	Vector3	RIGHT_CALF;
	Vector3	RIGHT_THIGH;

	Vector3	LEFT_TOE;
	Vector3	LEFT_FOOT;
	Vector3	LEFT_CALF;
	Vector3	LEFT_THIGH;
};

class CGroup {
public:
	char* groupName;
	BYTE topsID;
};
class CWeaponInfo {
public:
	char pad_0000[16]; //0x0000
	uint32_t m_NameHash; //0x0010
	uint32_t m_ModelHash; //0x0014
	char pad_0018[72]; //0x0018
	void* pCAmmoInfo; //0x0060
	char pad_0068[20]; //0x0068
	float fWeaponSpread; //0x007C
	char pad_0078[30]; //0x0080
	float fBulletDamage; //0x00B0
	char pad_0130[576]; //0xB4
	float fWeaponRecoil; //0x02F4


	void setRecoil(float value) {
		//*(float*)((DWORD64)this + 0x2E8) = value;
		*(float*)((DWORD64)this + 0x2F4) = value;
	}
	void setSpread(float value) {
		*(float*)((DWORD64)this + 0x84) = value;//0.0f; //Spread
												//*(float*)( (DWORD64)this + 0x11C ) = 0.0f; //Multi Bulit spread
	}
	char* GetSzWeaponName() {
		return (*reinterpret_cast<char**>((DWORD64)this + 0x5F0));
	}
}; //Size: 0x0610

class CWeaponManager {
public:
	char pad_0000[32]; //0x0000
	CWeaponInfo* _WeaponInfo; //0x0020
	char pad_0028[96]; //0x0028
	void* _CurrentWeapon; //0x0088
	char pad_0090[272]; //0x0090
	Vector3 Aiming_at_Cord; //0x01A0
	char pad_01AC[4]; //0x01AC
	Vector3 Last_Impact_Cord; //0x01B0
	char pad_01BC[44]; //0x01BC
}; //Size: 0x01E8


class CObject {
public:
	char pad_0x0000[0x2C]; //0x0000
	BYTE btInvisibleSP; //0x002C 
	char pad_0x002D[0x1]; //0x002D
	BYTE btFreezeMomentum; //0x002E 
	char pad_0x002F[0x1]; //0x002F




	//CObjectNavigation* _ObjectNavigation; //0x0030 
	//char pad_0x0038[0x58]; //0x0038
	//Vector3 fPosition; //0x0090 

	CObjectNavigation* _ObjectNavigation; //0x0030 
	char pax_0x0038[0x10]; //0x0038
	void* pCPedStyle; //0x0048
	char pad_0x0038[0x40]; //0x0050
	Vector3 fPosition; //0x0090 



	char pad_0x009C[0xED]; //0x009C
	BYTE godmode; //0x0189 
	char pad_0x018A[0xF6]; //0x018A
	float HP; //0x0280 
	char pad_0x0284[0x1C]; //0x0284
	float MaxHP; //0x02A0 
	char pad_0x02A4[0x4]; //0x02A4
	CAttacker* CAttacker; //0x02A8 
	char pad_0x02B0[0x70]; //0x02B0
	Vector3 v3Velocity; //0x0320 
	char pad_0x032C[0x9FC]; //0x032C
	CVehicle* VehicleManager; //0x0D28 
	char pad_0x0D30[0x378]; //0x0D30
	BYTE btNoRagdoll; //0x10A8 
	char pad_0x10A9[0xF]; //0x10A9
	void* PlayerInfo; //0x10B8 
	char pad_0x10C0[0x18]; //0x10C0
	CWeaponManager* WeaponManager; //0x10C8 change to 10D8 
	char pad_0x10D0[0x31C]; //0x10D0
	BYTE btSeatBelt; //0x13EC 
	char pad_0x13ED[0xB]; //0x13ED
	BYTE btSeatbeltWindshield; //0x13F8 
	char pad_0x13F9[0x72]; //0x13F9
	BYTE btIsInVehicle; //0x146B 
	char pad_0x146C[0x44]; //0x146C
	float Armor; //0x14B0 
	char pad_0x14B4[0x3C]; //0x14B4

	CVehicle* vehicle() {
		return *(CVehicle**)((uintptr_t)this + 0xD30);
		//return *(CVehicle**)((DWORD64)this + 0xD30);

	}

	bool IsVisible() {
		return (*(BYTE*)((DWORD64)this + 0xAC) > 0 ? true : false);
	}
	void SetAlpha(float alpha) {
		(*(BYTE*)((DWORD64)this + 0xAC)) = alpha;
	}
	BYTE GetAlpha() {
		return (*(BYTE*)((DWORD64)this + 0xAC));
	}

	float GetArmor() {
		//return (*(float*)((DWORD64)this + 0x14B8));
		return (*(float*)((DWORD64)this + 0x14E0));
	}
	void SetArmor(float v) {
		//return (*(float*)((DWORD64)this + 0x14B8));
		*(float*)((DWORD64)this + 0x14E0) = v;
	}

	bool is_god_active() {
		return (godmode & 0x01) ? true : false;
	}
	void set_godmode(bool toggle) {
		this->godmode = toggle ? 0x1 : 0x0;
	}


	CModelInfo* ModelInfo() {
		return (*(CModelInfo**)((DWORD64)this + 0x20));
	}


}; //Size=0x14F8




enum ExplosionTypes {
	EXPLOSION_GRENADE,
	EXPLOSION_GRENADELAUNCHER,
	EXPLOSION_STICKYBOMB,
	EXPLOSION_MOLOTOV,
	EXPLOSION_ROCKET,
	EXPLOSION_TANKSHELL,
	EXPLOSION_HI_OCTANE,
	EXPLOSION_CAR,
	EXPLOSION_PLANE,
	EXPLOSION_PETROL_PUMP,
	EXPLOSION_BIKE,
	EXPLOSION_DIR_STEAM,
	EXPLOSION_DIR_FLAME,
	EXPLOSION_DIR_WATER_HYDRANT,
	EXPLOSION_DIR_GAS_CANISTER,
	EXPLOSION_BOAT,
	EXPLOSION_SHIP_DESTROY,
	EXPLOSION_TRUCK,
	EXPLOSION_BULLET,
	EXPLOSION_SMOKEGRENADELAUNCHER,
	EXPLOSION_SMOKEGRENADE,
	EXPLOSION_BZGAS,
	EXPLOSION_FLARE,
	EXPLOSION_GAS_CANISTER,
	EXPLOSION_EXTINGUISHER,
	EXPLOSION_PROGRAMMABLEAR,
	EXPLOSION_TRAIN,
	EXPLOSION_BARREL,
	EXPLOSION_PROPANE,
	EXPLOSION_BLIMP,
	EXPLOSION_DIR_FLAME_EXPLODE,
	EXPLOSION_TANKER,
	EXPLOSION_PLANE_ROCKET,
	EXPLOSION_VEHICLE_BULLET,
	EXPLOSION_GAS_TANK,
	EXPLOSION_BIRD_CRAP
};

enum WeaponHashes {
	WEAPON_ADVANCEDRIFLE = 0xAF113F99,
	WEAPON_AIRSTRIKE_ROCKET = 0x13579279,
	WEAPON_ANIMAL = 0xF9FBAEBE,
	WEAPON_APPISTOL = 0x22D8FE39,
	WEAPON_ASSAULTRIFLE = 0xBFEFFF6D,
	WEAPON_ASSAULTSHOTGUN = 0xE284C527,
	WEAPON_ASSAULTSMG = 0xEFE7E2DF,
	WEAPON_TEC9 = 0xDB1AA450,
	WEAPON_DOUBLEBARRELED = 0xDB1AA450,
	WEAPON_BALL = 0x23C9F95C,
	WEAPON_BARBED_WIRE = 0x48E7B178,
	WEAPON_BAT = 0x958A4A8F,
	WEAPON_BLEEDING = 0x8B7333FB,
	WEAPON_BOTTLE = 0xF9E6AA4B,
	WEAPON_BRIEFCASE = 0x88C78EB7,
	WEAPON_BRIEFCASE_02 = 0x01B79F17,
	WEAPON_BULLPUPRIFLE = 0x7F229F94,
	WEAPON_COMPACTRIFLE = 0x624FE830,
	WEAPON_BULLPUPSHOTGUN = 0x9D61E50F,
	WEAPON_BZGAS = 0xA0973D5E,
	WEAPON_CARBINERIFLE = 0x83BF0278,
	WEAPON_COMBATMG = 0x7FD62962,
	WEAPON_PARACHUTE = 0xFBAB5776,
	WEAPON_COMBATPDW = 0xA3D4D34,
	WEAPON_COMBATPISTOL = 0x5EF9FEC4,
	WEAPON_COUGAR = 0x08D4BE52,
	WEAPON_CROWBAR = 0x84BD7BFD,
	WEAPON_DAGGER = 0x92A27487,
	WEAPON_DIGISCANNER = 0xFDBADCED,
	WEAPON_DROWNING = 0xFF58C4FB,
	WEAPON_DROWNING_IN_VEHICLE = 0x736F5990,
	WEAPON_ELECTRIC_FENCE = 0x92BD4EBB,
	WEAPON_EXHAUSTION = 0x364A29EC,
	WEAPON_EXPLOSION = 0x2024F4E8,
	WEAPON_FALL = 0xCDC174B0,
	WEAPON_FIRE = 0xDF8E89EB,
	WEAPON_FIREEXTINGUISHER = 0x060EC506,
	WEAPON_FIREWORK = 0x7F7497E5,
	WEAPON_FLARE = 0x497FACC3,
	WEAPON_FLAREGUN = 0x47757124,
	WEAPON_GARBAGEBAG = 0xE232C28C,
	WEAPON_GOLFCLUB = 0x440E4788,
	WEAPON_GRENADE = 0x93E220BD,
	WEAPON_GRENADELAUNCHER = 0xA284510B,
	WEAPON_GRENADELAUNCHER_SMOKE = 0x4DD2DC56,
	WEAPON_GUSENBERG = 0x61012683,
	WEAPON_HAMMER = 0x4E875F73,
	WEAPON_HANDCUFFS = 0xD04C944D,
	WEAPON_HEAVYPISTOL = 0xD205520E,
	WEAPON_HEAVYSHOTGUN = 0x3AABBBAA,
	WEAPON_HEAVYSNIPER = 0x0C472FE2,
	WEAPON_HELI_CRASH = 0x145F1012,
	WEAPON_HIT_BY_WATER_CANNON = 0xCC34325E,
	WEAPON_HOMINGLAUNCHER = 0x63AB0442,
	WEAPON_KNIFE = 0x99B507EA,
	WEAPON_KNUCKLE = 0xD8DF3C3C,
	WEAPON_MARKSMANPISTOL = 0xDC4DB296,
	WEAPON_MARKSMANRIFLE = 0xC734385A,
	WEAPON_MG = 0x9D07F764,
	WEAPON_HATCHET = 0xF9DCBF2D,
	WEAPON_FLASHLIGHT = 0x8BB05FD7,
	WEAPON_MACHINEPISTOL = 0xDB1AA450,
	WEAPON_MACHETE = 0xDD5DF8D9,
	WEAPON_SWITCHBLADE = 0xDFE37640,
	WEAPON_REVOLVER = 0xC1B3C3D1,
	WEAPON_MICROSMG = 0x13532244,
	WEAPON_MINIGUN = 0x42BF8A85,
	WEAPON_MOLOTOV = 0x24B17070,
	WEAPON_MUSKET = 0xA89CB99E,
	WEAPON_NIGHTSTICK = 0x678B81B1,
	WEAPON_PASSENGER_ROCKET = 0x166218FF,
	WEAPON_PETROLCAN = 0x34A67B97,
	WEAPON_PISTOL = 0x1B06D571,
	WEAPON_PISTOL50 = 0x99AEEB3B,
	WEAPON_PROXMINE = 0xAB564B93,
	WEAPON_PUMPSHOTGUN = 0x1D073A89,
	WEAPON_RAILGUN = 0x6D544C99,
	WEAPON_RAMMED_BY_CAR = 0x07FC7D7A,
	WEAPON_REMOTESNIPER = 0x33058E22,
	WEAPON_RPG = 0xB1CA77B1,
	WEAPON_RUN_OVER_BY_CAR = 0xA36D413E,
	WEAPON_SAWNOFFSHOTGUN = 0x7846A318,
	WEAPON_SMG = 0x2BE6766B,
	WEAPON_SMOKEGRENADE = 0xFDBC8A50,
	WEAPON_SNIPERRIFLE = 0x05FC3C11,
	WEAPON_SNOWBALL = 0x787F0BB,
	WEAPON_SNSPISTOL = 0xBFD21232,
	WEAPON_SPECIALCARBINE = 0xC0A3098D,
	WEAPON_STICKYBOMB = 0x2C3731D9,
	WEAPON_STINGER = 0x687652CE,
	WEAPON_STUNGUN = 0x3656C8C1,
	WEAPON_UNARMED = 0xA2719263,
	WEAPON_VEHICLE_ROCKET = 0xBEFDC581,
	WEAPON_VINTAGEPISTOL = 0x083839C4
};

typedef struct
{
	int Result;
	BOOL DidHitAnything;
	bool DidHitEntity;
	DWORD HitEntity;
	Vector3 HitCoords;
} RaycastResult;

enum IntersectOptions {
	IntersectEverything = -1,
	IntersectMap = 1,
	IntersectMissionEntityAndTrain = 2,
	IntersectPeds1 = 4,
	IntersectPeds2 = 8,
	IntersectVehicles = 10,
	IntersectObjects = 16,
	IntersectVegetation = 256
};

enum game_state_t
{
	playing,
	intro,
	unk,
	license,
	main_menu,
	load_online
};

enum class thread_state_t : std::uint32_t
{
	idle,
	running,
	killed,
	unk_3,
	unk_4,
};

class thread_context_t
{
public:
	std::uint32_t m_thread_id;
	std::uint32_t m_script_hash; // + 4 (program id)
	thread_state_t m_state; // + 8
	std::uint32_t m_instruction_pointer; // 0x0C
	std::uint32_t m_frame_pointer;       // 0x10
	std::uint32_t m_stack_pointer;       // 0x14
	float m_timer_a;                     // 0x18
	float m_timer_b;                     // 0x1C
	float m_timer_c;                     // 0x20
	char m_padding1[0x2C];               // 0x24
	std::uint32_t m_stack_size;          // 0x50
	char m_padding2[0x54];               // 0x54
};

class game_thread
{
public:
	virtual ~game_thread() = default;
	virtual thread_state_t reset(std::uint32_t script_hash, void* args, std::uint32_t arg_count) = 0;
	virtual thread_state_t run() = 0;
	virtual thread_state_t tick() = 0;
	virtual void kill() = 0;

	inline static game_thread*& get()
	{
		return *(game_thread**)(*reinterpret_cast<uintptr_t*>(__readgsqword(0x58)) + 0x830);
	}
public:
	thread_context_t m_context; // 0x08
	void* m_stack;              // 0xB0
	char m_padding[0x10];       // 0xB8
	const char* m_exit_message; // 0xC8
	char m_name[0x40];          // 0xD0
	void* m_handler;   // 0x110
	char m_padding2[0x28];      // 0x118
	std::uint8_t m_flag1;       // 0x140
	std::uint8_t m_flag2;       // 0x141
	char m_padding3[0x16];      // 0x142
};

template<typename type>
class array_collection
{
private:
	type* data;
	uint16_t	count;
	uint16_t	size;

public:
	type* begin()
	{
		return data;
	}

	type* end()
	{
		return (data + count);
	}

	type* at(uint16_t index)
	{
		return &data[index];
	}
};
