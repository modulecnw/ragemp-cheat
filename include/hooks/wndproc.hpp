#pragma once
#include "imports.hpp"
#include "gui/gui.hpp"
#include "nemo.hpp"

class Wndproc : public Singleton<Wndproc>
{
public:
    LRESULT call_wndproc(HWND hwnd, unsigned int message_u, WPARAM param_w, LPARAM param_l);
};