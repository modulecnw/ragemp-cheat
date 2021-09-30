#pragma once
#include "imports.hpp"
#include "module.hpp"
#include "scanner.hpp"

using namespace std;
class Memory : public Singleton<Memory>
{
public:
	/* typedefs*/
	using script_thread_tick_t = uintptr_t(*)(game_thread* thread, int ops_to_execute);
	using fix_context_vector_t = void(*)(void* context);
	using fetch_native_handler_t = void* (*)(uintptr_t* table, uint64_t hash);
	using ragemp_fetch_handler_t = uintptr_t(*)(uintptr_t hash);

	using pointer_to_handle_t = int32_t(*)(void* ptr);
	using world_to_screen_t = bool(*)(Vector3* coords, float* x, float* y);
	using get_bone_position_t = void(*)(int32_t* ped, __m128* pos, int32_t bone);

	using get_name_verify_t = DWORD64*(*)();
	using get_rage_name_t = __int64(*)(DWORD64* thisptr, WORD a2);

	memory::module_t gta5_module = memory::module_t(nullptr);
	memory::module_t ragemp_module = memory::module_t(nullptr);

	MultiplayerFrameworks multiplayer_framework = MultiplayerFrameworks::RAGEMP_037;

	IDXGISwapChain* ptr_gta_swapchain = nullptr;
	CWorldFactory* ptr_gta_world_factory = nullptr;
	CReplayInterface* ptr_gta_replay_interface = nullptr;
	CViewPort* ptr_gta_viewport = nullptr;
	uintptr_t ptr_gta_camera = 0;
	world_to_screen_t ptr_gta_world_to_screen = nullptr;
	get_bone_position_t ptr_gta_get_bone_position = nullptr;
	script_thread_tick_t ptr_gta_script_thread_tick = nullptr;
	fix_context_vector_t ptr_gta_fix_context_vector = nullptr;
	fetch_native_handler_t ptr_gta_fetch_native_handler = nullptr;
	pointer_to_handle_t ptr_gta_pointer_to_handle = nullptr;
	game_state_t* ptr_gta_game_state = 0;
	uintptr_t* ptr_gta_native_handler_table = 0;

	CRagePool* ptr_rage037_pool = nullptr;
	get_name_verify_t ptr_rage037_get_name_verify = nullptr;
	get_rage_name_t ptr_rage037_get_rage_name = nullptr;

	ragemp_fetch_handler_t ptr_rageshared_fetch_handler = nullptr;

	void Initialize();
};