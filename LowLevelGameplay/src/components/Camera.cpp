#include "Camera.h"
#include "core/GameObject.h"
#include "core/Renderer.h"

namespace LLGP
{
	Camera::Camera(GameObject* owner) : Component(owner)
	{
		m_windowSize = Vector2f::zero;
		m_windowSize.x = Renderer::GetRenderWindow()->getSize().x;
		m_windowSize.y = Renderer::GetRenderWindow()->getSize().y;

		m_view = std::make_unique<sf::View>();

		m_view.get()->setCenter(GetGameObject()->transform.GetPosition());
		m_view.get()->setSize(m_windowSize);

		Renderer::SetView(m_view.get());
	}

	void Camera::Update(float deltaTime)
	{
		m_view.get()->setCenter(GetGameObject()->transform.GetPosition());
	}
}
