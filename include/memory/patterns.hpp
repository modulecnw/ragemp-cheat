#pragma once
#include "imports.hpp"

//splitted into patterns class cause of xor string problems :'-(
using namespace std;
class Patterns : public Singleton<Patterns>
{
public:
    /* patterns gta */
    string pattern_gta_swapchain;
    string pattern_gta_world;
    string pattern_gta_viewport;

    /* patterns rage037 */
    string pattern_rage037_replayinterface;
    string pattern_rage037_nametags_setter;
    string pattern_rage037_get_name;
    string pattern_rage037_get_name_verify;

    /* patterns rage11 */

    /* patterns rageshared */
    // maybe here shared patterns?

    void Initialize();
};