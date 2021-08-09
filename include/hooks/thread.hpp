#pragma once
#include "imports.hpp"

using namespace std;
class Thread : public Singleton<Thread>
{
private:

public:
	void Call(game_thread* this_ptr, int ops_to_execute);
};
