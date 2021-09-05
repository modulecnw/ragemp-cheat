#include "hacks/aimbot.hpp"
#include "hacks/replayinterface.hpp"

#include "memory/memory.hpp"
#include "utils.hpp"
#include "config.hpp"
#include "functions.hpp"

std::string Aimbot::getCategory()
{
	return std::string("Aiming");
}

std::string Aimbot::getName()
{
	return std::string("Aimbot");
}

int current_target = -1;

void getBestTarget(CPlayerAngles* cam) {
	if (IsValidPtr(cam)) {
		Vector3 CrosshairPos = cam->m_cam_pos;
		static float oldDistance = FLT_MAX;
		float newDistance = 0;

		if (current_target == -1) oldDistance = FLT_MAX;

		for (int i = 0; i < 255; i++) {
			auto* nPed = &Replayinterface::Instance().peds[i];
			if (nPed == NULL) continue;

			Vector3 aimpos = nPed->bones.HEAD;
			Vector2 aim2d = functions::world_to_screen_vec(aimpos);

			newDistance = functions::screen_distance(Nemo::Instance().vScreen.x / 2, Nemo::Instance().vScreen.y / 2, aim2d.x, aim2d.y);
			if (newDistance < oldDistance && newDistance < Config::Instance().aiming.aimbot.fov) {
				oldDistance = newDistance;
				current_target = i;
			}
		}
	}
}

void Aimbot::Tick()
{
	if (!Config::Instance().aiming.aimbot.enabled) return;
	try {
		if (GetAsyncKeyState(Config::Instance().aiming.aimbot.aim_key) & 0x8000) {

			CPlayerAngles* cam = functions::get_camera();
			if (IsValidPtr(cam)) {
				if (current_target == -1) getBestTarget(cam);

				if (current_target != -1) {
					auto* target = &Replayinterface::Instance().peds[current_target];
					if (!target) {
						current_target = -1;
						return;
					}

					Vector3 CrosshairPos = cam->m_cam_pos;
					Vector3 aimpos = target->bones.HEAD;
					Vector2 aim2d = functions::world_to_screen_vec(aimpos);

					auto Distance = functions::get_distance(CrosshairPos, aimpos);
					float Distance2d = functions::screen_distance(Nemo::Instance().vScreen.x / 2, Nemo::Instance().vScreen.y / 2, aim2d.x, aim2d.y);

					Vector3 Out = Vector3((aimpos.x - CrosshairPos.x) / Distance, (aimpos.y - CrosshairPos.y) / Distance, (aimpos.z - CrosshairPos.z) / Distance);

					cam->m_fps_angles = Out;
					cam->m_tps_angles = Out;
				}
			}
		}
		else {
			current_target = -1;
		}

	}
	catch (const std::exception& e) {
		printf_s(e.what());
	}
}