#include "engine.h"

Engine::Engine() : m_window{ {1200u, 720u}, "Slot Machine" }, m_state_manager{ &m_context }
{
	m_clock.restart();

	m_context.m_window = &m_window;
	m_context.m_event_manager = m_window.getEventManager();
	m_context.m_texture_manager = &m_state_manager.m_texture_manager;
	m_context.m_font_manager = &m_state_manager.m_font_manager;

	// TODO: should fix this
	m_state_manager.createState(StateType::StartGame);
	m_state_manager.createState(StateType::Game);
	m_state_manager.switchTo(StateType::StartGame);
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

sf::Time Engine::getElapsed() const
{
	return m_clock.getElapsedTime();
}

Window* Engine::getWindow()
{
	return &m_window;
}

void Engine::restartClock()
{
	m_elapsed = m_clock.restart();
}
