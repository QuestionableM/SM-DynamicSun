#pragma once

#include "win_include.hpp"

namespace Memory
{
	template<typename T>
	inline T GetGlobal(std::uintptr_t offset) noexcept
	{
		return reinterpret_cast<T>(std::uintptr_t(GetModuleHandle(NULL)) + offset);
	}

	template<typename T>
	inline T* Read(std::uintptr_t offset) noexcept
	{
		return reinterpret_cast<T*>(std::uintptr_t(GetModuleHandle(NULL)) + offset);
	}

	template<typename T>
	inline T& ReadRef(std::uintptr_t offset)
	{
		return *reinterpret_cast<T*>(std::uintptr_t(GetModuleHandle(NULL)) + offset);
	}

	inline std::uintptr_t ToLocalOffset(void* global_ptr) noexcept
	{
		return std::uintptr_t(global_ptr) - std::uintptr_t(GetModuleHandle(NULL));
	}

	//Writes any amount of bytes to pointer to protected memory
	inline void WriteBytesPtr(void* ptr, const char* data, std::size_t data_size)
	{
		DWORD v_old_protect;
		VirtualProtect(ptr, data_size, PAGE_EXECUTE_READWRITE, &v_old_protect);
		std::memcpy(ptr, data, data_size);
		VirtualProtect(ptr, data_size, v_old_protect, &v_old_protect);
	}

	//Writes a value of any type to protected memory
	template<typename T>
	inline void WriteValue(std::uintptr_t offset, const T& data)
	{
		Memory::WriteBytesPtr(Memory::Read<void>(offset), reinterpret_cast<const char*>(&data), sizeof(T));
	}

	template<typename T>
	inline void WriteValueGlobal(std::uintptr_t address, const T& data)
	{
		Memory::WriteBytesPtr(reinterpret_cast<void*>(address), reinterpret_cast<const char*>(&data), sizeof(T));
	}

	template<typename T>
	inline void WriteValueGlobalSafe(std::uintptr_t address, const T& data)
	{
		if (IsBadReadPtr(reinterpret_cast<void*>(address), sizeof(T)) == 0)
			Memory::WriteValueGlobal<T>(address, data);
	}

	//Writes any amount of bytes to protected memory
	inline void WriteBytes(std::uintptr_t offset, const char* data, std::size_t data_size)
	{
		Memory::WriteBytesPtr(Memory::Read<void>(offset), data, data_size);
	}
}