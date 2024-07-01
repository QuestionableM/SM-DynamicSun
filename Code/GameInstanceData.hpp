#pragma once

#include <SmSdk/Util/Memory.hpp>

struct GameInstanceData
{
	float time_of_day;

	inline static GameInstanceData* GetInstance()
	{
		return *Memory::ReadPtr<GameInstanceData*>(0x128D790);
	}
};