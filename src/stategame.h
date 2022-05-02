#pragma once

#include "basestate.h"

class StateGame : public BaseState
{
public:
	StateGame(StateManager* state_mgr);

	~StateGame() = default;

	virtual void onCreate() override;

	virtual void onDestroy() override;

	virtual void onActivation() override;

	virtual void onDeactivation() override;

	virtual void update(const sf::Time& delta_seconds) override;

	virtual void draw() override;
};
