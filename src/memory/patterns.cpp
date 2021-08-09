#include "memory/patterns.hpp"

void Patterns::Initialize() {
    Log::Warning(_xor_("[+] Patterns >> Initializing gta patterns..."));

    /* patterns gta */
    this->pattern_gta_swapchain = _xor_("48 8B 0D ? ? ? ? 48 8B 01 44 8D 43 01 33 D2 FF 50 40 8B C8").c_str();
    this->pattern_gta_world = _xor_("48 8B 05 ? ? ? ? 48 8B 58 08 48 85 DB 74 32");
    this->pattern_gta_viewport = _xor_("48 8B 15 ? ? ? ? 48 8D 2D ? ? ? ? 48 8B CD");
    this->pattern_gta_world_to_screen = _xor_("48 8B E9 C6 44 24 ? ? F3 0F 10 09");
    this->pattern_gta_get_bone_position = _xor_("48 83 EC 60 48 8B 01 41 8B E8 48 8B F2");
    this->pattern_gta_script_thread_tick = _xor_("48 83 EC 20 80 B9 46 01 00 00 00 8B FA");
    this->pattern_gta_fix_context_vector = _xor_("83 79 18 00 48 8B D1 74 4A FF 4A 18 48 63 4A 18 48 8D 41 04 48 8B 4C CA");
    this->pattern_gta_fetch_native_handler = _xor_("E8 ? ? ? ? 48 85 C0 75 0A 48 8D 05 ? ? ? ?");
    this->pattern_gta_native_handler_table = _xor_("48 8D 0D ? ? ? ? 48 8B 14 FA E8 ? ? ? ? 48 85 C0 75 0A");

    Log::Warning(_xor_("[+] Patterns >> Initializing rage037 patterns..."));

    /* patterns rage037 */
    this->pattern_rage037_replayinterface = _xor_("48 8B 05 ? ? ? ? 48 8B 1C C8 48 85 DB 0F 84 ? ? ? ? 8B");
    this->pattern_rage037_nametags_setter = _xor_("88 0D ? ? ? ? C3");
    this->pattern_rage037_get_name = _xor_("0F B7 C2 48 C1 E0 05");
    this->pattern_rage037_get_name_verify = _xor_("48 83 EC 38 48 C7 44 24 ? ? ? ? ? 48 8B 05 ? ? ? ? 48 85 C0 75 1B 8D 48 08");
    
    this->pattern_rageshared_fetch_handler = _xor_("E8 ? ? ? ? 48 89 05 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? E9 ? ? ? ?");
}