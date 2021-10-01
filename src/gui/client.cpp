#include "gui/client.hpp"
#include "utils.hpp"
#include "memory/memory.hpp"
#include "handlers/key_handler.hpp"
#include "hooks/hooks.hpp"
#include <hacks/visuals_player.hpp>
#include <hacks/aimbot.hpp>

void Client::Render() {
	utils::render::draw_text(15, 15, "nemo:V");

	KeyHandler::Instance().trigger_keybinds();

	VisualsPlayer::Instance().Tick();
	Aimbot::Instance().Tick();
}