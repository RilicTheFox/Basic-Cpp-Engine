#include "Input.h"

namespace LLGP
{
	std::map<std::string, sf::Keyboard::Key> Input::buttonMap = std::map<std::string, sf::Keyboard::Key>();
	Vector2f Input::m_thrustInput = Vector2f::zero;

	void Input::Init()
	{
		buttonMap["up"] = sf::Keyboard::W;
		buttonMap["down"] = sf::Keyboard::S;
		buttonMap["left"] = sf::Keyboard::A;
		buttonMap["right"] = sf::Keyboard::D;
		buttonMap["shoot"] = sf::Keyboard::Space;
	}
	
	// TODO: an overload of this funciton for controller support
	float Input::GetValue(sf::Keyboard::Key key)
	{
		return sf::Keyboard::isKeyPressed(key) ? 1.f : 0.f;
	}

	bool Input::IsActionPressed(std::string action)
	{
		return sf::Keyboard::isKeyPressed(buttonMap[action]);
	}

	void Input::Poll()
	{
		// Get thrust input for the player's ship.
		Vector2f thrustInput;

		thrustInput.x = GetValue(buttonMap["right"]) - GetValue(buttonMap["left"]);
		thrustInput.y = GetValue(buttonMap["down"]) - GetValue(buttonMap["up"]);
		thrustInput.Normalise();
		m_thrustInput = thrustInput;
	}
}
