#pragma once

#include "Utils/Memory.hpp"

struct GameInstanceData
{
	float time_of_day;

	inline static GameInstanceData* GetInstance()
	{
		return *Memory::Read<GameInstanceData*>(0x128D790);
	}
};