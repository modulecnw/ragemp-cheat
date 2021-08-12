#include "gui/client.hpp"
#include "utils.hpp"
#include "memory/memory.hpp"
#include <hacks/visuals_player.hpp>

void Client::Render() {
	//utils::render::draw_text(15, 15, "nemo:V");
	
	VisualsPlayer::Instance().Tick();
}