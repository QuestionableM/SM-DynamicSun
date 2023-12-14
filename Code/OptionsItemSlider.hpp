#pragma once

#include "OptionsItemBase.hpp"

#include <functional>
#include <string>

struct OptionsItemSlider : public OptionsItemBase
{
	/* 0x0010 */ char pad_0x10[0x10];
	/* 0x0020 */ std::string name;
	/* 0x0040 */ char pad_0x40[0x4];
	/* 0x0044 */ float min_value;
	/* 0x0048 */ float max_value;
	/* 0x004C */ char pad_0x4C[0x4];
	/* 0x0050 */ __int64 m_uSteps;
	/* 0x0058 */ char pad_0x58[0x98];

	OptionsItemSlider(MyGUI::Widget* widget,
		const std::string& caption,
		const std::string& name,
		float min_value,
		float max_value,
		size_t scroll_range,
		const std::function<void(std::size_t)>& callback);
}; // Size: 0xF0

static_assert(sizeof(OptionsItemSlider) == 0xF0, "OptionsItemSlider: Incorrect Size");