#pragma once

#include "Utils/Memory.hpp"

#include <unordered_map>
#include <string>

struct GameSettings
{
	/* 0x0000 */ std::unordered_map<std::string, int> int_settings;
	/* 0x0040 */ std::unordered_map<std::string, float> float_settings;
	/* 0x0080 */ std::unordered_map<std::string, std::string> string_settings;
	/* 0x00C0 */ char pad_0xC0[0x8];

	inline static void UpdateFloatSetting(const std::string& name, float value)
	{
		GameSettings* v_instance = GameSettings::GetInstance();
		if (!v_instance) return;

		auto v_iter = v_instance->float_settings.find(name);
		if (v_iter == v_instance->float_settings.end())
		{
			v_instance->float_settings.emplace(name, value);
			return;
		}

		v_iter->second = value;
	}

	inline static GameSettings* GetInstance()
	{
		return *Memory::Read<GameSettings*>(0x128D830);
	}
}; // Size: 0xC8

static_assert(sizeof(GameSettings) == 0xC8, "GameSettings: Incorrect Size");