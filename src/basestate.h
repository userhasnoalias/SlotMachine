#pragma once

#include "SFML/Graphics.hpp"

class StateManager;

class BaseState
{
public:

	BaseState(StateManager* state_mgr) : m_state_manager{ state_mgr }
	{}

	virtual ~BaseState() = default;

	virtual void onCreate() = 0;

	virtual void onDestroy() = 0;

	// Fired on a new stated that was just switched to
	virtual void onActivation() = 0;

	// Fired on an old state that was just removed/moved back
	virtual void onDeactivation() = 0;

	virtual void update(const sf::Time& delta_seconds) = 0;

	virtual void draw() = 0;

	void setTransparent(bool value) { m_transparent = value; }

	bool isTransparent() const { return m_transparent; }

	void setAllowsUpdating(bool value) { m_allows_updating = value; }

	bool doesAllowUpdating() const { return m_allows_updating; }

	bool isActive() const { return m_active; }
protected:

	StateManager* m_state_manager;

	// If state is transparent then it is drawn on top of previous state
	bool m_transparent = false;

	// If this state allows updating states below on stack
	bool m_allows_updating = false;

	// If the current state is active now
	bool m_active = false;
};