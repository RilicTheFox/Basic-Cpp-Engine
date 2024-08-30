#pragma once
#include "core/Component.h"
#include <memory>
#include <SFML/Graphics/View.hpp>
#include "Vector2.h"

namespace LLGP
{
	class Camera : public Component
	{
	public:
		explicit Camera(GameObject* owner);
		void Update(float deltaTime) override;

		void SetZoom(float newZoom) { m_view.get()->zoom(newZoom); }

	private:
		std::unique_ptr<sf::View> m_view;
		Vector2f m_windowSize;
	};
}


