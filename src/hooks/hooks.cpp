#include "hooks/hooks.hpp"
#include "hooks/renderer.hpp"
#include "hooks/thread.hpp"
#include "gui/gui.hpp"
#include "gta/fiber.hpp"
#include "gta/natives/database.hpp"
#include "config.hpp"

// needs rework
HRESULT call_renderer_hook(IDXGISwapChain* this_swapchain_pointer, unsigned int sync_interval, unsigned int flags)
{
	Renderer::Instance().Render(this_swapchain_pointer, sync_interval, flags);
	return Hooks::Instance().vthDirectHook->fetch(call_renderer_hook, 8)(this_swapchain_pointer, sync_interval, flags);
}

uintptr_t hooked_native_thread(game_thread* this_ptr, int ops_to_execute) {
	Thread::Instance().Call(this_ptr, ops_to_execute);
	return Hooks::Instance().original_native_thread(this_ptr, ops_to_execute);
}

void on_entity_coords(native::nsdk::NativeContext& context)
{
	if (Config::Instance().vehicle.stealer) {
		auto ped = native::player::player_ped_id();

		if (context.GetArgument<int32_t>(0) == native::ped::get_vehicle_ped_is_using(ped))
			return;
	}

	reinterpret_cast<decltype(&on_entity_coords)>(Hooks::Instance().original_entity_set_coords)(context);
}

void on_entity_velocity(native::nsdk::NativeContext& context)
{
	if (Config::Instance().vehicle.stealer) {
		auto ped = native::player::player_ped_id();

		if (context.GetArgument<int32_t>(0) == native::ped::get_vehicle_ped_is_using(ped))
			return;
	}

	reinterpret_cast<decltype(&on_entity_velocity)>(Hooks::Instance().original_entity_set_velocity)(context);
}

void on_entity_rot(native::nsdk::NativeContext& context)
{
	if (Config::Instance().vehicle.stealer) {
		auto ped = native::player::player_ped_id();

	if (context.GetArgument<int32_t>(0) == native::ped::get_vehicle_ped_is_using(ped))
		return;
	}

	reinterpret_cast<decltype(&on_entity_rot)>(Hooks::Instance().original_entity_set_rotation)(context);
}


void Hooks::Render() {
	this->vthDirectHook = std::make_unique<hooks::virtual_table_hook>(_xor_("Swapchain").c_str(), Memory::Instance().ptr_gta_swapchain, 0x12);
	this->vthDirectHook->attach(8, call_renderer_hook);
	this->vthDirectHook->enable();
}

void Hooks::Thread() {
	Fiber::Instance().Call();

	MH_CreateHook(Memory::Instance().ptr_gta_script_thread_tick, hooked_native_thread, reinterpret_cast<void**>(&Hooks::Instance().original_native_thread));
	if (MH_EnableHook(Memory::Instance().ptr_gta_script_thread_tick) == MH_OK) {
		Log::Debug(_xor_("[+] Hooks >>"), _xor_("Game-Thread"), _xor_("enabled."));
	}
}

void Hooks::Native() {
	auto sync_coords = native::invoker::find_native_handler(0x9AFEFF481A85AB2E);
	MH_CreateHook(sync_coords, on_entity_coords, reinterpret_cast<void**>(&original_entity_set_coords));
	if (MH_EnableHook(sync_coords) == MH_OK) {
		Log::Debug(_xor_("[+] Hooks >>"), _xor_("Sync Coords"), _xor_("enabled."));
	}

	auto sync_velocity = native::invoker::find_native_handler(0x239A3351AC1DA385);
	MH_CreateHook(sync_velocity, on_entity_velocity, reinterpret_cast<void**>(&original_entity_set_velocity));
	if (MH_EnableHook(sync_velocity) == MH_OK) {
		Log::Debug(_xor_("[+] Hooks >>"), _xor_("Sync Velocity"), _xor_("enabled."));
	}

	auto sync_rot = native::invoker::find_native_handler(0x77B21BE7AC540F07);
	MH_CreateHook(sync_rot, on_entity_rot, reinterpret_cast<void**>(&original_entity_set_rotation));
	if (MH_EnableHook(sync_rot) == MH_OK) {
		Log::Debug(_xor_("[+] Hooks >>"), _xor_("Sync Rot"), _xor_("enabled."));
	}
}

void Hooks::Initialize() {
	Log::Warning("[+] Hooks >> Initializing hooks...");

	do {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		Log::Warning("[+] Hooks >> Waiting for game...");
	} while (*Memory::Instance().ptr_gta_game_state != game_state_t::playing);

	MH_Initialize();

	this->Render();
	this->Thread();

	this->Native();
}