#include "statemanager.h"

StateManager::StateManager(SharedContext* context) : m_context{ context }
{
	registerState<StateIdle>(StateType::StartGame);
	registerState<StateGame>(StateType::Game);
	registerState<StateStop>(StateType::PreEndGame);
	registerState<StateCalculateWin>(StateType::EndGame);
}

StateManager::~StateManager()
{
	for (auto& state : m_states)
	{
		state.second->onDestroy();
		delete state.second;
	}
}

void StateManager::processRemovals()
{
	while (m_states_to_remove.begin() != m_states_to_remove.end())
	{
		removeState(*m_states_to_remove.begin());
		m_states_to_remove.erase(m_states_to_remove.begin());
	}
}

void StateManager::update(float dt)
{
	if (m_states.empty()) { return; }

	// If we need to update more than 1 state at once ->
	// traverse through state array until we find state that doesn't allow updating states below
	if (m_states.back().second->doesAllowUpdating() && m_states.size() > 1)
	{
		auto it = m_states.end();
		while (it != m_states.begin())
		{
			if (it != m_states.end())
			{
				if (!it->second->doesAllowUpdating())
				{
					break;
				}
			}
			--it;
		}

		for (; it != m_states.end(); ++it)
		{
			it->second->update(dt);
		}
	}
	else
	{
		m_states.back().second->update(dt);
	}
}

void StateManager::draw()
{
	if (m_states.empty()) { return; }

	// Same as with update method
	if (m_states.back().second->isTransparent() && m_states.size() > 1)
	{
		auto it = m_states.end();
		while (it != m_states.begin())
		{
			if (it != m_states.end())
			{
				if (!it->second->isTransparent())
				{
					break;
				}
			}
			--it;
		}
	
		for (; it != m_states.end(); ++it)
		{
			it->second->draw();
		}
	}
	else
	{
		m_states.back().second->draw();
	}
}

void StateManager::switchTo(StateType type)
{
	m_context->m_event_manager->setCurrentState(type);

	for (auto it = m_states.begin(); it != m_states.end(); ++it)
	{
		if (it->first == type)
		{
			m_states.back().second->onDeactivation();
			StateType tmp_type = it->first;
			BaseState* tmp_base = it->second;
			m_states.erase(it);
			m_states.emplace_back(tmp_type, tmp_base);
			m_states.back().second->onActivation();
			return;
		}
	}

	if (!m_states.empty()) { m_states.back().second->onDeactivation(); }
	createState(type);
	m_states.back().second->onActivation();
}

void StateManager::addToRemove(StateType type)
{
	m_states_to_remove.emplace_back(type);
}

SharedContext* StateManager::getContext()
{
	return m_context;
}

void StateManager::createState(StateType type)
{
	auto it = m_factory.find(type);
	if (it != m_factory.end())
	{
		BaseState* state = it->second();
		m_states.emplace_back(type, state);
		m_states.back().second->onCreate();
	}
}

void StateManager::removeState(StateType type)
{
	for (auto it = m_states.begin(); it != m_states.end(); ++it)
	{
		if (it->first == type)
		{
			it->second->onDestroy();
			delete it->second;
			m_states.erase(it);
			return;
		}
	}
}


