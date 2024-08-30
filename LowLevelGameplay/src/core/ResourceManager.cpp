#include <memory>
#include "ResourceManager.h"

#include <iostream>

namespace LLGP
{
	std::map<std::string, std::weak_ptr<sf::Texture>> ResourceManager::_textureMap;

	std::shared_ptr<sf::Texture> ResourceManager::GetTexture(std::string path)
	{
		// If weak pointer exists in map and isn't expired, lock it and return a new shared pointer to it.
		if (_textureMap.contains(path) and not _textureMap[path].expired())
		{
			return _textureMap[path].lock();
		}
		// Else, load a new texture and make a shared pointer to it. Then store a weak pointer to the shared pointer.
		else
		{
			const std::shared_ptr<sf::Texture> tex = std::make_shared<sf::Texture>();
			_textureMap[path] = tex;

			if (!tex->loadFromFile(path))
			{
				std::cout << "FILE FAILED TO LOAD SOMEHOW" << std::endl;
			}

			return tex;
		}
	}
}
