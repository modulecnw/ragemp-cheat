#include "memory/memory.hpp"
#include "memory/patterns.hpp"
#include "gta/fiber.hpp"

void Memory::Initialize() {
	this->gta5_module = memory::module_t(nullptr);
	this->ragemp_module = memory::module_t(_xor_("multiplayerL.dll"));
	Log::Warning(_xor_("[+] Memory >> Initializing memory..."), std::to_string(this->gta5_module.base()));

	if (!this->ragemp_module.base()) {
		this->multiplayer_framework = MultiplayerFrameworks::RAGEMP_11;
		this->ragemp_module = memory::module_t(_xor_("multiplayer.dll"));
	}

	this->ptr_gta_swapchain					= *memory::as_relative<IDXGISwapChain**>(memory::find_pattern(this->gta5_module, _xor_("Swapchain"), Patterns::Instance().pattern_gta_swapchain));
	this->ptr_gta_world_factory				= memory::as_relative<CWorldFactory*>(memory::find_pattern(this->gta5_module, _xor_("WorldFactory"), Patterns::Instance().pattern_gta_world_factory, -11));
	this->ptr_gta_viewport					= memory::as_relative<CViewPort*>(memory::find_pattern(this->gta5_module, _xor_("Viewport"), Patterns::Instance().pattern_gta_viewport));
	this->ptr_gta_world_to_screen			= memory::find_pattern<world_to_screen_t>(this->gta5_module, _xor_("WorldToScreen"), Patterns::Instance().pattern_gta_world_to_screen, -65);
	this->ptr_gta_get_bone_position			= memory::find_pattern<get_bone_position_t>(this->gta5_module, _xor_("GetBone"), Patterns::Instance().pattern_gta_get_bone_position, -16);
	this->ptr_gta_script_thread_tick		= memory::find_pattern<script_thread_tick_t>(this->gta5_module, _xor_("ScriptThreadTick"), Patterns::Instance().pattern_gta_script_thread_tick, -0xB);
	this->ptr_gta_fix_context_vector		= memory::find_pattern<fix_context_vector_t>(this->gta5_module, _xor_("FixContextVector"), Patterns::Instance().pattern_gta_fix_context_vector);
	this->ptr_gta_fetch_native_handler		= memory::as_relative<fetch_native_handler_t>(memory::find_pattern(this->gta5_module, _xor_("FetchNativeHandler"), Patterns::Instance().pattern_gta_fetch_native_handler), 1);
	this->ptr_gta_native_handler_table		= memory::as_relative<uintptr_t*>(memory::find_pattern(this->gta5_module, _xor_("NativeHandlerTable"), Patterns::Instance().pattern_gta_native_handler_table));
	this->ptr_gta_pointer_to_handle			= memory::find_pattern<pointer_to_handle_t>(this->gta5_module, _xor_("PointerToHandle"), Patterns::Instance().pattern_gta_pointer_to_handle);

	if(this->multiplayer_framework == MultiplayerFrameworks::RAGEMP_037) {
		this->ptr_rage037_pool					= *memory::as_relative<CRagePool**>(memory::find_pattern(this->ragemp_module, _xor_("Rage Replayinterface"), Patterns::Instance().pattern_rage037_replayinterface));
		this->ptr_rage037_get_rage_name			= memory::find_pattern<get_rage_name_t>(this->ragemp_module, _xor_("Rage GetName"), Patterns::Instance().pattern_rage037_get_name);
		this->ptr_rage037_get_name_verify		= memory::find_pattern<get_name_verify_t>(this->ragemp_module, _xor_("Rage GetNameVerify"), Patterns::Instance().pattern_rage037_get_name_verify);
	}

	this->ptr_rageshared_fetch_handler		= memory::as_relative<ragemp_fetch_handler_t>(memory::find_pattern(this->ragemp_module, _xor_("Rage FetchHandler"), Patterns::Instance().pattern_rageshared_fetch_handler), 1);

	Fiber::Instance().Call();
}

