#include "components/DrawableComponent.h"
#include "core/Renderer.h"

namespace LLGP
{
    DrawableComponent::~DrawableComponent()
    {
        Renderer::DeregisterDrawable(_drawable);
    }

    void DrawableComponent::SetDrawable(sf::Drawable *drawablePointer)
    {
        _drawable = drawablePointer;
        Renderer::RegisterDrawable(_drawable);
    }
}
