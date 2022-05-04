#pragma once

#include "constants.h"

#include <SFML/Graphics.hpp>

//#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

struct SharedContext;
class Button;
class Reel;

// This maps each fruit sprite to a string
using IconContainer = std::unordered_map<std::string, sf::Sprite*>;

//using SingleDelegate = std::function<void()>;

class Slot
{
public:

	Slot(SharedContext* context, int32 reel_count);

	~Slot();

	void spinReels(float dt);

	void draw();

	const sf::RectangleShape* getButtonByName(const std::string& name);

	const IconContainer* getIconSprites() const;

	//template<class T>
	//void bindOnTimerEnd(T* object, void(T::* func)())
	//{
	//	onTimerEnd = std::bind(func, object);
	//}

private:

	void createButtons();

	void createIconSprites();

	void createReels(int32 count);

	SharedContext* m_context;

	sf::Sprite m_background;

	std::vector<Button> m_buttons;

	IconContainer m_icons;

	std::vector<Reel> m_reels;

	//float m_spin_time = 5.f;

	//SingleDelegate onTimerEnd;
};
