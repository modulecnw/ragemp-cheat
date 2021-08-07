#pragma once
#include <windows.h>
#include <string>
#include <optional>
#include <vector>
#include <sstream>
#include <d3d11.h>
#include <functional>
#include <xmmintrin.h>
#include <iostream>
#include <thread>
#include <map>
#include <memory>

// d3d11 
#include <d3d11.h>
#include <D3Dcompiler.h>
#pragma comment(lib, "D3dcompiler.lib")
#pragma comment(lib, "d3d11.lib")

//imgui
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/imgui_impl_dx11.h>
#include <imgui/imgui_impl_win32.h>

// nlohmann
#include "nlohmann/json.hpp"

//alt
#include "alt/alt-log.hpp"
using namespace alt;

//ragemp
#include "ragemp/game.hpp"

//gta
#include "gta/game.hpp"

#include "singleton.hpp"
#include "xor.hpp"