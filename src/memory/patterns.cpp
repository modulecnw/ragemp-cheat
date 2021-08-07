#include "memory/patterns.hpp"

void Patterns::Initialize() {
    Log::Warning(_xor_("[+] Patterns >> Initializing gta patterns..."));

    /* patterns gta */
    this->pattern_gta_swapchain = _xor_("48 8B 05 ? ? ? ? C3 48 8B C1 8D 4A 0E").c_str();
    this->pattern_gta_world = _xor_("48 8B 05 ? ? ? ? 48 8B 58 08 48 85 DB 74 32");
    this->pattern_gta_viewport = _xor_("48 8B 15 ? ? ? ? 48 8D 2D ? ? ? ? 48 8B CD");

    Log::Warning(_xor_("[+] Patterns >> Initializing rage037 patterns..."));

    /* patterns rage037 */
    this->pattern_rage037_replayinterface = _xor_("48 8B 05 ? ? ? ? 48 8B 1C C8 48 85 DB 0F 84 ? ? ? ? 8B");
    this->pattern_rage037_nametags_setter = _xor_("88 0D ? ? ? ? C3");
    this->pattern_rage037_get_name = _xor_("0F B7 C2 48 C1 E0 05");
    this->pattern_rage037_get_name_verify = _xor_("48 83 EC 38 48 C7 44 24 ? ? ? ? ? 48 8B 05 ? ? ? ? 48 85 C0 75 1B 8D 48 08");
}