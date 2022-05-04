#pragma once

#include "constants.h"

#include <SFML/Graphics.hpp>

#include <string>
#include <unordered_map>
#include <vector>

struct SharedContext;
class Button;
class Reel;

using IconContainer = std::unordered_map<std::string, sf::Sprite*>;

class Slot
{
public:

	Slot(SharedContext* context, int32 reel_count);

	~Slot();

	void update(float dt);

	void draw();

	const sf::RectangleShape* getButtonByName(const std::string& name);

	const IconContainer* getIconSprites() const;

private:

	void createButtons();

	void createIconSprites();

	void createReels(int32 count);

	SharedContext* m_context;

	sf::Sprite m_background;

	std::vector<Button> m_buttons;

	IconContainer m_icons;

	std::vector<Reel> m_reels;
};
