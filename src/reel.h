#pragma once

#include "commontypes.h"

#include <SFML/Graphics.hpp>

#include <cassert>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

class Slot;
class Window;

// We use string to find appropriate sprite from Slot class icon container
using IconWheelContainer = std::vector<std::pair<std::string_view, sf::Vector2f>>;

struct ReelIconOrders
{
	// Get unique icon order for each reel
	static const std::vector<std::string>& getIconOrderForReel()
	{
		static int32 s_reel_number = 0;
		++s_reel_number;
		switch (s_reel_number)
		{
		case 1:
			return s_reel1;
		default:
			assert(false && "Reel is not initialized with icon order!");
			return s_reel1;
		}
	}

	static const std::vector<std::string> s_reel1;
};

class Reel
{
public:
	Reel(Slot* owner, const sf::Vector2f& positon);

	void update(float dt);

	void draw(Window* window);

	void setSpeed(float speed);

private:

	Slot* m_slot;

	sf::Vector2f m_position;

	IconWheelContainer m_icons;

	// Current reel speed
	float m_speed = 50.f;

	// Speed reel is going to achieve
	float m_target_speed = 500.f;

	float m_acceleration = 250.f;

	// Indicates if the current reel is not spinning or should stop spinning
	bool m_stopped = true;
};