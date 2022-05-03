#include "button.h"
#include "sharedcontext.h"
#include "window.h"

Button::Button(SharedContext* context, const ButtonInfo& info) : m_context{ context }, m_name{info.label}, 
	m_position{ info.button_position }, m_font_id{ info.font }
{
	FontManager* font_mgr = m_context->m_font_manager;
	font_mgr->requireResource(m_font_id);

	m_text.setFont(*font_mgr->getResource(m_font_id));
	m_text.setString(info.label);
	m_text.setCharacterSize(info.character_size);
	m_text.setFillColor(info.label_color);

	// Set button text origin to center
	sf::FloatRect rect = m_text.getLocalBounds();
	m_text.setOrigin(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);

	m_shape.setSize(info.size);
	m_shape.setFillColor(sf::Color{ 255, 0, 0, 200 });
}

Button::~Button()
{
	FontManager* font_mgr = m_context->m_font_manager;
	font_mgr->releaseResource(m_font_id);
}

void Button::draw()
{
	Window* window = m_context->m_window;
	sf::Vector2u window_size = window->size();

	m_shape.setPosition(m_position);
	sf::FloatRect rect = m_shape.getGlobalBounds();
	m_text.setPosition(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);

	window->draw(m_shape);
	window->draw(m_text);
}

sf::RectangleShape* Button::getShape()
{
	return &m_shape;
}

sf::Vector2f Button::getPosition() const
{
	return m_position;
}

bool operator==(const Button& button, const std::string& str)
{
	return button.m_name == str;
}

bool operator==(const std::string& str, const Button& button)
{
	return button == str;
}
