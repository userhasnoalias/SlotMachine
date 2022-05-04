#pragma once

#include "eventmanager.h"
#include "statemanager.h"
#include "texturemanager.h"
#include "window.h"

#include <SFML/Graphics.hpp>


class Engine final
{
	Engine();
public:

	Engine(const Engine&) = delete;

	Engine& operator=(Engine) = delete;

	static Engine& get();

	void update();

	void render();

	void lateUpdate();

	float getElapsed() const;

	float getGameTimeSeconds() const;

	Window* getWindow();
private:

	void restartClock();

	sf::Clock m_clock;
	
	sf::Time m_elapsed;

	// In seconds
	float m_total_played_time = 0.f;

	SharedContext m_context;

	Window m_window;

	StateManager m_state_manager;
};