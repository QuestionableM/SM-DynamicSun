#pragma once

#include "Utils/Memory.hpp"
#include "Utils/Timer.hpp"

class DynamicSun
{
public:
	using PresentFunction = __int64 (*)(void*);
	inline static PresentFunction o_PresentFunction = nullptr;

	static DirectX::XMVECTOR ComputeQuatFromAngle(float angle);
	static DirectX::XMFLOAT3& GetLightDirection();

	static DirectX::XMVECTOR GetRotationQuat(float time_of_day);
	static void UpdateLightDirection(DirectX::FXMVECTOR& dir, DirectX::FXMVECTOR& quat, float intensity);
	static __int64 Update(void* device);

	inline static float ms_fSunAngle = 0.32f;

private:
	inline static Timer ms_deltaTimeTimer;
	inline static float ms_fLightIntensity = 0.0f;
	inline static float ms_fMainMenuTime = 0.5f;
};