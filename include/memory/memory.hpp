#pragma once
#include "imports.hpp"
#include "module.hpp"
#include "scanner.hpp"

using namespace std;
class Memory : public Singleton<Memory>
{
public:
    memory::module_t gta5_module = memory::module_t(nullptr);
    memory::module_t ragemp_module = memory::module_t(nullptr);

    MultiplayerFrameworks multiplayer_framework = MultiplayerFrameworks::RAGEMP_037;

    IDXGISwapChain* ptr_gta_swapchain = nullptr;
    CWorld* ptr_gta_world = nullptr;
    CViewPort* ptr_gta_viewport = nullptr;

    CRagePool* ptr_rage037_pool = nullptr;

    void Initialize();
};