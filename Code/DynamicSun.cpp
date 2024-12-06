#include "DynamicSun.hpp"

#include "GameInstanceData.hpp"
#include <SmSdk/GameState.hpp>

#include "Utils/Console.hpp"
#include "offsets.hpp"

float DynamicSun::GetSunAngle()
{
	if (GameInstanceData::GetInstance())
		return ms_fSunAngle;

	return std::abs(ms_fSunAngle);
}

DirectX::XMVECTOR DynamicSun::ComputeQuatFromAngle(float angle)
{
	DirectX::FXMMATRIX v_rot_matrix = DirectX::XMMatrixRotationRollPitchYaw(0.0f, angle, DynamicSun::GetSunAngle());
	return DirectX::XMQuaternionRotationMatrix(v_rot_matrix);
}

DirectX::XMFLOAT3& DynamicSun::GetLightDirection()
{
	return *Memory::Read<DirectX::XMFLOAT3*>(DYNAMIC_SUN_DIRECTION_OFFSET);
}

inline static float lerp_float(float a, float b, float f)
{
	return a + f * (b - a);
}

const float GetLightIntensity(float time_of_day)
{
	constexpr float c_fSunriseTime = 0.27f;
	constexpr float c_fSunsetTime = 0.75f;
	constexpr float c_fSunsetTimeReversed = 1.0f - c_fSunsetTime;
	constexpr float c_fSunriseOffset = 0.265f;
	constexpr float c_fSunsetOffset = 0.23f;

	if (time_of_day <= c_fSunriseTime)
	{
		return std::max<float>(time_of_day - c_fSunriseOffset, 0.0f) / (c_fSunriseTime - c_fSunriseOffset);
	}
	else if (time_of_day >= c_fSunsetTime)
	{
		const float v_time_reversed = std::max<float>((1.0f - time_of_day) - c_fSunsetOffset, 0.0f);
		return v_time_reversed / (c_fSunsetTimeReversed - c_fSunsetOffset);
	}
	else
	{
		return 1.0f;
	}
}

DirectX::XMVECTOR DynamicSun::GetRotationQuat(float time_of_day)
{
	float v_lerp_factor;
	if (time_of_day <= 0.5f)
	{
		const float v_range_start = std::fmaxf(0.0f, time_of_day - 0.27f);
		const float v_range_end = 0.5f - 0.27f;

		const float v_distance = 1.0f - std::fmaxf((v_range_end - v_range_start) / v_range_end, 0.0f);
		v_lerp_factor = v_distance / 2.0f;
	}
	else
	{
		const float v_range_start = time_of_day - 0.5f;
		const float v_range_end = 1.0f - 0.75f;

		const float v_distance = 1.0f - std::fmaxf((v_range_end - v_range_start) / v_range_end, 0.0f);
		v_lerp_factor = 0.5f + (v_distance / 2.0f);
	}

	//0.27 -> v_lerp_factor = 0.0 sun appears
	//0.73 -> v_lerp_factor = 1.0 sun disappears

	const float v_rotation_radians = lerp_float(0.0f, DirectX::XM_PI, v_lerp_factor);
	return ComputeQuatFromAngle(v_rotation_radians);
}

const static DirectX::FXMVECTOR v_right_dir = { 1.0f, 0.0f, 0.0f, 0.0f };
const static DirectX::FXMVECTOR v_up_dir = { 0.0f, 1.0f, 0.0f, 0.0f };

void DynamicSun::UpdateLightDirection(DirectX::FXMVECTOR& dir, DirectX::FXMVECTOR& quat, float intensity)
{
	DirectX::FXMVECTOR v_shadow_dir = DirectX::XMVectorScale(
		DirectX::XMVector3Normalize(DirectX::XMVector3Rotate(dir, quat)), intensity);

	DirectX::XMStoreFloat3(&DynamicSun::GetLightDirection(), v_shadow_dir);
}

__int64 DynamicSun::Update(void* device)
{
	const float delta_time = ms_deltaTimeTimer.Update();

	DirectX::XMFLOAT3& v_curLightDir = DynamicSun::GetLightDirection();

	GameInstanceData* v_game_instance = GameInstanceData::GetInstance();
	if (v_game_instance)
	{
		const float v_light_intensity = GetLightIntensity(v_game_instance->time_of_day);
		DynamicSun::UpdateLightDirection(v_right_dir, GetRotationQuat(v_game_instance->time_of_day), v_light_intensity);
	}
	else
	{
		ms_fMainMenuTime = std::fmod(ms_fMainMenuTime + delta_time * 0.015625f, 1.0f);

		const float v_rot = lerp_float(0.0f, DirectX::XM_2PI, ms_fMainMenuTime);

		DirectX::FXMVECTOR v_right_rotation = DirectX::XMQuaternionRotationAxis(
			{ -1.0f, 0.0f, 0.0f, 0.0f }, DirectX::XMConvertToRadians(70.0f) - std::abs(ms_fSunAngle));
		DirectX::FXMVECTOR v_roll_rotation = DirectX::XMQuaternionRotationAxis(
			{ 0.0f, 0.0f, 1.0f, 0.0f }, v_rot);
		DirectX::FXMVECTOR v_quat = DirectX::XMQuaternionMultiply(v_right_rotation, v_roll_rotation);

		DynamicSun::UpdateLightDirection(v_up_dir, v_quat, 1.0f);
	}

	return DynamicSun::o_PresentFunction(device);
}