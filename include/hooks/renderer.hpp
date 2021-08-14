#pragma once
#include "imports.hpp"
#include "virtual-table.hpp"

using namespace std;
class Renderer : public Singleton<Renderer>
{
private:
	ID3D11Device* pDevice = NULL;
	ID3D11DeviceContext* pDeviceContext = NULL;

public:
	bool bInitialized = false;

	void Render(IDXGISwapChain* this_swapchain_pointer, unsigned int sync_interval, unsigned int flags);
};

class Fonts : public Singleton<Fonts>
{
public:
	ImFont* fITCAvant18 = nullptr;
};