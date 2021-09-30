#pragma once
#include "imports.hpp"
#include "nemo.hpp"

namespace utils
{
	namespace
	{
		struct handle_data
		{
			unsigned long process_id;
			HWND window_handle;
		};

		inline BOOL is_main_window(HWND handle)
		{
			return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);
		}

		inline BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam)
		{
			handle_data& data = *(handle_data*)lParam;
			unsigned long process_id = 0;
			GetWindowThreadProcessId(handle, &process_id);
			if (data.process_id != process_id || !is_main_window(handle))
				return TRUE;
			data.window_handle = handle;
			return FALSE;
		}
	}

	namespace render {
		static bool isInScreen(const ImVec2& from, const ImVec2& to) {
			if ((from.x >= 0) && (from.x <= (Nemo::Instance().vScreen.x)) & (from.y >= 0) & (from.y <= (Nemo::Instance().vScreen.y)))
			{
				if ((to.x >= 0) & (to.x <= (Nemo::Instance().vScreen.x)) & (to.y >= 0) & (to.y <= (Nemo::Instance().vScreen.y)))
				{
					return true;
				}
			}
			return false;
		}

		static auto draw_line = [](float x, float y, float x2, float y2, float r, float g, float b, float a, float thickness = 1.0f)
		{
			if (isInScreen({ x, y }, { x2, y2 }))
				ImGui::GetOverlayDrawList()->AddLine({ x, y }, { x2, y2 }, ImGui::GetColorU32({ r / 255, g / 255, b / 255, a / 255, }), thickness);
		};

		static auto draw_filled_rect = [](float x, float y, float x2, float y2, float r, float g, float b, float a, float rounding = 0.0f)
		{
			if (isInScreen({ x, y }, { x2, y2 }))

				ImGui::GetOverlayDrawList()->AddRectFilled({ x, y }, { x2, y2 }, ImGui::GetColorU32({ r / 255, g / 255, b / 255, a / 255, }), rounding);
		};

		static auto draw_filled_circle = [](float x, float y, float radius, float r = 255, float g = 255, float b = 255, float a = 255)
		{
			if (isInScreen({ x, y }, { x + radius, y + radius }))
				ImGui::GetOverlayDrawList()->AddCircleFilled({ x, y }, radius, ImGui::GetColorU32({ r / 255, g / 255, b / 255, a / 255 }));
		};

		static auto draw_circle = [](float x, float y, float radius, float r = 255, float g = 255, float b = 255, float a = 255)
		{
			if (isInScreen({ x, y }, { x + radius, y + radius }))
				ImGui::GetOverlayDrawList()->AddCircle({ x, y }, radius, ImGui::GetColorU32({ r / 255, g / 255, b / 255, a / 255 }));
		};

		static auto draw_rect = [](float x, float y, float x2, float y2, float r, float g, float b, float a, float rounding = 0.0f)
		{
			if (isInScreen({ x, y }, { x2, y2 }))
				ImGui::GetOverlayDrawList()->AddRect({ x, y }, { x2, y2 }, ImGui::GetColorU32({ r / 255, g / 255, b / 255, a / 255, }), rounding);
		};

		static auto draw_text = [](float x, float y, std::string_view string, float size = 14.f, float r = 255, float g = 255, float b = 255, float a = 255)
		{
			//TODO: add font resizing
			if (isInScreen({ x, y }, { x + size, y + size }))
				ImGui::GetOverlayDrawList()->AddText({ x, y }, ImGui::GetColorU32({ r / 255, g / 255, b / 255, a / 255, }), string.data());
		};
	}

	inline HWND find_main_window(unsigned long process_id)
	{
		handle_data data;
		data.process_id = process_id;
		data.window_handle = 0;
		EnumWindows(enum_windows_callback, (LPARAM)&data);
		return data.window_handle;
	}

	inline Vector2 get_widescreen_scale(float size)
	{
		return { (static_cast<float>(Nemo::Instance().vScreen.y) / static_cast<float>(Nemo::Instance().vScreen.x)) * size, size };
	}

	inline float get_width_scale(float width)
	{
#define default_width 1920
		return (width / default_width) * Nemo::Instance().vScreen.x;
	}

	inline float get_height_scale(float height)
	{
#define default_height 1080
		return (height / default_height) * Nemo::Instance().vScreen.y;
	}

	inline Vector2 get_screen_scale(float x, float y)
	{
		return { get_width_scale(x), get_height_scale(y) };
	}

	inline bool in_range(ImVec2 vec, ImVec2 start, ImVec2 end)
	{
		return vec.x >= start.x && vec.x < end.x&& vec.y >= start.y && vec.y < end.y;
	}


}