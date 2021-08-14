#include "gui/elements.h"
#include "hooks/hooks.hpp"

#include <iostream>

#define IMGUI_DEFINE_MATH_OPERATORS

void c_menu_elements::draw_logo(ImVec2 pos, int sz, ImColor clr, const char* text) {
	/*ImGui::GetWindowDrawList()->AddRectFilled(
		pos,
		{ pos.x + sz, pos.y + sz },
		clr,
		100,
		1 | 2 | 4
	);
	ImGui::GetWindowDrawList()->AddCircleFilled(
		{ pos.x + sz / 2, pos.y + sz / 2 },
		(sz + 1) / 2,
		clr,
		32
	);

	ImGui::GetWindowDrawList()->AddRectFilled(
		{ pos.x + float(sz / 5.9),  pos.y + float(sz / 5.9) },
		{ pos.x + sz - (sz / 5), pos.y + sz - (sz / 5) },
		ImGui::GetColorU32(ImGuiCol_WindowBg),
		100,
		1 | 2 | 4
	);*/

	ImGui::GetWindowDrawList()->AddText(pos, clr, text);
}

ImU32 c_menu_elements::quick_lerp(ImVec4 from, ImVec4 to, float step) {
	ImU32 _col = ImU32();
	if (ImGui::IsItemHovered())
		_col = ImGui::GetColorU32(ImLerp(from, to, step));
	else _col = ImGui::GetColorU32(ImLerp(from, to, step));

	return _col;
}

bool c_menu_elements::button(std::string label_str, ImVec2 size_arg, ImGuiButtonFlags flags)
{
	const char* label = label_str.c_str();

	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	if ((size_arg.x && size_arg.y) == 0)
		size_arg = ImVec2(150, 30);

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
	const float out_sz = 5;

	ImVec2 pos = window->DC.CursorPos;
	if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
		pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
	ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, pos + size);
	ImGui::ItemSize(size, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
		return false;

	if (window->DC.ItemFlags & ImGuiItemFlags_ButtonRepeat)
		flags |= ImGuiButtonFlags_Repeat;
	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);

	if (hovered)
		ImGui::SetMouseCursor(7);

	bool draw_outer = false;

	float t = draw_outer ? 1.0f : 0.0f;
	float ANIM_SPEED = 0.45f;
	if (g.LastActiveId == g.CurrentWindow->GetID(label)) {
		float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
		t = draw_outer ? (t_anim) : (1.0f - t_anim);
	}

	if (pressed)
		draw_outer = !draw_outer;

	if ((t >= 0))
		ImGui::GetWindowDrawList()->AddRectFilled(
			bb.Min - ImVec2(out_sz * (1 - t), out_sz * (1 - t)),
			bb.Max + ImVec2(out_sz * (1 - t), out_sz * (1 - t)),
			ImGui::GetColorU32(ImGuiCol_MainColorAccent, t),
			4.0f
		);

	const ImU32 col = ImGui::GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
	ImGui::RenderNavHighlight(bb, id);
	ImGui::RenderFrame(bb.Min, bb.Max, col, true, 4.f/*style.FrameRounding*/);
	ImGui::RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb);

	IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.LastItemStatusFlags);
	return pressed;
}

bool c_menu_elements::button(const char* label, ImVec2 size_arg, ImGuiButtonFlags flags)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	if ((size_arg.x && size_arg.y) == 0)
		size_arg = ImVec2(150, 30);

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
	const float out_sz = 5;

	ImVec2 pos = window->DC.CursorPos;
	if ((flags & ImGuiButtonFlags_AlignTextBaseLine) && style.FramePadding.y < window->DC.CurrLineTextBaseOffset) // Try to vertically align buttons that are smaller/have no padding so that text baseline matches (bit hacky, since it shouldn't be a flag)
		pos.y += window->DC.CurrLineTextBaseOffset - style.FramePadding.y;
	ImVec2 size = ImGui::CalcItemSize(size_arg, label_size.x + style.FramePadding.x * 2.0f, label_size.y + style.FramePadding.y * 2.0f);

	const ImRect bb(pos, pos + size);
	ImGui::ItemSize(size, style.FramePadding.y);
	if (!ImGui::ItemAdd(bb, id))
		return false;

	if (window->DC.ItemFlags & ImGuiItemFlags_ButtonRepeat)
		flags |= ImGuiButtonFlags_Repeat;
	bool hovered, held;
	bool pressed = ImGui::ButtonBehavior(bb, id, &hovered, &held, flags);

	if (hovered)
		ImGui::SetMouseCursor(7);

	bool draw_outer = false;

	float t = draw_outer ? 1.0f : 0.0f;
	float ANIM_SPEED = 0.45f;
	if (g.LastActiveId == g.CurrentWindow->GetID(label)) {
		float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
		t = draw_outer ? (t_anim) : (1.0f - t_anim);
	}

	if (pressed)
		draw_outer = !draw_outer;

	if ((t >= 0))
		ImGui::GetWindowDrawList()->AddRectFilled(
			bb.Min - ImVec2(out_sz * (1 - t), out_sz * (1 - t)),
			bb.Max + ImVec2(out_sz * (1 - t), out_sz * (1 - t)),
			ImGui::GetColorU32(ImGuiCol_MainColorAccent, t),
			4.0f
		);

	const ImU32 col = ImGui::GetColorU32((held && hovered) ? ImGuiCol_ButtonActive : hovered ? ImGuiCol_ButtonHovered : ImGuiCol_Button);
	ImGui::RenderNavHighlight(bb, id);
	ImGui::RenderFrame(bb.Min, bb.Max, col, true, 4.f/*style.FrameRounding*/);
	ImGui::RenderTextClipped(bb.Min + style.FramePadding, bb.Max - style.FramePadding, label, NULL, &label_size, style.ButtonTextAlign, &bb);

	IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.LastItemStatusFlags);
	return pressed;
}

void c_menu_elements::tab(const char* label, int* value, int index)
{
	ImGuiContext& g = *GImGui;
	ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
	const ImGuiStyle& style = g.Style;

	const ImRect total_bb = ImRect(p, p + ImVec2(22 + label_size.x, 39));

	ImGui::InvisibleButton(label, ImVec2(22 + label_size.x, 40));

	if (ImGui::IsItemClicked())
		*value = index;

	if (ImGui::IsItemHovered())
		ImGui::SetMouseCursor(7);

	float t = *value == index ? 1.0f : 0.0f;
	if (g.LastActiveId == g.CurrentWindow->GetID(label)) {
		float t_anim = ImSaturate(g.LastActiveIdTimer / 0.23f);
		t = *value == index ? (t_anim) : (1.0f - t_anim);
	}

	ImU32 col_bg = ImU32();
	col_bg =
		quick_lerp(ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_WindowBg)), ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_MainColorAccent)), t);

	ImU32 col_txt = ImU32();
	col_txt =
		quick_lerp(ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_TextDisabled)), ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_Text)), t);

	draw_list->AddRectFilled(total_bb.Min + ImVec2(0, 37), total_bb.Max, col_bg/*ImGui::GetColorU32(ImGuiCol_MainColorAccent, t)*/);
	draw_list->AddText(total_bb.Min + ImVec2(11, 12), col_txt/*ImGui::GetColorU32(ImGuiCol_Text, 0.45 + t)*/, label);
}

