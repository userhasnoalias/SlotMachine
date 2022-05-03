#pragma once

#include "commontypes.h"
#include "resource.h"

#include <SFML/Graphics.hpp>

#include <string>

struct ButtonInfo
{
	sf::Vector2f size;

	sf::Vector2f button_position;

	std::string label;

	sf::Color label_color;

	sf::Color button_color;

	int32 character_size = 50;

	int32 font = IDR_CYR;
};
