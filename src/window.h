#pragma once

#include "eventmanager.h"

#include <SFML/Graphics.hpp>

#include <string>

class Window final
{
public:

	Window();

	Window(const sf::Vector2u& size, const std::string& title);

	~Window();

	void startDraw();

	void endDraw();

	void update();

	void draw(sf::Drawable& drawable);

	void close(EventDetails* details);

	bool isClosed() const;

	sf::Vector2u size() const;

	sf::RenderWindow* getRenderWindow();

	EventManager* getEventManager();
private:

	void create();

	sf::RenderWindow m_window;

	EventManager m_event_manager;

	sf::Vector2u m_size;

	sf::Vector2u m_default_size;

	std::string m_title;

	bool m_closed = false;
};