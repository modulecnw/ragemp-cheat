#include "config.hpp"
#include "hacks/visuals_player.hpp"
#include "memory/memory.hpp"

std::string VisualsPlayer::getCategory()
{
	return std::string("Visuals");
}

std::string VisualsPlayer::getName()
{
	return std::string("Player");
}

const int MAX_PLAYERS = 255;

void VisualsPlayer::Tick()
{
	if (!Config::Instance().visuals.player.enabled) return;

	for (int i = 0; i < MAX_PLAYERS; i++) {
		auto* pRemotePlayer = *reinterpret_cast<CRemotePlayer**>((DWORD64)Memory::Instance().ptr_rage037_pool + (i * 0x8));
		if (pRemotePlayer == NULL) continue;

		if (!IsValidPtr(pRemotePlayer) || !IsValidPtr(pRemotePlayer->pPedLink) || !IsValidPtr(pRemotePlayer->pPedLink->pPed)) continue;

		CObject* ped = pRemotePlayer->pPedLink->pPed;
		if (ped == NULL || !IsValidPtr(ped)) continue;


	}
}

