#pragma once

#include "buttoninfo.h"
#include "commontypes.h"

#include <SFML/Graphics.hpp>

#include <string>

struct ButtonInfo;
class Window;
struct SharedContext;

class Button
{
public:

	Button(SharedContext* context, const ButtonInfo& info = ButtonInfo());

	~Button();

	void draw();

	sf::RectangleShape* getShape();

	sf::Vector2f getPosition() const;

	friend bool operator==(const Button& button, const std::string& str);

	friend bool operator==(const std::string& str, const Button& button);

private:

	SharedContext* m_context;

	sf::Text m_text;

	sf::RectangleShape m_shape;

	std::string m_name;

	sf::Vector2f m_position;

	int32 m_font_id = -1;
};