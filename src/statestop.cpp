#include "statemanager.h"
#include "statestop.h"

#include <iostream>

StateStop::StateStop(StateManager* state_mgr) : BaseState{state_mgr}, m_slot{m_state_manager->getContext()->m_slot}
{
	m_transparent = true;
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
}

void StateStop::onDeactivation()
{
}

void StateStop::update(float dt)
{
	// TODO: magic number
	m_slot->stopReels(dt, 2);
}

void StateStop::draw()
{
}
