#pragma once

#include "basestate.h"
#include "buttoninfo.h"

class Slot;

class StateIdle : public BaseState
{
public:

	StateIdle(StateManager* state_mgr);

	~StateIdle() = default;

	virtual void onCreate() override;

	virtual void onDestroy() override;

	virtual void onActivation() override;

	virtual void onDeactivation() override;

	virtual void update(float dt) override;

	virtual void draw() override;

	void onButtonClick(EventDetails* details);
private:
	
	Slot m_slot;
};