/*void c_menu_elements::subtab(const char* label, const char* icon, int* selected, int index, int width)
{
	ImGuiContext& g = *GImGui;
	ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
	const ImVec2 icon_size = ImGui::CalcTextSize(icon, NULL, true);
	const ImGuiStyle& style = g.Style;

	const ImRect total_bb = ImRect(p, p + ImVec2(width, 39));

	ImGui::InvisibleButton(label, ImVec2(width, 39));

	if (ImGui::IsItemHovered())
		ImGui::SetMouseCursor(7);

	if (ImGui::IsItemClicked())
		*selected = index;

	float t = *selected == index ? 1.0f : 0.0f;
	if (g.LastActiveId == g.CurrentWindow->GetID(label))
	{
		float t_anim = ImSaturate(g.LastActiveIdTimer / 0.23f);
		t = *selected == index ? (t_anim) : (1.0f - t_anim);
	}

	ImU32 col_bg = ImU32();
	col_bg =
		quick_lerp(ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_SubtabZoneBackground)), ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_SubtabActiveBackground)), t);

	ImU32 col_txt = ImU32();
	col_txt =
		quick_lerp(ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_TextDisabled)), ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_Text)), t);

	draw_list->AddRectFilled(
		total_bb.Min, total_bb.Max,
		col_bg);

	draw_list->AddText(total_bb.Min + ImVec2(width / 2 - icon_size.x / 2, 7), col_txt, icon);
	draw_list->AddText(total_bb.Min + ImVec2(width / 2 - label_size.x / 2, 22), col_txt, label);
}*/

bool c_menu_elements::checkbox(std::string label_str, bool* value, const char* desc)
{
	const char* label = label_str.c_str();
	bool result = false;

	ImGuiContext& g = *GImGui;
	ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	ImVec4 check_col_vec4 = ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_MainColorAccent));

	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
	const ImGuiStyle& style = g.Style;
	const float square_sz = ImGui::GetFrameHeight();
	const ImRect total_bb = ImRect(p, p + ImVec2(square_sz + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), label_size.y + style.FramePadding.y * 2.0f));
	const ImRect check_bb = ImRect(p, p + ImVec2(square_sz, square_sz));

	const float nGpad = ImMax(1.0f, IM_FLOOR(square_sz / 6.0f));
	float height = ImGui::GetFrameHeight();
	float width = height * 1.5 + label_size.x;
	const float radius = 7;

	ImGui::InvisibleButton(label, ImVec2(width, height));

	if (ImGui::IsItemClicked()) {
		*value = !*value;
		result = true;
	}

	float t = *value ? 1.0f : 0.0f;
	float ANIM_SPEED = 0.23f; // Bigger = Slower
	if (g.LastActiveId == g.CurrentWindow->GetID(label)) {
		float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
		t = *value ? (t_anim) : (1.0f - t_anim);
	}

	ImU32 col_bg;
	if (ImGui::IsItemHovered())
		col_bg = ImGui::GetColorU32(ImLerp(ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_FrameBgHovered)),
			ImVec4(check_col_vec4.x + 0.03f,
				check_col_vec4.y + 0.03f,
				check_col_vec4.z + 0.3f, t), t)),
		ImGui::SetMouseCursor(7);
	else col_bg = ImGui::GetColorU32(ImLerp(ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_FrameBgActive)),
		check_col_vec4, t));

	if (*value || (t != 0.f))
		draw_list->AddCircle(
			check_bb.Min + ImVec2(nGpad + radius + 2, nGpad + radius + 2),
			radius,
			col_bg,
			24,
			3.0 * t
		);

	draw_list->AddCircle(
		check_bb.Min + ImVec2(nGpad + radius + 2, nGpad + radius + 2),
		radius,
		col_bg,
		24,
		3.5 /*+ t*/
	);

	if (label_size.x > 0.0f)
		ImGui::RenderText(ImVec2(check_bb.Max.x + style.ItemInnerSpacing.x, check_bb.Min.y + style.FramePadding.y), label);

#ifdef DEBUG
	draw_list->AddText(ImVec2(check_bb.Max.x + style.ItemInnerSpacing.x + 100, check_bb.Min.y + style.FramePadding.y), ImColor(255, 255, 255), std::to_string(t).c_str());
#endif

	return result;
}

void c_menu_elements::subtab(const char* label, const char* icon, int* selected, int index, int width)
{
	ImGuiContext& g = *GImGui;
	ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
	const ImVec2 icon_size = ImGui::CalcTextSize(icon, NULL, true);
	const ImGuiStyle& style = g.Style;

	const ImRect total_bb = ImRect(p, p + ImVec2(width, 39));

	ImGui::InvisibleButton(label, ImVec2(width, 39));

	if (ImGui::IsItemHovered())
		ImGui::SetMouseCursor(7);

	if (ImGui::IsItemClicked())
		*selected = index;

	float t = *selected == index ? 1.0f : 0.0f;
	if (g.LastActiveId == g.CurrentWindow->GetID(label))
	{
		float t_anim = ImSaturate(g.LastActiveIdTimer / 0.23f);
		t = *selected == index ? (t_anim) : (1.0f - t_anim);
	}

	ImU32 col_bg = ImU32();
	col_bg =
		quick_lerp(ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_SubtabZoneBackground)), ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_SubtabActiveBackground)), t);

	ImU32 col_txt = ImU32();
	col_txt =
		quick_lerp(ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_TextDisabled)), ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_Text)), t);

	draw_list->AddRectFilled(
		total_bb.Min, total_bb.Max,
		col_bg);

	draw_list->AddText(total_bb.Min + ImVec2(width / 2 - icon_size.x / 2, 7 /* 11 */), col_txt, icon);
	draw_list->AddText(total_bb.Min + ImVec2(width / 2 - label_size.x / 2, 22), col_txt, label);
}

bool c_menu_elements::checkbox(const char* label, bool* value, const char* desc)
{
	bool result = false;

	ImGuiContext& g = *GImGui;
	ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	ImVec4 check_col_vec4 = ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_MainColorAccent));

	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
	const ImGuiStyle& style = g.Style;
	const float square_sz = ImGui::GetFrameHeight();
	const ImRect total_bb = ImRect(p, p + ImVec2(square_sz + (label_size.x > 0.0f ? style.ItemInnerSpacing.x + label_size.x : 0.0f), label_size.y + style.FramePadding.y * 2.0f));
	const ImRect check_bb = ImRect(p, p + ImVec2(square_sz, square_sz));

	const float nGpad = ImMax(1.0f, IM_FLOOR(square_sz / 6.0f));
	float height = ImGui::GetFrameHeight();
	float width = height * 1.5 + label_size.x;
	const float radius = 7;

	ImGui::InvisibleButton(label, ImVec2(width, height));

	if (ImGui::IsItemClicked()){
		*value = !*value;
		result = true;
	}

	float t = *value ? 1.0f : 0.0f;
	float ANIM_SPEED = 0.23f; // Bigger = Slower
	if (g.LastActiveId == g.CurrentWindow->GetID(label)) {
		float t_anim = ImSaturate(g.LastActiveIdTimer / ANIM_SPEED);
		t = *value ? (t_anim) : (1.0f - t_anim);
	}

	ImU32 col_bg;
	if (ImGui::IsItemHovered())
		col_bg = ImGui::GetColorU32(ImLerp(ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_FrameBgHovered)),
			ImVec4(check_col_vec4.x + 0.03f,
				check_col_vec4.y + 0.03f,
				check_col_vec4.z + 0.3f, t), t)),
		ImGui::SetMouseCursor(7);
	else col_bg = ImGui::GetColorU32(ImLerp(ImGui::ColorConvertU32ToFloat4(ImGui::GetColorU32(ImGuiCol_FrameBgActive)),
		check_col_vec4, t));

	if (*value || (t != 0.f))
		draw_list->AddCircle(
			check_bb.Min + ImVec2(nGpad + radius + 2, nGpad + radius + 2),
			radius,
			col_bg,
			24,
			3.0 * t
		);

	draw_list->AddCircle(
		check_bb.Min + ImVec2(nGpad + radius + 2, nGpad + radius + 2),
		radius,
		col_bg,
		24,
		3.5 /*+ t*/
	);

	if (label_size.x > 0.0f)
		ImGui::RenderText(ImVec2(check_bb.Max.x + style.ItemInnerSpacing.x, check_bb.Min.y + style.FramePadding.y), label);

