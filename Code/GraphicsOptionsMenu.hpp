#pragma once

#include <SmSdk/Gui/OptionsSubMenuBase.hpp>
#include "OptionsItemDropDown.hpp"

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

class GraphicsOptionsMenu : public OptionsSubMenuBase
{
public:
	using CreateWidgetsSig = __int64 (*)(GraphicsOptionsMenu*);

	/* 0x0168 */ MyGUI::Button* some_button;
	/* 0x0170 */ std::shared_ptr<OptionsItemDropDown> shader_quality_dropdown;
	/* 0x0180 */ std::shared_ptr<OptionsItemDropDown> reflection_quality_dropdown;
	/* 0x0190 */ std::shared_ptr<OptionsItemDropDown> shadow_resolution_dropdown;
	/* 0x01A0 */ std::shared_ptr<OptionsItemDropDown> shadow_quality_dropdown;
	/* 0x01B0 */ std::shared_ptr<OptionsItemDropDown> ssao_dropdown;
	/* 0x01C0 */ std::shared_ptr<OptionsItemDropDown> foliage_dropdown;
	/* 0x01D0 */ std::shared_ptr<OptionsItemDropDown> texture_quality_dropdown;
	/* 0x01E0 */ std::shared_ptr<OptionsItemDropDown> draw_distance_dropdown;
	/* 0x01F0 */ std::shared_ptr<OptionsItemDropDown> tex_filtering_dropdown;
	/* 0x0200 */ std::shared_ptr<OptionsItemDropDown> particle_quality_dropdown;
	/* 0x0210 */ std::vector<std::string> quality_level_labels;
	/* 0x0228 */ char pad_0x228[0x20];

	inline static CreateWidgetsSig o_CreateWidgets = nullptr;

	static __int64 h_CreateWidgets(GraphicsOptionsMenu* self);
}; // Size: 0x248

static_assert(sizeof(GraphicsOptionsMenu) == 0x248, "GraphicsOptionsMenu: Incorrect Size");