#pragma once
#include "imports.hpp"
#include "module.hpp"
#include "scanner.hpp"

using namespace std;
class Memory : public Singleton<Memory>
{
private:
    /* patterns gta */
    string pattern_gta_swapchain = _xor_("48 8B 0D ? ? ? ? 48 8B 01 44 8D 43 01 33 D2 FF 50 40 8B C8");
    string pattern_gta_world = _xor_("48 8B 05 ? ? ? ? 48 8B 58 08 48 85 DB 74 32");
    string pattern_gta_viewport = _xor_("48 8B 15 ? ? ? ? 48 8D 2D ? ? ? ? 48 8B CD");

    /* patterns rage037 */
    string pattern_rage037_replayinterface = _xor_("48 8B 05 ? ? ? ? 48 8B 1C C8 48 85 DB 0F 84 ? ? ? ? 8B");
    string pattern_rage037_nametags_setter = _xor_("88 0D ? ? ? ? C3");
    string pattern_rage037_get_name = _xor_("0F B7 C2 48 C1 E0 05");
    string pattern_rage037_get_name_verify = _xor_("48 83 EC 38 48 C7 44 24 ? ? ? ? ? 48 8B 05 ? ? ? ? 48 85 C0 75 1B 8D 48 08");

    /* patterns rage11 */

    /* patterns rageshared */
    // maybe here shared patterns?

public:
    memory::module_t gta5_module = memory::module_t(nullptr);
    memory::module_t ragemp_module = memory::module_t(nullptr);

    MultiplayerFrameworks multiplayer_framework = MultiplayerFrameworks::RAGEMP_037;

    uintptr_t memory_test_ptr = 0;

    void Initialize();
};