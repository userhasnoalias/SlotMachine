#include "engine.h"

Engine::Engine() : m_window{ {1200u, 720u}, "Slot Machine" }, m_state_manager{ &m_context }
{
	m_clock.restart();

	m_context.m_window = &m_window;
	m_context.m_event_manager = m_window.getEventManager();
	m_context.m_texture_manager = &m_state_manager.m_texture_manager;
	m_context.m_font_manager = &m_state_manager.m_font_manager;

	// StartGame should go first as it creates Slot class on which other states rely on upon constructing
	m_state_manager.createState(StateType::StartGame);
	m_state_manager.createState(StateType::Game);
	m_state_manager.switchTo(StateType::StartGame);
}

Engine& Engine::get()
{
	static Engine instance;
	return instance;
}

void Engine::update()
{
	m_window.update();
	m_state_manager.update(m_elapsed.asSeconds());
}

void Engine::render()
{
	m_window.startDraw();
	m_state_manager.draw();
	m_window.endDraw();
}

void Engine::lateUpdate()
{
	m_state_manager.processRemovals();
	restartClock();
}

float Engine::getElapsed() const
{
	return m_clock.getElapsedTime().asSeconds();
}

float Engine::getGameTimeSeconds() const
{
	return m_total_played_time;
}

Window* Engine::getWindow()
{
	return &m_window;
}

void Engine::restartClock()
{
	m_elapsed = m_clock.restart();
	m_total_played_time += m_elapsed.asSeconds();
}
