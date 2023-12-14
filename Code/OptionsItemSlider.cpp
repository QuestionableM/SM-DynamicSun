#include "OptionsItemSlider.hpp"

#include "Utils/Memory.hpp"

OptionsItemSlider::OptionsItemSlider(
	MyGUI::Widget* widget,
	const std::string& caption,
	const std::string& name,
	float min_value,
	float max_value,
	size_t scroll_range,
	const std::function<void(std::size_t)>& callback)
{
	using OptionsItemSliderConstructor = void (*)(
		OptionsItemSlider* self,
		MyGUI::Widget* widget,
		const std::string& caption,
		const std::string& name,
		float min_value,
		float max_value,
		size_t scroll_range,
		const std::function<void(std::size_t)>& callback
	);

	OptionsItemSliderConstructor v_constructor = Memory::GetGlobal<OptionsItemSliderConstructor>(0x3C9A30);
	v_constructor(this, widget, caption, name, min_value, max_value, scroll_range, callback);
}