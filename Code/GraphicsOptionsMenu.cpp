#include "GraphicsOptionsMenu.hpp"

#include "OptionsItemSlider.hpp"
#include "GameSettings.hpp"
#include "DynamicSun.hpp"


#include "Utils/Console.hpp"
#include "Utils/Memory.hpp"

MyGUI::Widget* Options::createNewOption()
{
	using NewOptionConstructor = MyGUI::Widget* (*)(Options*);

	NewOptionConstructor v_constructor = Memory::GetGlobal<NewOptionConstructor>(0x536A90);
	return v_constructor(this);
}

void GraphicsOptionsMenu::RegisterOptionItem(OptionsItemBase* item)
{
	auto v_iter = ms_customItems.find(this);
	if (v_iter == ms_customItems.end())
	{
		ms_customItems.emplace(this, std::vector<OptionsItemBase*>{ item });
		return;
	}

	v_iter->second.push_back(item);
}

void GraphicsOptionsMenu::DestroyOptionItems()
{
	auto v_iter = ms_customItems.find(this);
	if (v_iter == ms_customItems.end())
		return;

	for (auto v_item_ptr : v_iter->second)
		v_item_ptr->~OptionsItemBase();

	ms_customItems.erase(v_iter);
}

__int64 GraphicsOptionsMenu::h_CreateWidgets(GraphicsOptionsMenu* self)
{
	if (Memory::ToLocalOffset(*reinterpret_cast<void**>(self)) == 0xF65600)
	{
		DebugOutL(__FUNCTION__, " -> Injected custom game settings");

		constexpr float v_min_sun_angle = DirectX::XMConvertToRadians(-70.0f);
		constexpr float v_max_sun_angle = DirectX::XMConvertToRadians(70.0f);

		GameSettings::UpdateFloatSetting("SunAngle", DynamicSun::ms_fSunAngle);

		MyGUI::Widget* v_new_option = self->options2.createNewOption();
		OptionsItemSlider* v_new_slider = new OptionsItemSlider(
			v_new_option, "Sun Angle", "SunAngle", v_min_sun_angle, v_max_sun_angle, 20,
			[](std::size_t value) -> void {
				DynamicSun::ms_fSunAngle = *reinterpret_cast<float*>(&value);
			}
		);

		self->RegisterOptionItem(v_new_slider);
		v_new_slider->Update();
	}

	return GraphicsOptionsMenu::o_CreateWidgets(self);
}

void GraphicsOptionsMenu::h_Destructor(GraphicsOptionsMenu* self, char flag)
{
	//Cleanup custom options
	self->DestroyOptionItems();
	o_Destructor(self, flag);
}