#pragma once

#include "resource.h"
#include "resourcemanager.h"

#include <SFML/Graphics.hpp>

#include <iostream>

class FontManager : public ResourceManager<FontManager, sf::Font>
{
public:
	FontManager() : ResourceManager{ {}, MAKEINTRESOURCEA(8) }
	{}

	sf::Font* load(ResInfo resource)
	{
		sf::Font* font = new sf::Font;
		if (!font->loadFromMemory(resource.first, resource.second))
		{
			delete font;
			font = nullptr;
			std::cerr << "Failed loading font\n";
		}

		return font;
	}
};