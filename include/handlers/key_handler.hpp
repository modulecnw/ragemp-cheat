#pragma once
#include "imports.hpp"

using namespace std;
using key_func_t = void(*)();

class KeyHandler : public Singleton<KeyHandler>
{
public:
	struct key_binding {
		int m_vkey;
		key_func_t m_key_func;
		bool m_call_once;

		key_binding(int vkey, key_func_t key_func, bool call_once) :
			m_vkey(vkey),
			m_key_func(key_func),
			m_call_once(call_once)
		{ }
	};

	void add_keybind(key_binding key_bind) {
		this->key_binds.emplace_back(key_bind);
	}

	void trigger_keybinds() {
		for (key_binding& key_bind : key_binds) {
			if (GetAsyncKeyState(key_bind.m_vkey) & key_bind.m_call_once ? 0x1 : 0x8000)
				key_bind.m_key_func();
		}
	}

private:
	std::vector<key_binding> key_binds;
};