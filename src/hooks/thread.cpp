#include "hooks/thread.hpp"
#include "gta/fiber.hpp"

void Thread::Call(game_thread* this_ptr, int ops_to_execute) {
	if (this_ptr->m_context.m_script_hash == 0x26FB4AB9 || this_ptr->m_context.m_script_hash == 1104607124 || this_ptr->m_context.m_script_hash == 3381724246)
	{
		auto& thread = game_thread::get();

		auto orig_thread = thread;

		thread = this_ptr;

		Fiber::Instance().s_game_fiber->on_tick();

		thread = orig_thread;
	}

}