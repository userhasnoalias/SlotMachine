#pragma once

#include "basestate.h"

class Slot;

class StateCalculateWin : public BaseState
{
public:

	StateCalculateWin(StateManager* state_mgr);

	virtual void onCreate() override;

	virtual void onDestroy() override;

	virtual void onActivation() override;

	virtual void onDeactivation() override;

	virtual void update(float dt) override;

	virtual void draw() override;

private:

	Slot* m_slot;
};