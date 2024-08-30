#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics/Shape.hpp>
#include "Component.h"

namespace LLGP
{
    class BackgroundStars : public Component
    {
    public:
        BackgroundStars(GameObject* owner) : Component(owner) {};

    private:
        std::vector<std::unique_ptr<GameObject>> m_stars;
    };
}