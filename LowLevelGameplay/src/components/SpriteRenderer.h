#pragma once
#include <memory>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "DrawableComponent.h"

namespace LLGP
{
    class SpriteRenderer : public DrawableComponent
    {
    public:
        SpriteRenderer(GameObject* owner);

        bool flipX;
        bool flipY;

        void SetTextureRect(const sf::IntRect rect) { m_sprite->setTextureRect(rect); }
        const sf::IntRect GetTextureRect() { return m_sprite->getTextureRect(); }

        void SetTexture(std::shared_ptr<sf::Texture> newTexture);
        inline std::shared_ptr<sf::Texture> GetTexture() { return m_texturePointer; }

        void Update(float deltaTime) override;

    private:
        sf::Sprite* m_sprite;
        std::shared_ptr<sf::Texture> m_texturePointer;
    };
}
