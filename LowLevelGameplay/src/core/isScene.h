#pragma once
#include <concepts>
#include "Scene.h"

namespace LLGP
{
    template <class T>
    concept isScene = std::derived_from<T, Scene>;
}