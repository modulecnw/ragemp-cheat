#pragma once
#include "imports.hpp"

//splitted into patterns class cause of xor string problems :'-(
using namespace std;
class Patterns : public Singleton<Patterns>
{
public:
    /* patterns gta */
    string pattern_gta_swapchain;
    string pattern_gta_world_factory;
    string pattern_gta_replay_interface;
    string pattern_gta_viewport;
    string pattern_gta_camera;
    string pattern_gta_world_to_screen;
    string pattern_gta_get_bone_position;
    string pattern_gta_script_thread_tick;
    string pattern_gta_fix_context_vector;
    string pattern_gta_fetch_native_handler;
    string pattern_gta_native_handler_table;
    string pattern_gta_pointer_to_handle;
    string pattern_gta_game_state;

    /* patterns rage037 */
    string pattern_rage037_replayinterface;
    string pattern_rage037_nametags_setter;
    string pattern_rage037_get_name;
    string pattern_rage037_get_name_verify;

    /* patterns rage11 */

    /* patterns rageshared */
    string pattern_rageshared_fetch_handler;

    // maybe here shared patterns?

    void Initialize();
};