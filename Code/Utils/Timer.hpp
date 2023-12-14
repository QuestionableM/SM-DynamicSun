#pragma once

#include <chrono>

class Timer
{
public:
	Timer()
	{
		m_time = std::chrono::high_resolution_clock::now();
		m_start_time = m_time;
	}

	~Timer() = default;

	template<typename T = float>
	T Update()
	{
		auto v_old_time = m_time;
		m_time = std::chrono::high_resolution_clock::now();

		return std::chrono::duration<T>(m_time - v_old_time).count();
	}

	template<typename T = float>
	T GetTime() const
	{
		auto v_new_time = std::chrono::high_resolution_clock::now();

		return std::chrono::duration<T>(v_new_time - m_start_time).count();
	}

private:
	std::chrono::steady_clock::time_point m_time;
	std::chrono::steady_clock::time_point m_start_time;
};