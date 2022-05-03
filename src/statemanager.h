#pragma once

#include "basestate.h"
#include "fontmanager.h"
#include "sharedcontext.h"
#include "stategame.h"
#include "stateidle.h"
// include every state.h
#include "texturemanager.h"

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
	friend class Engine;
public:

	StateManager(SharedContext* context);

	~StateManager();

	// This function will remove unnecessary states at the end of game loop
	void processRemovals();

	void update(float dt);

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

	/* Should be here so StateManager controls the lifetime of TextureManager & FontManager*/
	TextureManager m_texture_manager;

	FontManager m_font_manager;

	StateContainer m_states;

	TypeContainer m_states_to_remove;

	StateFactory m_factory;
};