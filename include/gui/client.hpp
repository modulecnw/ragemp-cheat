#pragma once
#include "imports.hpp"

class Client : public Singleton<Client>
{
public:
	void Render();
};