#ifdef DEBUG
	draw_list->AddText(ImVec2(check_bb.Max.x + style.ItemInnerSpacing.x + 100, check_bb.Min.y + style.FramePadding.y), ImColor(255, 255, 255), std::to_string(t).c_str());
#endif

	return result;
}

bool c_menu_elements::shared_item(const char* author, const char* name, const char* lastEdit)
{
	ImGuiContext& g = *GImGui;
	ImVec2 p = ImGui::GetCursorScreenPos();
	ImDrawList* draw_list = ImGui::GetWindowDrawList();

	const ImGuiStyle& style = g.Style;
	const ImRect total_bb = ImRect(p, p + ImVec2(560, 90));

	ImGui::InvisibleButton(name, ImVec2(560, 90));

	draw_list->AddRectFilled(total_bb.Min, total_bb.Max, ImGui::GetColorU32(ImGuiCol_NetworkingItemBg), 4);

	draw_logo(total_bb.Min + ImVec2(25, 30), 30, ImGui::GetColorU32(ImGuiCol_MainColorAccent), (const char*)"p");
	draw_list->AddText(total_bb.Min + ImVec2(100, 10), ImGui::GetColorU32(ImGuiCol_Text), name);
	//draw_list->AddText(total_bb.Max - ImVec2(20 + ImGui::CalcTextSize(std::string("#").append(id).c_str()).x, 80), ImGui::GetColorU32(ImGuiCol_Text), std::string("#").append(id).c_str());
	draw_list->AddText(total_bb.Min + ImVec2(100, 25), ImGui::GetColorU32(ImGuiCol_TextDisabled), std::string("Last edited at ").append(lastEdit).c_str());
	//draw_list->AddText(total_bb.Min + ImVec2(100, 65), ImGui::GetColorU32(ImGuiCol_TextDisabled), std::string("By ").append(author).c_str());

	draw_list->AddRectFilled(total_bb.Max - ImVec2(150, 33), total_bb.Max - ImVec2(20, 13), ImGui::GetColorU32(ImGuiCol_MainColorAccent), 4);
	draw_list->AddText(total_bb.Max - ImVec2(85 + ImGui::CalcTextSize("Click to load").x / 2, 31), ImColor(255, 255, 255, 255), "Click to load");

	return ImGui::IsItemClicked();
}

void c_menu_elements::beginchild(const char* label, ImVec2 size)
{
	ImGui::BeginChild(label, size);
	ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetWindowPos(), ImGui::GetWindowPos() + size, ImGui::GetColorU32(ImGuiCol_ChildBg), 6);
}

void c_menu_elements::beginchild2(const char* label, ImVec2 size)
{
	ImGui::BeginChild(label, size, false, ImGuiWindowFlags_HorizontalScrollbar);
	ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetWindowPos(), ImGui::GetWindowPos() + size, ImGui::GetColorU32(ImGuiCol_ChildBg), 6);
}

void c_menu_elements::endchild()
{
	ImGui::EndChild();
}

void c_menu_elements::beginsubchild(const char* label, ImVec2 size)
{
	ImGui::BeginChild(label, size);
	ImGui::GetWindowDrawList()->AddRectFilled(ImGui::GetWindowPos(), ImGui::GetWindowPos() + size, ImGui::GetColorU32(ImGuiCol_FrameBg), 6);
}

void c_menu_elements::endsubchild()
{
	ImGui::EndChild();
}

static float CalcMaxPopupHeightFromItemCount(int items_count)
{
	ImGuiContext& g = *GImGui;
	if (items_count <= 0)
		return FLT_MAX;
	return (g.FontSize + g.Style.ItemSpacing.y) * items_count - g.Style.ItemSpacing.y + (g.Style.WindowPadding.y * 2);
}

bool c_menu_elements::begincombo(const char* label, const char* preview_value, ImGuiComboFlags flags)
{
	using namespace ImGui;

	ImGuiContext& g = *GImGui;
	bool has_window_size_constraint = (g.NextWindowData.Flags & ImGuiNextWindowDataFlags_HasSizeConstraint) != 0;
	g.NextWindowData.Flags &= ~ImGuiNextWindowDataFlags_HasSizeConstraint;

	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	IM_ASSERT((flags & (ImGuiComboFlags_NoArrowButton | ImGuiComboFlags_NoPreview)) != (ImGuiComboFlags_NoArrowButton | ImGuiComboFlags_NoPreview));

	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);

	const float arrow_size = (flags & ImGuiComboFlags_NoArrowButton) ? 0.0f : GetFrameHeight();
	const ImVec2 label_size = CalcTextSize(label, NULL, true);
	const float expected_w = ImGui::GetWindowSize().x - 22;
	const float w = (flags & ImGuiComboFlags_NoPreview) ? expected_w : expected_w;
	const ImRect frame_bb(window->DC.CursorPos + ImVec2(3, 15), window->DC.CursorPos + ImVec2(w, label_size.y + style.FramePadding.y * 2.0f + 15));
	const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(0.0f, 20));
	ItemSize(total_bb, style.FramePadding.y);
	if (!ItemAdd(total_bb, id, &frame_bb))
		return false;

	bool hovered, held;
	bool pressed = ButtonBehavior(frame_bb, id, &hovered, &held);
	bool popup_open = IsPopupOpen(id);

	const ImU32 frame_col = GetColorU32(hovered ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);
	const float value_x2 = ImMax(frame_bb.Min.x, frame_bb.Max.x - arrow_size);

	window->DrawList->AddRectFilled(frame_bb.Min, frame_bb.Max, ImGui::GetColorU32(ImGuiCol_ComboBg), 3);
	window->DrawList->AddRect(frame_bb.Min, frame_bb.Max, ImColor(90, 90, 90, 150), 3);


	window->DrawList->AddText(frame_bb.Min + style.FramePadding, ImGui::GetColorU32(ImGuiCol_Text), preview_value);

	if (label_size.x > 0)
		window->DrawList->AddText(ImVec2(frame_bb.Min.x, frame_bb.Min.y - 18), ImGui::GetColorU32(ImGuiCol_Text), label);

	if ((pressed || g.NavActivateId == id) && !popup_open)
	{
		if (window->DC.NavLayerCurrent == 0)
			window->NavLastIds[0] = id;
		OpenPopupEx(id);
		popup_open = true;
	}

	if (!popup_open)
		return false;

	if (has_window_size_constraint)
	{
		g.NextWindowData.Flags |= ImGuiNextWindowDataFlags_HasSizeConstraint;
		g.NextWindowData.SizeConstraintRect.Min.x = ImMax(g.NextWindowData.SizeConstraintRect.Min.x, w);
	}
	else
	{
		if ((flags & ImGuiComboFlags_HeightMask_) == 0)
			flags |= ImGuiComboFlags_HeightRegular;
		IM_ASSERT(ImIsPowerOfTwo(flags & ImGuiComboFlags_HeightMask_));    // Only one
		int popup_max_height_in_items = -1;
		if (flags & ImGuiComboFlags_HeightRegular)     popup_max_height_in_items = 8;
		else if (flags & ImGuiComboFlags_HeightSmall)  popup_max_height_in_items = 4;
		else if (flags & ImGuiComboFlags_HeightLarge)  popup_max_height_in_items = 20;
		SetNextWindowSizeConstraints(ImVec2(w - 3, 0.0f), ImVec2(FLT_MAX, CalcMaxPopupHeightFromItemCount(popup_max_height_in_items)));
	}

	char name[16];
	ImFormatString(name, IM_ARRAYSIZE(name), "##Combo_%02d", g.BeginPopupStack.Size);

	if (ImGuiWindow* popup_window = FindWindowByName(name))
		if (popup_window->WasActive)
		{
			ImVec2 size_expected = CalcWindowExpectedSize(popup_window);
			if (flags & ImGuiComboFlags_PopupAlignLeft)
				popup_window->AutoPosLastDirection = ImGuiDir_Left;
			ImRect r_outer = GetWindowAllowedExtentRect(popup_window);
			ImVec2 pos = FindBestWindowPosForPopupEx(frame_bb.GetBL(), size_expected, &popup_window->AutoPosLastDirection, r_outer, frame_bb, ImGuiPopupPositionPolicy_ComboBox);
			SetNextWindowPos(pos + ImVec2(0, 5));
		}

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_Popup | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoMove;

	PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(style.FramePadding.x, style.WindowPadding.y));
	bool ret = Begin(name, NULL, window_flags);
	PopStyleVar();
	if (!ret)
	{
		EndPopup();
		IM_ASSERT(0);
		return false;
	}
	return true;
}

