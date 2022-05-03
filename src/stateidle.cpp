#include "eventmanager.h"
#include "slot.h"
#include "statemanager.h"
#include "stateidle.h"

#include <iostream>

StateIdle::StateIdle(StateManager* state_mgr) : BaseState{ state_mgr }, m_slot{ m_state_manager->getContext() }
{
	m_state_manager->getContext()->m_slot = &m_slot;
}

void StateIdle::onCreate()
{
	m_transparent = true;

	EventManager* ev_mgr = m_state_manager->getContext()->m_event_manager;
	ev_mgr->addDelegate(StateType::StartGame, "LMB", this, &StateIdle::onButtonClick);
}

void StateIdle::onDestroy()
{
	EventManager* ev_mgr = m_state_manager->getContext()->m_event_manager;
	ev_mgr->removeDelegate(StateType::StartGame, "LMB");

	std::cout << __FUNCTION__ << '\n';
}

void StateIdle::onActivation()
{
	m_active = true;
	std::cout << __FUNCTION__ << '\n';
}

void StateIdle::onDeactivation()
{
	//m_active = false;
	std::cout << __FUNCTION__ << '\n';
}

void StateIdle::update([[maybe_unused]] float dt)
{}

void StateIdle::draw()
{
	m_state_manager->getContext()->m_slot->draw();
}

void StateIdle::onButtonClick(EventDetails* details)
{
	Slot* slot = m_state_manager->getContext()->m_slot;

	sf::Vector2f mouse_pos = static_cast<sf::Vector2f>(details->m_mouse_pos);
	if (const sf::RectangleShape* shape = slot->getButtonByName("Start"))
	{
		if (shape->getGlobalBounds().contains(mouse_pos))
		{
			std::cout << "Clicked Start!\n";
			m_state_manager->switchTo(StateType::Game);
		}
	}
}