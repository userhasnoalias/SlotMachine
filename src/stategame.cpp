#include "eventmanager.h"
#include "stategame.h"
#include "statemanager.h"

#include <iostream>

StateGame::StateGame(StateManager* state_mgr) : BaseState{ state_mgr }, m_slot{ m_state_manager->getContext()->m_slot }
{}

void StateGame::onCreate()
{
	m_transparent = true;

	EventManager* ev_mgr = m_state_manager->getContext()->m_event_manager;
	ev_mgr->addDelegate(StateType::Game, "LMB", this, &StateGame::onButtonClick);
}

void StateGame::onDestroy()
{
	EventManager* ev_mgr = m_state_manager->getContext()->m_event_manager;
	ev_mgr->removeDelegate(StateType::Game, "LMB");

	std::cout << __FUNCTION__ << '\n';
}

void StateGame::onActivation()
{
	std::cout << __FUNCTION__ << '\n';
}

void StateGame::onDeactivation()
{
	std::cout << __FUNCTION__ << '\n';
}

void StateGame::update([[maybe_unused]] float dt)
{

}

void StateGame::draw()
{

}

void StateGame::onButtonClick(EventDetails* details)
{
	Slot* slot = m_state_manager->getContext()->m_slot;

	sf::Vector2f mouse_pos = static_cast<sf::Vector2f>(details->m_mouse_pos);
	if (const sf::RectangleShape* shape = slot->getButtonByName("Stop"))
	{
		if (shape->getGlobalBounds().contains(mouse_pos))
		{
			std::cout << "Clicked Stop!\n";
			//m_state_manager->switchTo(StateType::EndGame);
		}
	}
}
