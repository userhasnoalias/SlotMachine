#include "statemanager.h"
#include "statestop.h"

#include <iostream>

StateStop::StateStop(StateManager* state_mgr) : BaseState{state_mgr}, m_slot{m_state_manager->getContext()->m_slot}
{
	m_transparent = true;
	m_slot->bindOnReelStop(this, &StateStop::onReelStop);
}

void StateStop::onCreate()
{}

void StateStop::onDestroy()
{}

void StateStop::onActivation()
{
	m_active = true;
	m_count_reels_to_stop = 1;
	std::cout << __FUNCTION__ << '\n';
}

void StateStop::onDeactivation()
{
	m_active = false;
	std::cout << __FUNCTION__ << '\n';
}

void StateStop::update(float dt)
{
	// This check is used to prevent this state from updating when stateidle is on top of state stack
	// e.g. StateGame<---StateStop<---StateIdle
	// We want stateidle to allow updating only statecalculatewin, so winning text shows appropriately
	if (!m_active) { return; }

	if (m_count_reels_to_stop > m_slot->getReelsCount())
	{
		m_state_manager->switchTo(StateType::EndGame);
		return;
	}

	m_slot->spinCountReelsFromEnd(dt, m_slot->getReelsCount() - m_count_reels_to_stop);
	m_slot->stopReels(dt, m_count_reels_to_stop);
}

void StateStop::draw()
{}

void StateStop::onReelStop([[maybe_unused]] int32 reel_number)
{
	// Increase count reels to stop each time next reel stops
	++m_count_reels_to_stop;
}