inline static bool Items_ArrayGetter(void* data, int idx, const char** out_text)
{
	const char* const* items = (const char* const*)data;
	if (out_text)
		*out_text = items[idx];
	return true;
}

inline static bool Items_SingleStringGetter(void* data, int idx, const char** out_text)
{
	const char* items_separated_by_zeros = (const char*)data;
	int items_count = 0;
	const char* p = items_separated_by_zeros;
	while (*p)
	{
		if (idx == items_count)
			break;
		p += strlen(p) + 1;
		items_count++;
	}
	if (!*p)
		return false;
	if (out_text)
		*out_text = p;
	return true;
}

bool c_menu_elements::combo(const char* label, int* current_item, bool (*items_getter)(void*, int, const char**), void* data, int items_count, int popup_max_height_in_items)
{
	ImGuiContext& g = *GImGui;

	// Call the getter to obtain the preview string which is a parameter to BeginCombo()
	const char* preview_value = NULL;
	if (*current_item >= 0 && *current_item < items_count)
		items_getter(data, *current_item, &preview_value);

	// The old Combo() API exposed "popup_max_height_in_items". The new more general BeginCombo() API doesn't have/need it, but we emulate it here.
	if (popup_max_height_in_items != -1 && !(g.NextWindowData.Flags & ImGuiNextWindowDataFlags_HasSizeConstraint))
		ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0), ImVec2(FLT_MAX, CalcMaxPopupHeightFromItemCount(popup_max_height_in_items)));

	if (!begincombo(label, preview_value, ImGuiComboFlags_None))
		return false;

	bool value_changed = false;
	for (int i = 0; i < items_count; i++)
	{
		ImGui::PushID((void*)(intptr_t)i);
		const bool item_selected = (i == *current_item);
		const char* item_text;
		if (!items_getter(data, i, &item_text))
			item_text = "*Unknown item*";
		if (ImGui::Selectable(item_text, item_selected))
		{
			value_changed = true;
			*current_item = i;
		}
		if (item_selected)
			ImGui::SetItemDefaultFocus();
		ImGui::PopID();
	}

	ImGui::EndPopup();
	return value_changed;
}

bool c_menu_elements::combo(const char* label, int* current_item, const char* const items[], int items_count, int height_in_items)
{
	const bool value_changed = combo(label, current_item, Items_ArrayGetter, (void*)items, items_count, height_in_items);
	return value_changed;
}

bool c_menu_elements::combo(const char* label, int* current_item, const char* items_separated_by_zeros, int height_in_items)
{
	int items_count = 0;
	const char* p = items_separated_by_zeros;
	while (*p)
	{
		p += strlen(p) + 1;
		items_count++;
	}
	bool value_changed = combo(label, current_item, Items_SingleStringGetter, (void*)items_separated_by_zeros, items_count, height_in_items);
	return value_changed;
}

namespace vars
{
	static const signed char    IM_S8_MIN = -128;
	static const signed char    IM_S8_MAX = 127;
	static const unsigned char  IM_U8_MIN = 0;
	static const unsigned char  IM_U8_MAX = 0xFF;
	static const signed short   IM_S16_MIN = -32768;
	static const signed short   IM_S16_MAX = 32767;
	static const unsigned short IM_U16_MIN = 0;
	static const unsigned short IM_U16_MAX = 0xFFFF;
	static const ImS32          IM_S32_MIN = INT_MIN;
	static const ImS32          IM_S32_MAX = INT_MAX;
	static const ImU32          IM_U32_MIN = 0;
	static const ImU32          IM_U32_MAX = UINT_MAX;
#ifdef LLONG_MIN
	static const ImS64          IM_S64_MIN = LLONG_MIN;
	static const ImS64          IM_S64_MAX = LLONG_MAX;
#else
	static const ImS64          IM_S64_MIN = -9223372036854775807LL - 1;
	static const ImS64          IM_S64_MAX = 9223372036854775807LL;
#endif
	static const ImU64          IM_U64_MIN = 0;
#ifdef ULLONG_MAX
	static const ImU64          IM_U64_MAX = ULLONG_MAX;
#else
	static const ImU64          IM_U64_MAX = (2ULL * 9223372036854775807LL + 1);
#endif

	struct ImGuiDataTypeInfo
	{
		size_t      Size;
		const char* PrintFmt;   // Unused
		const char* ScanFmt;
	};

	static const ImGuiDataTypeInfo GDataTypeInfo[] =
	{
		{ sizeof(int),          "%d",   "%d"    },
		{ sizeof(unsigned int), "%u",   "%u"    },
	#ifdef _MSC_VER
		{ sizeof(ImS64),        "%I64d","%I64d" },
		{ sizeof(ImU64),        "%I64u","%I64u" },
	#else
		{ sizeof(ImS64),        "%lld", "%lld"  },
		{ sizeof(ImU64),        "%llu", "%llu"  },
	#endif
		{ sizeof(float),        "%f",   "%f"    },  // float are promoted to double in va_arg
		{ sizeof(double),       "%f",   "%lf"   },
	};
}

template<typename TYPE, typename FLOATTYPE>
float slider_calc_ratio_from_value_t(ImGuiDataType data_type, TYPE v, TYPE v_min, TYPE v_max, float power, float linear_zero_pos)
{
	using namespace ImGui;

	if (v_min == v_max)
		return 0.0f;

	const bool is_power = (power != 1.0f) && (data_type == ImGuiDataType_Float || data_type == ImGuiDataType_Double);
	const TYPE v_clamped = (v_min < v_max) ? ImClamp(v, v_min, v_max) : ImClamp(v, v_max, v_min);
	if (is_power)
	{
		if (v_clamped < 0.0f)
		{
			const float f = 1.0f - (float)((v_clamped - v_min) / (ImMin((TYPE)0, v_max) - v_min));
			return (1.0f - ImPow(f, 1.0f / power)) * linear_zero_pos;
		}
		else
		{
			const float f = (float)((v_clamped - ImMax((TYPE)0, v_min)) / (v_max - ImMax((TYPE)0, v_min)));
			return linear_zero_pos + ImPow(f, 1.0f / power) * (1.0f - linear_zero_pos);
		}
	}

	// Linear slider
	return (float)((FLOATTYPE)(v_clamped - v_min) / (FLOATTYPE)(v_max - v_min));
}

