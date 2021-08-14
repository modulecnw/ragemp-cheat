#pragma once

#include "singleton.hpp"
#include <imgui/imgui.h>
#define IMGUI_DEFINE_MATH_OPERATORS
#include <imgui/imgui_internal.h>

#include <Windows.h>
#include <winuser.h>
#include <string>

#include <ctime>
#include <time.h>

class c_menu_elements : public Singleton<c_menu_elements>
{
public:
	void draw_logo(ImVec2 pos, int sz, ImColor clr, const char* text);
	void tab(const char* label, int* value, int index);
	void subtab(const char* label, const char* icon, int* selected, int index, int width = 100);

	bool checkbox(const char* label, bool* value, const char* desc = "");
	bool checkbox(std::string label_str, bool* value, const char* desc = "");

	bool shared_item(const char* author, const char* name, const char* lastEdit);

	void beginchild(const char* label, ImVec2 size);
	void beginchild2(const char* label, ImVec2 size);
	void endchild();

	void beginsubchild(const char* label, ImVec2 size);
	void endsubchild();

	bool begincombo(const char* label, const char* preview_value, ImGuiComboFlags flags);

	bool combo(const char* label, int* current_item, const char* const items[], int items_count, int popup_max_height_in_items = -1);
	bool combo(const char* label, int* current_item, const char* items_separated_by_zeros, int popup_max_height_in_items = -1);
	bool combo(const char* label, int* current_item, bool(*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int popup_max_height_in_items = -1);

	bool slider_float(const char* label, float* v, float v_min, float v_max, const char* format = "%.0f", float power = 1);
	bool slider_int(const char* label, int* v, int v_min, int v_max, const char* format = NULL);

	void sameline(float offset_from_start_x = 0.0f, float spacing_w = -1.0f);

	bool key_bind(const char* label, int& k, const ImVec2& size_arg = ImVec2(230, 20));

	void create_styles();

	void create_decorations();

	bool button(std::string label_str, ImVec2 size_arg = { NULL, NULL }, ImGuiButtonFlags flags = NULL);
	bool button(const char* label, ImVec2 size_arg = { NULL, NULL }, ImGuiButtonFlags flags = NULL);
	void help_marker(const char* desc, bool sameline, float sl_d);

	ImFont* title = nullptr;
	ImFont* title_small = nullptr;

	ImU32 quick_lerp(ImVec4 from, ImVec4 to, float step);

	ImVec2 window_position;
	ImDrawList* draw_list;

	int window_tab = 1;

	int window_subtab_home = 0;
	int window_subtab_visuals = 0;
	int window_subtab_aimbot = 0;
	int window_subtab_misc = 1;
	int window_subtab_others = 0;
	int window_subtab_configs = 0;
};

#define imsl c_menu_elements::Instance().sameline();
#define imnl ImGui::NewLine();