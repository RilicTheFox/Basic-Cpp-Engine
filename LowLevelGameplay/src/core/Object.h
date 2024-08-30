#pragma once
#include <core/UUID.h>

namespace LLGP
{
	class Object
	{
	public:
		Object() : uuid() {}
		Object(const Object&) = default;

		UUID uuid;

		inline bool operator==(const Object& rhs) const
		{
			return (uint64_t)this->uuid == (uint64_t)rhs.uuid;
		}

		inline bool operator!=(const Object& rhs) const
		{
			return !(*this == rhs);
		}
	};
}
