#pragma once
#include "imports.hpp"

class Gui : public Singleton<Gui>
{
public:
	bool bMenuOpen = false;
};