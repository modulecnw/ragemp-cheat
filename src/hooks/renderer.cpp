#include "hooks/renderer.hpp"
#include "nemo.hpp"
#include "memory/memory.hpp"
#include "utils.hpp"
#include "gui/gui.hpp"
#include "gui/client.hpp"
#include "hooks/wndproc.hpp"

/* FONTS */
#include "fonts/font_itcavantgarde.hpp"

LRESULT call_wndproc(HWND hwnd, unsigned int message_u, WPARAM param_w, LPARAM param_l) {
	return Wndproc::Instance().call_wndproc(hwnd, message_u, param_w, param_l);
}

void Renderer::Render(IDXGISwapChain* this_swapchain_pointer, unsigned int sync_interval, unsigned int flags) {
	if (!bInitialized) {
		this_swapchain_pointer->GetDevice(__uuidof(pDevice), (void**)&pDevice);
		pDevice->GetImmediateContext(&pDeviceContext);

		ImGui::CreateContext();
		auto& io = ImGui::GetIO();

		DXGI_SWAP_CHAIN_DESC sd;
		this_swapchain_pointer->GetDesc(&sd);
		Nemo::Instance().hWindow = sd.OutputWindow;

		static const ImWchar ranges[] = {
			0x0020, 0x00FF, // Basic Latin + Latin Supplement
			0x2000, 0x206F, // General Punctuation
			0x3000, 0x30FF, // CJK Symbols and Punctuations, Hiragana, Katakana
			0x31F0, 0x31FF, // Katakana Phonetic Extensions
			0xFF00, 0xFFEF, // Half-width characters
			0x4e00, 0x9FAF, // CJK Ideograms
			0x0400, 0x052F, // Cyrillic + Cyrillic Supplement
			0x2DE0, 0x2DFF, // Cyrillic Extended-A
			0xA640, 0xA69F, // Cyrillic Extended-B
			0,
		};

		//#define create_font(bytes, byte_size, size) io.Fonts->AddFontFromMemoryCompressedTTF(bytes, byte_size, utils::get_height_scale(size), nullptr, ranges);
		//Fonts::Instance().fITCAvant18 = create_font(itc_avantgarde_font, sizeof(itc_avantgarde_font), 18.f);

		//#define create_font(size) io.Fonts->AddFontFromFileTTF(_xor_("C:/Windows/Fonts/ITCAvantGardeStdBk.otf").c_str(), size);
		//Fonts::Instance().fITCAvant18 = create_font(14.f);

		//ImGui::StyleColorsDark();
		/* styling here */
		Gui::Instance().pre_init();
		Gui::Instance().create_styles();

		ImGui_ImplWin32_Init(Nemo::Instance().hWindow);
		ImGui_ImplDX11_Init(pDevice, pDeviceContext);
		Nemo::Instance().wWndproc = reinterpret_cast<WNDPROC>(SetWindowLongPtrW(Nemo::Instance().hWindow, GWLP_WNDPROC, reinterpret_cast<long long>(call_wndproc)));

		bInitialized = true;
	}

	static uintptr_t pixel_refresh_clock = 0;
	if (GetTickCount64() - pixel_refresh_clock > 1000)
	{
		RECT rect;
		GetClientRect(Nemo::Instance().hWindow, &rect);
		int client_width = (rect.right - rect.left);
		int client_height = (rect.bottom - rect.top);

		Nemo::Instance().vScreen = { static_cast<float>(client_width), static_cast<float>(client_height) };

		pixel_refresh_clock = GetTickCount64();
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();
	Gui::Instance().init();

	if (Gui::Instance().bMenuOpen) {
		ImGui::GetIO().MouseDrawCursor = true;
		ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
	}
	else {
		ImGui::GetIO().MouseDrawCursor = false;
		ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouse;
	}

	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_Alpha, 1.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0.0f, 0.0f });
	ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.0f, 0.0f, 0.0f, 0.0f });
	ImGui::Begin("##ingame_hud", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoInputs);

	ImGui::SetWindowPos(ImVec2(0, 0), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y), ImGuiCond_Always);

	if (Memory::Instance().ptr_gta_world_factory != nullptr) {
		// client render
		Client::Instance().Render();
	}
	

	ImGui::End();
	ImGui::PopStyleVar(3);
	ImGui::PopStyleColor();

	ImGui::EndFrame();
	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}