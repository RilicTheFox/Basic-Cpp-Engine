#include <utility>
#include "components/SpriteRenderer.h"
#include "Vector2.h"
#include "core/GameObject.h"
#include "core/Renderer.h"

namespace LLGP
{
    SpriteRenderer::SpriteRenderer(GameObject *owner) : DrawableComponent(owner)
    {
        SetDrawable(new sf::Sprite());
        m_sprite = dynamic_cast<sf::Sprite*>(GetDrawable());
        flipX = false;
        flipY = false;
    }

    void SpriteRenderer::SetTexture(std::shared_ptr<sf::Texture> newTexture)
    {
        m_texturePointer = newTexture;
        m_sprite->setTexture(*m_texturePointer);

        const Vector2f size = Vector2f(m_texturePointer->getSize().x, m_texturePointer->getSize().y);
        m_sprite->setOrigin(size / 2);
    }

    void SpriteRenderer::Update(float deltaTime)
    {
        m_sprite->setPosition(_gameObject->transform.GetPosition());
        m_sprite->setScale(_gameObject->transform.GetScale());

        Vector2f flipVector = Vector2f(1, 1);

        if (flipX) flipVector.x = -1;
        if (flipY) flipVector.y = -1;

        Vector2f unflipped = Vector2f(m_sprite->getScale().x, m_sprite->getScale().y);
        m_sprite->setScale(unflipped * flipVector);

        m_sprite->setRotation(_gameObject->transform.GetRotation());
    }
}
