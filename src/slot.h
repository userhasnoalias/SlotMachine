#pragma once

#include "constants.h"
#include "reel.h"

#include <SFML/Graphics.hpp>

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

struct SharedContext;
class Button;
class Reel;

// This maps each fruit sprite to a string
using IconContainer = std::unordered_map<std::string, sf::Sprite*>;

using OnReelStopDelegate = std::function<void(int32)>;

class Slot
{
	friend class Reel;

public:

	Slot(SharedContext* context, int32 reel_count);

	~Slot();

	// Spin all reels for this slot
	void spinReels(float dt);

	// Spin count reels starting from the last, e.g. count = 1 will only spin the last reel for this slot
	void spinCountReelsFromEnd(float dt, int32 count);

	// Stop spinning count reels from first reel, e.g. count = 2 will stop 1st and 2nd reel
	void stopReels(float dt, int32 count = 1);

	void resetReelsSpeed(float speed);

	void draw();

	int32 getReelsCount() const;

	const sf::RectangleShape* getButtonByName(const std::string& name);

	const IconContainer* getIconSprites() const;

	IconWheelContainer getAllVisibleIcons() const;

	// Bind to signle cast delegate
	template<class T>
	void bindOnReelStop(T* object, void(T::*func)(int32))
	{
		m_on_reel_stop = std::bind(func, object, std::placeholders::_1);
	}

private:
	// Fires when each reel stops, reel_number starts from 1
	void onReelStop(int32 reel_number);

	void createButtons();

	void createIconSprites();

	void createReels(int32 count);

	SharedContext* m_context;

	sf::Sprite m_background;

	sf::Sprite m_slot_tile;

	std::vector<Button> m_buttons;

	IconContainer m_icons;

	std::vector<Reel> m_reels;

	OnReelStopDelegate m_on_reel_stop;
};