// FIXME: Move some of the code into SliderBehavior(). Current responsability is larger than what the equivalent DragBehaviorT<> does, we also do some rendering, etc.
template<typename TYPE, typename SIGNEDTYPE, typename FLOATTYPE>
bool sliderbehaviort(const ImRect& bb, ImGuiID id, ImGuiDataType data_type, TYPE* v, const TYPE v_min, const TYPE v_max, const char* format, float power, ImGuiSliderFlags flags, ImRect* out_grab_bb)
{
	using namespace ImGui;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;

	const ImGuiAxis axis = (flags & ImGuiSliderFlags_Vertical) ? ImGuiAxis_Y : ImGuiAxis_X;
	const bool is_decimal = (data_type == ImGuiDataType_Float) || (data_type == ImGuiDataType_Double);
	const bool is_power = (power != 1.0f) && is_decimal;

	const float grab_padding = 2.0f;
	const float slider_sz = (bb.Max[axis] - bb.Min[axis]) - grab_padding * 2.0f;
	float grab_sz = style.GrabMinSize;
	SIGNEDTYPE v_range = (v_min < v_max ? v_max - v_min : v_min - v_max);
	if (!is_decimal && v_range >= 0)                                             // v_range < 0 may happen on integer overflows
		grab_sz = ImMax((float)(slider_sz / (v_range + 1)), style.GrabMinSize);  // For integer sliders: if possible have the grab size represent 1 unit
	grab_sz = ImMin(grab_sz, slider_sz);
	const float slider_usable_sz = slider_sz - grab_sz;
	const float slider_usable_pos_min = bb.Min[axis] + grab_padding + grab_sz * 0.5f;
	const float slider_usable_pos_max = bb.Max[axis] - grab_padding - grab_sz * 0.5f;

	// For power curve sliders that cross over sign boundary we want the curve to be symmetric around 0.0f
	float linear_zero_pos;   // 0.0->1.0f
	if (is_power && v_min * v_max < 0.0f)
	{
		// Different sign
		const FLOATTYPE linear_dist_min_to_0 = ImPow(v_min >= 0 ? (FLOATTYPE)v_min : -(FLOATTYPE)v_min, (FLOATTYPE)1.0f / power);
		const FLOATTYPE linear_dist_max_to_0 = ImPow(v_max >= 0 ? (FLOATTYPE)v_max : -(FLOATTYPE)v_max, (FLOATTYPE)1.0f / power);
		linear_zero_pos = (float)(linear_dist_min_to_0 / (linear_dist_min_to_0 + linear_dist_max_to_0));
	}
	else
	{
		// Same sign
		linear_zero_pos = v_min < 0.0f ? 1.0f : 0.0f;
	}

	// Process interacting with the slider
	bool value_changed = false;
	if (g.ActiveId == id)
	{
		bool set_new_value = false;
		float clicked_t = 0.0f;
		if (g.ActiveIdSource == ImGuiInputSource_Mouse)
		{
			if (!g.IO.MouseDown[0])
			{
				ClearActiveID();
			}
			else
			{
				const float mouse_abs_pos = g.IO.MousePos[axis];
				clicked_t = (slider_usable_sz > 0.0f) ? ImClamp((mouse_abs_pos - slider_usable_pos_min) / slider_usable_sz, 0.0f, 1.0f) : 0.0f;
				if (axis == ImGuiAxis_Y)
					clicked_t = 1.0f - clicked_t;
				set_new_value = true;
			}
		}
		else if (g.ActiveIdSource == ImGuiInputSource_Nav)
		{
			const ImVec2 delta2 = GetNavInputAmount2d(ImGuiNavDirSourceFlags_Keyboard | ImGuiNavDirSourceFlags_PadDPad, ImGuiInputReadMode_RepeatFast, 0.0f, 0.0f);
			float delta = (axis == ImGuiAxis_X) ? delta2.x : -delta2.y;
			if (g.NavActivatePressedId == id && !g.ActiveIdIsJustActivated)
			{
				ClearActiveID();
			}
			else if (delta != 0.0f)
			{
				clicked_t = slider_calc_ratio_from_value_t<TYPE, FLOATTYPE>(data_type, *v, v_min, v_max, power, linear_zero_pos);
				const int decimal_precision = is_decimal ? ImParseFormatPrecision(format, 3) : 0;
				if ((decimal_precision > 0) || is_power)
				{
					delta /= 100.0f;    // Gamepad/keyboard tweak speeds in % of slider bounds
					if (IsNavInputDown(ImGuiNavInput_TweakSlow))
						delta /= 10.0f;
				}
				else
				{
					if ((v_range >= -100.0f && v_range <= 100.0f) || IsNavInputDown(ImGuiNavInput_TweakSlow))
						delta = ((delta < 0.0f) ? -1.0f : +1.0f) / (float)v_range; // Gamepad/keyboard tweak speeds in integer steps
					else
						delta /= 100.0f;
				}
				if (IsNavInputDown(ImGuiNavInput_TweakFast))
					delta *= 10.0f;
				set_new_value = true;
				if ((clicked_t >= 1.0f && delta > 0.0f) || (clicked_t <= 0.0f && delta < 0.0f)) // This is to avoid applying the saturation when already past the limits
					set_new_value = false;
				else
					clicked_t = ImSaturate(clicked_t + delta);
			}
		}

		if (set_new_value)
		{
			TYPE v_new;
			if (is_power)
			{
				// Account for power curve scale on both sides of the zero
				if (clicked_t < linear_zero_pos)
				{
					// Negative: rescale to the negative range before powering
					float a = 1.0f - (clicked_t / linear_zero_pos);
					a = ImPow(a, power);
					v_new = ImLerp(ImMin(v_max, (TYPE)0), v_min, a);
				}
				else
				{
					// Positive: rescale to the positive range before powering
					float a;
					if (ImFabs(linear_zero_pos - 1.0f) > 1.e-6f)
						a = (clicked_t - linear_zero_pos) / (1.0f - linear_zero_pos);
					else
						a = clicked_t;
					a = ImPow(a, power);
					v_new = ImLerp(ImMax(v_min, (TYPE)0), v_max, a);
				}
			}
			else
			{
				// Linear slider
				if (is_decimal)
				{
					v_new = ImLerp(v_min, v_max, clicked_t);
				}
				else
				{
					// For integer values we want the clicking position to match the grab box so we round above
					// This code is carefully tuned to work with large values (e.g. high ranges of U64) while preserving this property..
					FLOATTYPE v_new_off_f = (v_max - v_min) * clicked_t;
					TYPE v_new_off_floor = (TYPE)(v_new_off_f);
					TYPE v_new_off_round = (TYPE)(v_new_off_f + (FLOATTYPE)0.5);
					if (!is_decimal && v_new_off_floor < v_new_off_round)
						v_new = v_min + v_new_off_round;
					else
						v_new = v_min + v_new_off_floor;
				}
			}

			// Round to user desired precision based on format string
			v_new = RoundScalarWithFormatT<TYPE, SIGNEDTYPE>(format, data_type, v_new);

			// Apply result
			if (*v != v_new)
			{
				*v = v_new;
				value_changed = true;
			}
		}
	}

	// Output grab position so it can be displayed by the caller
	float grab_t = SliderCalcRatioFromValueT<TYPE, FLOATTYPE>(data_type, *v, v_min, v_max, power, linear_zero_pos);
	if (axis == ImGuiAxis_Y)
		grab_t = 1.0f - grab_t;
	const float grab_pos = ImLerp(slider_usable_pos_min, slider_usable_pos_max, grab_t);
	if (axis == ImGuiAxis_X)
		*out_grab_bb = ImRect(grab_pos - grab_sz * 0.5f, bb.Min.y + grab_padding, grab_pos + grab_sz * 0.5f, bb.Max.y - grab_padding);
	else
		*out_grab_bb = ImRect(bb.Min.x + grab_padding, grab_pos - grab_sz * 0.5f, bb.Max.x - grab_padding, grab_pos + grab_sz * 0.5f);

	return value_changed;
}

