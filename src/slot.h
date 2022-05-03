#pragma once

#include "constants.h"

#include <SFML/Graphics.hpp>

#include <string>
#include <vector>

struct SharedContext;
class Button;

class Slot
{
public:

	Slot(SharedContext* context);

	~Slot();

	void update(float dt);

	void draw();

	const sf::RectangleShape* getButtonByName(const std::string& name);

private:

	void createButtons();

	SharedContext* m_context;

	sf::Sprite m_background;

	std::vector<Button> m_buttons;
};
