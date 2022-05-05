#include "statemanager.h"
#include "statestop.h"

#include <iostream>

StateStop::StateStop(StateManager* state_mgr) : BaseState{state_mgr}, m_slot{m_state_manager->getContext()->m_slot}
{
	m_transparent = true;
	m_slot->bindOnReelStop(this, &StateStop::onReelStop);
}

void StateStop::onCreate()
{
	std::cout << __FUNCTION__ << '\n';
}

void StateStop::onDestroy()
{
	std::cout << __FUNCTION__ << '\n';
}

void StateStop::onActivation()
{
	m_count_reels_to_stop = 1;
}

void StateStop::onDeactivation()
{
}

void StateStop::update(float dt)
{
	if (m_count_reels_to_stop > m_slot->getReelsCount())
	{
		std::cout << "STOP!\n";
		return;
	}

	m_slot->spinCountReelsFromEnd(dt, m_slot->getReelsCount() - m_count_reels_to_stop);
	m_slot->stopReels(dt, m_count_reels_to_stop);
}

void StateStop::draw()
{
}

void StateStop::onReelStop([[maybe_unused]] int32 reel_number)
{
	// Increase count reels to stop each time next reel stops
	++m_count_reels_to_stop;
}