// For 32-bits and larger types, slider bounds are limited to half the natural type range.
// So e.g. an integer Slider between INT_MAX-10 and INT_MAX will fail, but an integer Slider between INT_MAX/2-10 and INT_MAX/2 will be ok.
// It would be possible to lift that limitation with some work but it doesn't seem to be worth it for sliders.
bool sliderbehavior(const ImRect& bb, ImGuiID id, ImGuiDataType data_type, void* v, const void* v_min, const void* v_max, const char* format, float power, ImGuiSliderFlags flags, ImRect* out_grab_bb)
{
	switch (data_type)
	{
	case ImGuiDataType_S32:
		IM_ASSERT(*(const ImS32*)v_min >= vars::IM_S32_MIN / 2 && *(const ImS32*)v_max <= vars::IM_S32_MAX / 2);
		return sliderbehaviort<ImS32, ImS32, float >(bb, id, data_type, (ImS32*)v, *(const ImS32*)v_min, *(const ImS32*)v_max, format, power, flags, out_grab_bb);
	case ImGuiDataType_U32:
		IM_ASSERT(*(const ImU32*)v_min <= vars::IM_U32_MAX / 2);
		return sliderbehaviort<ImU32, ImS32, float >(bb, id, data_type, (ImU32*)v, *(const ImU32*)v_min, *(const ImU32*)v_max, format, power, flags, out_grab_bb);
	case ImGuiDataType_S64:
		IM_ASSERT(*(const ImS64*)v_min >= vars::IM_S64_MIN / 2 && *(const ImS64*)v_max <= vars::IM_S64_MAX / 2);
		return sliderbehaviort<ImS64, ImS64, double>(bb, id, data_type, (ImS64*)v, *(const ImS64*)v_min, *(const ImS64*)v_max, format, power, flags, out_grab_bb);
	case ImGuiDataType_U64:
		IM_ASSERT(*(const ImU64*)v_min <= vars::IM_U64_MAX / 2);
		return sliderbehaviort<ImU64, ImS64, double>(bb, id, data_type, (ImU64*)v, *(const ImU64*)v_min, *(const ImU64*)v_max, format, power, flags, out_grab_bb);
	case ImGuiDataType_Float:
		IM_ASSERT(*(const float*)v_min >= -FLT_MAX / 2.0f && *(const float*)v_max <= FLT_MAX / 2.0f);
		return sliderbehaviort<float, float, float >(bb, id, data_type, (float*)v, *(const float*)v_min, *(const float*)v_max, format, power, flags, out_grab_bb);
	case ImGuiDataType_Double:
		IM_ASSERT(*(const double*)v_min >= -DBL_MAX / 2.0f && *(const double*)v_max <= DBL_MAX / 2.0f);
		return sliderbehaviort<double, double, double>(bb, id, data_type, (double*)v, *(const double*)v_min, *(const double*)v_max, format, power, flags, out_grab_bb);
	case ImGuiDataType_COUNT: break;
	}
	IM_ASSERT(0);
	return false;
}

static const char* PatchFormatStringFloatToInt(const char* fmt)
{
	if (fmt[0] == '%' && fmt[1] == '.' && fmt[2] == '0' && fmt[3] == 'f' && fmt[4] == 0) // Fast legacy path for "%.0f" which is expected to be the most common case.
		return "%d";
	const char* fmt_start = ImParseFormatFindStart(fmt);    // Find % (if any, and ignore %%)
	const char* fmt_end = ImParseFormatFindEnd(fmt_start);  // Find end of format specifier, which itself is an exercise of confidence/recklessness (because snprintf is dependent on libc or user).
	if (fmt_end > fmt_start && fmt_end[-1] == 'f')
	{
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
		if (fmt_start == fmt && fmt_end[0] == 0)
			return "%d";
		ImGuiContext& g = *GImGui;
		ImFormatString(g.TempBuffer, IM_ARRAYSIZE(g.TempBuffer), "%.*s%%d%s", (int)(fmt_start - fmt), fmt, fmt_end); // Honor leading and trailing decorations, but lose alignment/precision.
		return g.TempBuffer;
#else
		IM_ASSERT(0 && "DragInt(): Invalid format string!"); // Old versions used a default parameter of "%.0f", please replace with e.g. "%d"
#endif
	}
	return fmt;
}

static int DataTypeFormatString1(char* buf, int buf_size, ImGuiDataType data_type, const void* data_ptr, const char* format)
{
	if (data_type == ImGuiDataType_S32 || data_type == ImGuiDataType_U32)   // Signedness doesn't matter when pushing the argument
		return ImFormatString(buf, buf_size, format, *(const ImU32*)data_ptr);
	if (data_type == ImGuiDataType_S64 || data_type == ImGuiDataType_U64)   // Signedness doesn't matter when pushing the argument
		return ImFormatString(buf, buf_size, format, *(const ImU64*)data_ptr);
	if (data_type == ImGuiDataType_Float)
		return ImFormatString(buf, buf_size, format, *(const float*)data_ptr);
	if (data_type == ImGuiDataType_Double)
		return ImFormatString(buf, buf_size, format, *(const double*)data_ptr);
	IM_ASSERT(0);
	return 0;
}

void c_menu_elements::help_marker(const char* desc, bool sameline, float sl_d) {
	if (sameline)
		ImGui::SameLine(0.f, sl_d == 0 ? 1.f : sl_d);

	ImGui::TextDisabled((const char*)" " "\uf059" " ");

	ImDrawList* draw_list = ImGui::GetOverlayDrawList();
	ImVec2 cur_pos = ImGui::GetIO().MousePos;
	const ImVec2 label_sz = ImGui::CalcTextSize(desc, NULL, true, 0.f);
	ImVec2 textpos = { cur_pos.x + label_sz.x / 2, cur_pos.y + label_sz.y / 2 };

	if (ImGui::IsItemHovered())
		draw_list->AddText(textpos, ImColor(255, 255, 255), desc, NULL);
}

