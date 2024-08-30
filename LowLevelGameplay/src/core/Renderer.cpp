#include "Renderer.h"

namespace LLGP
{
    std::vector<sf::Drawable*> Renderer::m_drawables;
    sf::RenderWindow* Renderer::m_renderWindow;
	sf::View* Renderer::m_currentView;

	void Renderer::Init()
	{
		m_renderWindow = new sf::RenderWindow(sf::VideoMode(1280, 800), "Sinistar");
	}

    void Renderer::RegisterDrawable(sf::Drawable* drawable)
    {
        m_drawables.push_back(drawable);
    }

    void Renderer::DeregisterDrawable(sf::Drawable* drawable)
    {
		auto iterator = std::find(m_drawables.begin(), m_drawables.end(), drawable);

		if (iterator == m_drawables.end()) return;
		m_drawables.erase(iterator);
    }

    void Renderer::Draw()
    {
		m_renderWindow->clear();

		m_renderWindow->setView(*m_currentView);

        for (const sf::Drawable* drawable : m_drawables)
        {
            if (drawable == nullptr) continue;
            m_renderWindow->draw(*drawable);
        }

		m_renderWindow->display();
    }
}
