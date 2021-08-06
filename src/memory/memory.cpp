#include "memory/memory.hpp"

void Memory::Initialize() {

	this->gta5_module = memory::module_t(nullptr);
	this->ragemp_module = memory::module_t(_xor_("multiplayerL.dll"));

	if (!this->ragemp_module.base()) {
		this->multiplayer_framework = MultiplayerFrameworks::RAGEMP_11;
		this->ragemp_module = memory::module_t(_xor_("multiplayer.dll"));
	}

	this->memory_test_ptr = memory::find_pattern(this->gta5_module, "Swapchain", this->pattern_gta_swapchain);

	Log::Warning(_xor_("Initializing memory..."), std::to_string(this->gta5_module.base()));
}