static const ImGuiDataTypeInfo GDataTypeInfo[] =
{
	{ sizeof(char),             "%d",   "%d"    },  // ImGuiDataType_S8
	{ sizeof(unsigned char),    "%u",   "%u"    },
	{ sizeof(short),            "%d",   "%d"    },  // ImGuiDataType_S16
	{ sizeof(unsigned short),   "%u",   "%u"    },
	{ sizeof(int),              "%d",   "%d"    },  // ImGuiDataType_S32
	{ sizeof(unsigned int),     "%u",   "%u"    },
#ifdef _MSC_VER
	{ sizeof(ImS64),            "%I64d","%I64d" },  // ImGuiDataType_S64
	{ sizeof(ImU64),            "%I64u","%I64u" },
#else
	{ sizeof(ImS64),            "%lld", "%lld"  },  // ImGuiDataType_S64
	{ sizeof(ImU64),            "%llu", "%llu"  },
#endif
	{ sizeof(float),            "%f",   "%f"    },  // ImGuiDataType_Float (float are promoted to double in va_arg)
	{ sizeof(double),           "%f",   "%lf"   },  // ImGuiDataType_Double
};
IM_STATIC_ASSERT(IM_ARRAYSIZE(GDataTypeInfo) == ImGuiDataType_COUNT);

const ImGuiDataTypeInfo* DataTypeGetInfo(ImGuiDataType data_type)
{
	IM_ASSERT(data_type >= 0 && data_type < ImGuiDataType_COUNT);
	return &GDataTypeInfo[data_type];
}

inline bool SliderScalar(const char* label, ImGuiDataType data_type, void* v, const void* v_min, const void* v_max, const char* format, float power)
{
	using namespace ImGui;

	ImGuiWindow* window = GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	const ImGuiStyle& style = g.Style;
	const ImGuiID id = window->GetID(label);
	const float w = ImGui::GetWindowSize().x - 22;

	const ImVec2 label_size = CalcTextSize(label, NULL, true);
	const ImRect frame_bb(window->DC.CursorPos + ImVec2(3, 15), window->DC.CursorPos + ImVec2(w, label_size.y + style.FramePadding.y * 2.0f + 15));
	const ImRect total_bb(frame_bb.Min, frame_bb.Max + ImVec2(0.0f, 15));

	ItemSize(total_bb, style.FramePadding.y);
	if (!ItemAdd(total_bb, id, &frame_bb))
		return false;

	// Default format string when passing NULL
	// Patch old "%.0f" format string to use "%d", read function comments for more details.
	IM_ASSERT(data_type >= 0 && data_type < ImGuiDataType_COUNT);
	if (format == NULL)
		format = GDataTypeInfo[data_type].PrintFmt;
	else if (data_type == ImGuiDataType_S32 && strcmp(format, "%d") != 0)
		format = PatchFormatStringFloatToInt(format);

	// Tabbing or CTRL-clicking on Slider turns it into an input box
	const bool hovered = ItemHoverable(frame_bb, id);
	bool temp_input_is_active = TempInputIsActive(id);
	bool temp_input_start = false;
	if (!temp_input_is_active)
	{
		const bool focus_requested = FocusableItemRegister(window, id);
		const bool clicked = (hovered && g.IO.MouseClicked[0]);
		if (focus_requested || clicked || g.NavActivateId == id || g.NavInputId == id)
		{
			SetActiveID(id, window);
			SetFocusID(id, window);
			FocusWindow(window);
			g.ActiveIdUsingNavDirMask |= (1 << ImGuiDir_Left) | (1 << ImGuiDir_Right);
			if (focus_requested || (clicked && g.IO.KeyCtrl) || g.NavInputId == id)
			{
				temp_input_start = true;
				FocusableItemUnregister(window);
			}
		}
	}

	// Display value using user-provided display format so user can add prefix/suffix/decorations to the value.
	char value_buf[64];
	const char* value_buf_end = value_buf + DataTypeFormatString(value_buf, IM_ARRAYSIZE(value_buf), data_type, v, format);

	// Draw frame
	const ImU32 frame_col = GetColorU32(g.ActiveId == id ? ImGuiCol_FrameBgActive : g.HoveredId == id ? ImGuiCol_FrameBgHovered : ImGuiCol_FrameBg);

	RenderFrame(frame_bb.Min + ImVec2(0, 7), frame_bb.Max - ImVec2(0, 7), GetColorU32(ImGuiCol_FrameBg)/*ImColor(90, 90, 90)*/, true, 6);

	// Slider behavior
	ImRect grab_bb;
	const bool value_changed = SliderBehavior(frame_bb, id, data_type, v, v_min, v_max, format, 1, NULL, &grab_bb);
	if (value_changed)
		MarkItemEdited(id);

	// Render grab
	if (grab_bb.Max.x > grab_bb.Min.x)
		window->DrawList->AddCircleFilled(grab_bb.Max - ImVec2((grab_bb.Max.x - grab_bb.Min.x) / 2, 9), 7, GetColorU32(ImGuiCol_FrameBgHovered)/*ImColor(120, 120, 120)*/, 33),
		window->DrawList->AddCircleFilled(grab_bb.Max - ImVec2((grab_bb.Max.x - grab_bb.Min.x) / 2, 9), 7, GetColorU32(ImGuiCol_MainColorAccent)/*ImColor(120, 120, 120)*/, 32);


	if (label_size.x > 0)
		window->DrawList->AddText(ImVec2(frame_bb.Min.x, frame_bb.Min.y - 14), ImGui::GetColorU32(ImGuiCol_Text), label);

	if (label_size.x > 0)
		window->DrawList->AddText(ImVec2(frame_bb.Max.x - ImGui::CalcTextSize(value_buf).x, frame_bb.Min.y - 14), ImGui::GetColorU32(ImGuiCol_TextDisabled), value_buf);

	IMGUI_TEST_ENGINE_ITEM_INFO(id, label, window->DC.ItemFlags);
	return value_changed;
}

bool c_menu_elements::slider_float(const char* label, float* v, float v_min, float v_max, const char* format, float power)
{
	return SliderScalar(label, ImGuiDataType_Float, v, &v_min, &v_max, format, power);
}

bool c_menu_elements::slider_int(const char* label, int* v, int v_min, int v_max, const char* format)
{
	return SliderScalar(label, ImGuiDataType_S32, v, &v_min, &v_max, format, 1);
}

void c_menu_elements::sameline(float offset_from_start_x, float spacing_w)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return;

	ImGuiContext& g = *GImGui;
	if (offset_from_start_x != 0.0f)
	{
		if (spacing_w < 0.0f) spacing_w = 0.0f;
		window->DC.CursorPos.x = window->Pos.x - window->Scroll.x + offset_from_start_x + spacing_w + window->DC.GroupOffset.x /*+ window->DC.ColumnsOffset.x*/;
		window->DC.CursorPos.y = window->DC.CursorPosPrevLine.y;
	}
	else
	{
		if (spacing_w < 0.0f) spacing_w = /*g.Style.ItemSpacing.x*/ 0;
		window->DC.CursorPos.x = window->DC.CursorPosPrevLine.x + spacing_w;
		window->DC.CursorPos.y = window->DC.CursorPosPrevLine.y;
	}
	window->DC.CurrLineSize = window->DC.PrevLineSize;
	window->DC.CurrLineTextBaseOffset = window->DC.PrevLineTextBaseOffset;
}



