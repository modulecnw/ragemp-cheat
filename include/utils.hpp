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