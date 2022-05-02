#pragma once

#include "basestate.h"
#include "sharedcontext.h"
// include every state.h

#include "SFML/Graphics.hpp"

#include <functional>
#include <tuple>
#include <unordered_map>
#include <vector>

enum class StateType
{
	Global,
	StartGame,
	Game,
	EndGame,
};

// Vector is used as stack for states, where the top stack element is current active state
using StateContainer = std::vector<std::pair<StateType, BaseState*>>;

using TypeContainer = std::vector<StateType>;

using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>>;

class StateManager final
{
public:

	StateManager(SharedContext* context);

	~StateManager();

	// This function will remove unnecessary states at the end of game loop
	void processRemovals();

	void update(const sf::Time& delta_seconds);

	void draw();

	void switchTo(StateType type);

	void addToRemove(StateType type);

	SharedContext* getContext();
private:

	void createState(StateType type);

	void removeState(StateType type);

	template<class T>
	void registerState(StateType type)
	{
		m_factory[type] = [this]() -> BaseState* { return new T(this); };
	}

	SharedContext* m_context;

	StateContainer m_states;

	TypeContainer m_states_to_remove;

	StateFactory m_factory;
};