const char* const KeyNames[] = {
	"Unknown",
	"VK_LBUTTON",
	"VK_RBUTTON",
	"VK_CANCEL",
	"VK_MBUTTON",
	"VK_XBUTTON1",
	"VK_XBUTTON2",
	"Unknown",
	"VK_BACK",
	"VK_TAB",
	"Unknown",
	"Unknown",
	"VK_CLEAR",
	"VK_RETURN",
	"Unknown",
	"Unknown",
	"VK_SHIFT",
	"VK_CONTROL",
	"VK_MENU",
	"VK_PAUSE",
	"VK_CAPITAL",
	"VK_KANA",
	"Unknown",
	"VK_JUNJA",
	"VK_FINAL",
	"VK_KANJI",
	"Unknown",
	"VK_ESCAPE",
	"VK_CONVERT",
	"VK_NONCONVERT",
	"VK_ACCEPT",
	"VK_MODECHANGE",
	"VK_SPACE",
	"VK_PRIOR",
	"VK_NEXT",
	"VK_END",
	"VK_HOME",
	"VK_LEFT",
	"VK_UP",
	"VK_RIGHT",
	"VK_DOWN",
	"VK_SELECT",
	"VK_PRINT",
	"VK_EXECUTE",
	"VK_SNAPSHOT",
	"VK_INSERT",
	"VK_DELETE",
	"VK_HELP",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"VK_LWIN",
	"VK_RWIN",
	"VK_APPS",
	"Unknown",
	"VK_SLEEP",
	"VK_NUMPAD0",
	"VK_NUMPAD1",
	"VK_NUMPAD2",
	"VK_NUMPAD3",
	"VK_NUMPAD4",
	"VK_NUMPAD5",
	"VK_NUMPAD6",
	"VK_NUMPAD7",
	"VK_NUMPAD8",
	"VK_NUMPAD9",
	"VK_MULTIPLY",
	"VK_ADD",
	"VK_SEPARATOR",
	"VK_SUBTRACT",
	"VK_DECIMAL",
	"VK_DIVIDE",
	"VK_F1",
	"VK_F2",
	"VK_F3",
	"VK_F4",
	"VK_F5",
	"VK_F6",
	"VK_F7",
	"VK_F8",
	"VK_F9",
	"VK_F10",
	"VK_F11",
	"VK_F12",
	"VK_F13",
	"VK_F14",
	"VK_F15",
	"VK_F16",
	"VK_F17",
	"VK_F18",
	"VK_F19",
	"VK_F20",
	"VK_F21",
	"VK_F22",
	"VK_F23",
	"VK_F24",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"VK_NUMLOCK",
	"VK_SCROLL",
	"VK_OEM_NEC_EQUAL",
	"VK_OEM_FJ_MASSHOU",
	"VK_OEM_FJ_TOUROKU",
	"VK_OEM_FJ_LOYA",
	"VK_OEM_FJ_ROYA",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"Unknown",
	"VK_LSHIFT",
	"VK_RSHIFT",
	"VK_LCONTROL",
	"VK_RCONTROL",
	"VK_LMENU",
	"VK_RMENU"
};


static bool IsKeyPressedMap(ImGuiKey key, bool repeat = true)
{
	const int key_index = GImGui->IO.KeyMap[key];
	return (key_index >= 0) ? ImGui::IsKeyPressed(key_index, repeat) : false;
}

bool c_menu_elements::key_bind(const char* label, int& k, const ImVec2& size_arg)
{
	ImGuiWindow* window = ImGui::GetCurrentWindow();
	if (window->SkipItems)
		return false;

	ImGuiContext& g = *GImGui;
	ImGuiIO& io = g.IO;
	const ImGuiStyle& style = g.Style;

	const ImGuiID id = window->GetID(label);
	const ImVec2 label_size = ImGui::CalcTextSize(label, NULL, true);
	ImVec2 size = ImGui::CalcItemSize(size_arg, ImGui::CalcItemWidth(), label_size.y + style.FramePadding.y * 2.0f);
	const ImRect frame_bb(window->DC.CursorPos, window->DC.CursorPos + size);
	const ImRect total_bb(window->DC.CursorPos, frame_bb.Max);

	ImGui::ItemSize(total_bb, style.FramePadding.y);
	if (!ImGui::ItemAdd(total_bb, id))
		return false;

	const bool focus_requested = ImGui::FocusableItemRegister(window, g.ActiveId == id);
	//const bool focus_requested_by_code = focus_requested && (window->FocusIdxAllCounter == window->FocusIdxAllRequestCurrent);
	//const bool focus_requested_by_tab = focus_requested && !focus_requested_by_code;

	const bool hovered = ImGui::ItemHoverable(frame_bb, id);

	if (hovered) {
		ImGui::SetHoveredID(id);
		g.MouseCursor = ImGuiMouseCursor_TextInput;
	}

	const bool user_clicked = hovered && io.MouseClicked[0];

	if (focus_requested || user_clicked) {
		if (g.ActiveId != id) {
			// Start edition
			memset(io.MouseDown, 0, sizeof(io.MouseDown));
			memset(io.KeysDown, 0, sizeof(io.KeysDown));
			k = 0;
		}
		ImGui::SetActiveID(id, window);
		ImGui::FocusWindow(window);
	}
	else if (io.MouseClicked[0]) {
		// Release focus when we click outside
		if (g.ActiveId == id)
			ImGui::ClearActiveID();
	}

	bool value_changed = false;
	int key = k;

	if (g.ActiveId == id) {
		for (auto i = 0; i < 5; i++) {
			if (io.MouseDown[i]) {
				switch (i) {
				case 0:
					key = VK_LBUTTON;
					break;
				case 1:
					key = VK_RBUTTON;
					break;
				case 2:
					key = VK_MBUTTON;
					break;
				case 3:
					key = VK_XBUTTON1;
					break;
				case 4:
					key = VK_XBUTTON2;
					break;
				}
				value_changed = true;
				ImGui::ClearActiveID();
			}
		}
		if (!value_changed) {
			for (auto i = VK_BACK; i <= VK_RMENU; i++) {
				if (io.KeysDown[i]) {
					key = i;
					value_changed = true;
					ImGui::ClearActiveID();
				}
			}
		}

		if (IsKeyPressedMap(ImGuiKey_Escape)) {
			k = 0;
			ImGui::ClearActiveID();
		}
		else {
			k = key;
		}
	}

	// Render
	// Select which buffer we are going to display. When ImGuiInputTextFlags_NoLiveEdit is Set 'buf' might still be the old value. We Set buf to NULL to prevent accidental usage from now on.

	char buf_display[64] = "None";

	ImGui::RenderFrame(frame_bb.Min, frame_bb.Max, ImGui::GetColorU32(ImGuiCol_ComboBg), true, 5);
	window->DrawList->AddRect(frame_bb.Min, frame_bb.Max, ImColor(90, 90, 90, 255), 5);

	if (k != 0 && g.ActiveId != id) {
		strcpy_s(buf_display, KeyNames[k]);
	}
	else if (g.ActiveId == id) {
		strcpy_s(buf_display, "[Press a key]");
	}

	const ImRect clip_rect(frame_bb.Min.x, frame_bb.Min.y, frame_bb.Min.x + size.x, frame_bb.Min.y + size.y); // Not using frame_bb.Max because we have adjusted size
	ImVec2 render_pos = frame_bb.Min + style.FramePadding;
	ImGui::RenderTextClipped(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding, buf_display, NULL, NULL, style.ButtonTextAlign, &clip_rect);
	//RenderTextClipped(frame_bb.Min + style.FramePadding, frame_bb.Max - style.FramePadding, buf_display, NULL, NULL, GetColorU32(ImGuiCol_Text), style.ButtonTextAlign, &clip_rect);
	//draw_window->DrawList->AddText(g.Font, g.FontSize, render_pos, GetColorU32(ImGuiCol_Text), buf_display, NULL, 0.0f, &clip_rect);

	if (label_size.x > 0)
		ImGui::RenderText(ImVec2(total_bb.Max.x + style.FramePadding.x, frame_bb.Min.y + style.FramePadding.y), label);

	return value_changed;
}