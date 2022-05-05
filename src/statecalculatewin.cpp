#include "statecalculatewin.h"
#include "statemanager.h"

StateCalculateWin::StateCalculateWin(StateManager* state_mgr) : BaseState{ state_mgr }, 
	m_slot{ m_state_manager->getContext()->m_slot }
{
	m_transparent = true;
}

void StateCalculateWin::onCreate()
{}

void StateCalculateWin::onDestroy()
{}

void StateCalculateWin::onActivation()
{
	std::cout << "Calculating win condition!\n";
}

void StateCalculateWin::onDeactivation()
{}

void StateCalculateWin::update(float dt)
{
}

void StateCalculateWin::draw()
{}