#include "GraphicsOptionsMenu.hpp"

#include <SmSdk/Gui/OptionsItemSlider.hpp>
#include <SmSdk/GameState.hpp>
#include <SmSdk/Util/Memory.hpp>

#include "GameInstanceData.hpp"
#include "Utils/Console.hpp"
#include "DynamicSun.hpp"

constexpr float g_minSunAngle = DirectX::XMConvertToRadians(-70.0f);
constexpr float g_maxSunAngle = DirectX::XMConvertToRadians(70.0f);

class SunAngleSlider : public OptionsItemSlider
{
public:
	inline SunAngleSlider(MyGUI::Widget* pWidget) :
		OptionsItemSlider(pWidget, "Sun Angle", g_minSunAngle, g_maxSunAngle, 20)
	{
		this->update();

		m_pSlider->eventScrollChangePosition += MyGUI::newDelegate(
			this, &SunAngleSlider::sliderChangePosition);
	}

	void updateText()
	{
		const std::int64_t v_cur_val = std::int64_t(this->getFraction() * 100.0f);
		m_pValueTextBox->setCaption(std::to_string(v_cur_val));
	}

	void sliderChangePosition(MyGUI::ScrollBar* caller, std::size_t new_val)
	{
		DynamicSun::ms_fSunAngle = this->getFraction();
		this->updateText();
	}

	std::size_t getSunAngleApprox() const
	{
		const float v_range = (DynamicSun::ms_fSunAngle + g_maxSunAngle) / (g_maxSunAngle * 2.0f);
		const float v_range_clamped = std::clamp(v_range, 0.0f, 1.0f);

		return std::size_t(v_range_clamped * m_uSteps);
	}

	void update() override
	{
		m_pSlider->setScrollPosition(this->getSunAngleApprox());
		this->updateText();
	}
};

__int64 GraphicsOptionsMenu::h_CreateWidgets(GraphicsOptionsMenu* self)
{
	if (Memory::ToLocalAddress(*reinterpret_cast<void**>(self)) == 0xF65600)
	{
		DebugOutL(__FUNCTION__, " -> Injected custom game settings");

		auto v_sun_slider = std::make_shared<SunAngleSlider>(
			self->m_rightStackBox.createNewOption());
		self->m_optionItems.emplace_back(std::move(v_sun_slider));
	}

	return GraphicsOptionsMenu::o_CreateWidgets(self);
}