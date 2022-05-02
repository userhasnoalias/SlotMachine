#pragma once

#include "eventmanager.h"
#include "statemanager.h"
#include "texturemanager.h"
#include "window.h"

#include <SFML/Graphics.hpp>


class Engine final
{
public:

	Engine();

	void update();

	void render();

	void lateUpdate();

	sf::Time getElapsed() const;

	Window* getWindow();
private:

	void restartClock();

	sf::Clock m_clock;
	
	sf::Time m_elapsed;

	SharedContext m_context;

	Window m_window;

	StateManager m_state_manager;

	TextureManager m_texture_manager;

	FontManager m_font_manager;
};