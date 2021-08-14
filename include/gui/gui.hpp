#pragma once
#include "imports.hpp"

#include "gui/elements.h"
#include "gui/hashes.h"
#include "gui/sffont.hpp"
#include "gui/faprolight.hpp"

#include <future>
#include <fstream>
#include <chrono>
#include <filesystem>
#include <random>
namespace fs = std::filesystem;
using namespace std::chrono_literals;


class Gui : public Singleton<Gui>
{
public:
	ImFont* title = nullptr;
	ImFont* title_small = nullptr;

	ImVec2 window_position;
	ImDrawList* draw_list;

	int window_tab = 0;

	int window_subtab_home = 0;
	int window_subtab_visuals = 0;
	int window_subtab_aiming = 0;
	int window_subtab_misc = 0;
	int window_subtab_config = 0;
	int window_subtab_exec = 0;
	int window_subtab_admin = 0;

	bool init_style = true;

	bool theme = false;

	bool bMenuOpen = true;

	void create_styles();
	void create_decorations();
	void create_tabs();
	void create_items();

	void pre_init();
	void init();
};