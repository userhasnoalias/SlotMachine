#include "stategame.h"

StateGame::StateGame(StateManager* state_mgr) : BaseState{ state_mgr }
{

}

void StateGame::onCreate()
{
	m_transparent = true;
}

void StateGame::onDestroy()
{
}

void StateGame::onActivation()
{
}

void StateGame::onDeactivation()
{
}

void StateGame::update(const sf::Time& delta_seconds)
{
}

void StateGame::draw()
{
}
