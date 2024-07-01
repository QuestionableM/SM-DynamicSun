#include "OptionsItemDropDown.hpp"

#include <SmSdk/Util/Memory.hpp>

OptionsItemDropDown::OptionsItemDropDown(
	MyGUI::Widget* widget,
	const std::string& caption,
	const std::string& name,
	std::function<void(const std::string&, const MyGUI::Any&)> callback)
{
	using OptionsItemDropDownConstructor = void(*)(
		OptionsItemDropDown*,
		MyGUI::Widget*,
		const std::string&,
		const std::string&,
		std::function<void(const std::string&, const MyGUI::Any&)>
	);

	OptionsItemDropDownConstructor v_constructor = Memory::Read<OptionsItemDropDownConstructor>(0x3C8460);
	v_constructor(this, widget, caption, name, callback);
}

void OptionsItemDropDown::AddItem(
	const std::string& item,
	const MyGUI::Any& item_data,
	const std::string& caption)
{
	using ItemConstructor = void(*)(
		OptionsItemDropDown*,
		const std::string& item_name,
		const MyGUI::Any& data,
		const std::string& caption
	);

	ItemConstructor v_constructor = Memory::Read<ItemConstructor>(0x3C89F0);
	v_constructor(this, item, item_data, caption);
}