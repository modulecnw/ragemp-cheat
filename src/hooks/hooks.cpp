#include "hooks/hooks.hpp"
#include "hooks/renderer.hpp"

// needs rework
HRESULT call_renderer_hook(IDXGISwapChain* this_swapchain_pointer, unsigned int sync_interval, unsigned int flags)
{
	Renderer::Instance().Render(this_swapchain_pointer, sync_interval, flags);
	return Hooks::Instance().vthDirectHook->fetch(call_renderer_hook, 8)(this_swapchain_pointer, sync_interval, flags);
}

void Hooks::Render() {
	this->vthDirectHook = std::make_unique<hooks::virtual_table_hook>("Swapchain", Memory::Instance().ptr_gta_swapchain, 0x12);
	this->vthDirectHook->attach(8, call_renderer_hook);
	this->vthDirectHook->enable();

}

void Hooks::Initialize() {
	Log::Warning("[+] Hooks >> Initializing hooks...");

	this->Render();
}