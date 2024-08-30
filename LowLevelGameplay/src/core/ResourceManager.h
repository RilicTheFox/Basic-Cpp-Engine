#pragma once

#include <map>
#include <memory>
#include <SFML/Graphics.hpp>

namespace LLGP
{
	class ResourceManager
	{
	public:
		static std::shared_ptr<sf::Texture> GetTexture(std::string path);

	private:
		static std::map<std::string, std::weak_ptr<sf::Texture>> _textureMap;
	};
}
