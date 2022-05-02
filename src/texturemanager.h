#pragma once

#include "resource.h"
#include "resourcemanager.h"

#include <SFML/Graphics.hpp>

#include <iostream>

class TextureManager : public ResourceManager<TextureManager, sf::Texture>
{
public:
	// TODO fix
	TextureManager() : ResourceManager{ {}, "TEXTURE" }
	{}

	sf::Texture* load(ResInfo resource)
	{
		sf::Texture* texture = new sf::Texture;
		if (!texture->loadFromMemory(resource.first, resource.second))
		{
			delete texture;
			texture = nullptr;
			std::cerr << "Failed loading texture\n";
		}

		return texture;
	}
};