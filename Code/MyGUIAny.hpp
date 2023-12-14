#pragma once

#include <memory>

namespace MyGUI
{
	struct Any
	{
		struct Holder {};

		struct HolderSizeT : Holder
		{
			void* vftable;
			std::size_t value;

			HolderSizeT(std::size_t value);
		};

		template<typename T>
		Any(const T& value)
		{
			if constexpr (std::is_same_v<T, std::size_t>)
			{
				this->holder = new HolderSizeT(value);
			}
			else
			{
				this->holder = nullptr;
			}
		}

		~Any() = default;

		template<typename T>
		inline T GetValue() const
		{
			return *reinterpret_cast<T*>(reinterpret_cast<char*>(holder) + 8);
		}

		Holder* holder;
	};
}