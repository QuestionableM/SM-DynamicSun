#pragma once

#include "MyGuiStructs.hpp"

struct OptionsItemBase
{
	virtual ~OptionsItemBase() = default;
	virtual void Update() {}

	/* 0x0008 */ MyGUI::Widget* widget;
}; // Size: 0x10

static_assert(sizeof(OptionsItemBase) == 0x10, "OptionsItemBase: Incorrect Size");