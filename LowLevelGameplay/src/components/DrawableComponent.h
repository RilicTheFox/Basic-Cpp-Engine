#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include "core/Component.h"

namespace LLGP
{
    class DrawableComponent : public Component
    {

    protected:
        sf::RenderStates _renderStates;

    public:
        DrawableComponent(GameObject *owner) : Component(owner) {}
        ~DrawableComponent();

    protected:
        void SetDrawable(sf::Drawable* drawablePointer);
        sf::Drawable* GetDrawable() const { return _drawable; }

    private:
        sf::Drawable* _drawable;
    };
}
