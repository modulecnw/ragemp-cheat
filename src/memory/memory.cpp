#include "memory/memory.hpp"
#include "memory/patterns.hpp"

void Memory::Initialize() {
	this->gta5_module = memory::module_t(nullptr);
	this->ragemp_module = memory::module_t(_xor_("multiplayerL.dll"));
	Log::Warning(_xor_("[+] Memory >> Initializing memory..."), std::to_string(this->gta5_module.base()));

	if (!this->ragemp_module.base()) {
		this->multiplayer_framework = MultiplayerFrameworks::RAGEMP_11;
		this->ragemp_module = memory::module_t(_xor_("multiplayer.dll"));
	}

	this->ptr_gta_swapchain = *memory::as_relative<IDXGISwapChain**>(memory::find_pattern(this->gta5_module, _xor_("Swapchain"), Patterns::Instance().pattern_gta_swapchain));
	this->ptr_gta_world		= memory::as_relative<CWorld*>(memory::find_pattern(this->gta5_module, _xor_("World"), Patterns::Instance().pattern_gta_world));
	this->ptr_gta_viewport	= memory::as_relative<CViewPort*>(memory::find_pattern(this->gta5_module, _xor_("Viewport"), Patterns::Instance().pattern_gta_viewport));
	
	//this->ptr_rage037_pool = memory::as_relative<CRagePool*>(memory::find_pattern(this->gta5_module, _xor_("Swapchain"), this->pattern_rage037_replayinterface));
}

