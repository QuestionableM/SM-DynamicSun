#pragma once

#include "OptionsItemDropDown.hpp"

#include <unordered_map>
#include <vector>
#include <string>
#include <memory>

struct Options
{
	/* 0x0000 */ char pad_0x0[0x8];
	/* 0x0008 */ std::string skin;
	/* 0x0028 */ char pad_0x28[0x38];
	/* 0x0060 */ std::vector<MyGUI::Widget*> widgets;
	/* 0x0078 */ MyGUI::Colour color;

	MyGUI::Widget* createNewOption();
}; // Size: 0x88

struct OptionsSubMenuBase
{
	/* 0x0000 */ char pad_0x0[0x30];
	/* 0x0030 */ Options options1;
	/* 0x00B8 */ Options options2;
	/* 0x0140 */ char pad_0x140[0x28];
}; // Size: 0x168

static_assert(sizeof(OptionsSubMenuBase) == 0x168, "OptionsSubMenuBase: Incorrect Size");

struct GraphicsOptionsMenu;

struct VoidHasher
{
	inline std::size_t operator()(const void* ptr) const noexcept
	{
		return reinterpret_cast<std::size_t>(ptr);
	}
};

struct GraphicsOptionsMenu : public OptionsSubMenuBase
{
	using CreateWidgetsSig = __int64 (*)(GraphicsOptionsMenu*);
	using Destructor = void (*)(GraphicsOptionsMenu*, char);

	inline static std::unordered_map<const GraphicsOptionsMenu*,
		std::vector<OptionsItemBase*>, VoidHasher> ms_customItems = {};

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

	void RegisterOptionItem(OptionsItemBase* item);
	void DestroyOptionItems();

	inline static CreateWidgetsSig o_CreateWidgets = nullptr;
	inline static Destructor o_Destructor = nullptr;

	static __int64 h_CreateWidgets(GraphicsOptionsMenu* self);
	static void h_Destructor(GraphicsOptionsMenu* self, char flag);
}; // Size: 0x248

static_assert(sizeof(GraphicsOptionsMenu) == 0x248, "GraphicsOptionsMenu: Incorrect Size");