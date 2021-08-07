#include "hooks/renderer.hpp"
#include "nemo.hpp"
#include "memory/memory.hpp"
#include "utils.hpp"
#include "gui/gui.hpp"

/* FONTS */
#include "fonts/font_itcavantgarde.hpp"

void Renderer::Render(IDXGISwapChain* this_swapchain_pointer, unsigned int sync_interval, unsigned int flags) {
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

	if (!bInitialized) {
		this_swapchain_pointer->GetDevice(__uuidof(this->pDevice), (void**)&this->pDevice);
		pDevice->GetImmediateContext(&this->pDeviceContext);

		ImGui::CreateContext();
		auto& io = ImGui::GetIO();
		
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

		#define create_font(size) io.Fonts->AddFontFromFileTTF(_xor_("C:/Windows/Fonts/ITCAvantGardeStdBk.otf").c_str(), size);
		Fonts::Instance().fITCAvant18 = create_font(18.f);

		ImGui::StyleColorsDark();
		/* styling here */

		ImGui_ImplWin32_Init(Nemo::Instance().hWindow);
		ImGui_ImplDX11_Init(this->pDevice, this->pDeviceContext);

		bInitialized = true;
	}

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

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

	if (Memory::Instance().ptr_gta_world != nullptr) {
		// client render
		ImGuiWindow* window = ImGui::GetCurrentWindow();

		window->DrawList->AddText(Fonts::Instance().fITCAvant18, 18.f, ImVec2(15, 15), ImColor(255,255,255), "nemo:V");
	}
	

	ImGui::End();
	ImGui::PopStyleVar(3);
	ImGui::PopStyleColor();

	ImGui::EndFrame();
	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}