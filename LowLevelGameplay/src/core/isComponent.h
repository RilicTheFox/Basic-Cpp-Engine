#pragma once
#include <concepts>
#include <core/Component.h>

namespace LLGP
{
	template <class T>
	concept isComponent = std::derived_from<T, Component>;
}
