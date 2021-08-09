#pragma once
#include <Windows.h>
#include <vector>

namespace native::maps
{
	struct map_t
	{
		uintptr_t native;
		uintptr_t eax;
	};

	extern std::vector<map_t> xmaps;
	extern void dump();

	class mapper
	{
	public:
		uintptr_t operator[](uintptr_t native)
		{
			for (auto&& hash : xmaps)
			{
				auto ptr = &hash;
				if (ptr->native == native)
					return ptr->eax;
			}

			return 0;
		}

		inline static mapper get()
		{
			static mapper m_mapper;
			return m_mapper;
		}

	};
}
