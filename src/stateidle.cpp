#include "eventmanager.h"
#include "slot.h"
#include "statemanager.h"
#include "stateidle.h"

StateIdle::StateIdle(StateManager* state_mgr) : BaseState{ state_mgr }, m_slot{ m_state_manager->getContext(), kReelsCount }
{
	m_transparent = true;
	m_allows_updating = true;
	m_state_manager->getContext()->m_slot = &m_slot;
}

void StateIdle::onCreate()
{
	EventManager* ev_mgr = m_state_manager->getContext()->m_event_manager;
	ev_mgr->addDelegate(StateType::StartGame, "LMB", this, &StateIdle::onButtonClick);
}

void StateIdle::onDestroy()
{
	EventManager* ev_mgr = m_state_manager->getContext()->m_event_manager;
	ev_mgr->removeDelegate(StateType::StartGame, "LMB");
}

void StateIdle::onActivation()
{}

void StateIdle::onDeactivation()
{}

void StateIdle::update([[maybe_unused]] float dt)
{}

void StateIdle::draw()
{}

void StateIdle::onButtonClick(EventDetails* details)
{
	Slot* slot = m_state_manager->getContext()->m_slot;

	sf::Vector2f mouse_pos = static_cast<sf::Vector2f>(details->m_mouse_pos);
	if (const sf::RectangleShape* shape = slot->getButtonByName("Start"))
	{
		if (shape->getGlobalBounds().contains(mouse_pos))
		{
			// Remove calculate win state here so if player hit start winning text disappears
			m_state_manager->addToRemove(StateType::EndGame);
			m_state_manager->switchTo(StateType::Game);
		}
	}
}