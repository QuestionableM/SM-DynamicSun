#include "MyGUIAny.hpp"

#include "Utils/Console.hpp"
#include "Utils/Memory.hpp"

namespace MyGUI
{
	Any::HolderSizeT::HolderSizeT(std::size_t value)
	{
		this->vftable = Memory::GetGlobal<void*>(0xF5CCC8);
		this->value = value;
	}
}