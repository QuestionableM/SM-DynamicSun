#pragma once

#include <SmSdk/Util/Memory.hpp>
#include "offsets.hpp"

struct GameInstanceData
{
	float time_of_day;

	inline static GameInstanceData* GetInstance()
	{
		return *Memory::ReadPtr<GameInstanceData*>(DYNAMIC_SUN_GAME_INSTANCE_PTR);
	}
};