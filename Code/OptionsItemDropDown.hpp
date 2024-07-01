#pragma once

#include <SmSdk/Gui/OptionsItemBase.hpp>

#include <functional>
#include <string>
#include <memory>

struct DropDown
{
	/* 0x0000 */ char pad_0x0[0x108];
}; // Size: 0x108

static_assert(sizeof(DropDown) == 0x108, "DropDown: Incorrect Size");

struct OptionsItemDropDown : public OptionsItemBase
{
	/* 0x0010 */ std::string name;
	/* 0x0030 */ char pad_0x30[0x8];
	/* 0x0038 */ std::shared_ptr<DropDown> drop_down;
	/* 0x0048 */ std::string current_option;
	/* 0x0068 */ char pad_0x68[0x48];

	OptionsItemDropDown(
		MyGUI::Widget* widget,
		const std::string& caption,
		const std::string& name,
		std::function<void(const std::string&, const MyGUI::Any&)>
	);

	void AddItem(const std::string& item, const MyGUI::Any& item_data, const std::string& caption);
}; // Size: 0xB0

static_assert(sizeof(OptionsItemDropDown) == 0xB0, "OptionsItemDropDown: Incorrect Size");