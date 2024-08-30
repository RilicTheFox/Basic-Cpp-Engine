#pragma once

#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

namespace LLGP
{
    class Renderer
    {
    public:
		static void Init();
        static void RegisterDrawable(sf::Drawable* drawable);
    	static void DeregisterDrawable(sf::Drawable* drawable);
        static void Draw();

		static void SetView(sf::View* newView) { m_currentView = newView; }
		static sf::RenderWindow* GetRenderWindow() { return m_renderWindow; }

    private:
        static std::vector<sf::Drawable*> m_drawables;
        static sf::RenderWindow* m_renderWindow;
		static sf::View* m_currentView;
    };
}
