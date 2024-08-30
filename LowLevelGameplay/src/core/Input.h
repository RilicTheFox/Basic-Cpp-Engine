#pragma once

#include <map>
#include "Vector2.h"

namespace LLGP
{
	class Input
	{
	public:
		static void Init();
		static void Poll();

		static float GetValue(sf::Keyboard::Key key);
		static bool IsActionPressed(std::string action);

		static Vector2f GetThrustInput() { return m_thrustInput; }

		static std::map<std::string, sf::Keyboard::Key> buttonMap;

	private:
		static Vector2f m_thrustInput;
	};
}

