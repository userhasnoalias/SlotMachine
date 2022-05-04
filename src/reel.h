#pragma once

#include "commontypes.h"

#include <SFML/Graphics.hpp>

#include <cassert>
#include <iostream>
#include <string>
#include <vector>

class Slot;
class Window;

using IconWheelContainer = std::vector<std::pair<std::string, sf::Vector2f>>;

struct ReelIconOrders
{
	// Get unique icon order for each reel
	static std::vector<std::string> getIconOrderForReel()
	{
		static int32 s_reel_number = 0;
		++s_reel_number;
		switch (s_reel_number)
		{
		case 1:
			return { "Orange", "Watermelon", "7", "Banana" };
		default:
			assert(false && "Reel is not initialized with icon order!");
			return {};
		}
	}
};

class Reel
{
public:
	Reel(Slot* owner, const sf::Vector2f& positon);

	void update(float dt);

	void draw(Window* window);

private:

	Slot* m_slot;

	sf::Vector2f m_position;

	IconWheelContainer m_icons;

	float m_speed = 100.f;
};