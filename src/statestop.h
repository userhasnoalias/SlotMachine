#pragma once

#include "basestate.h"
#include "commontypes.h"

class Slot;

class StateStop : public BaseState
{
public:

	StateStop(StateManager* state_mgr);

	virtual void onCreate() override;

	virtual void onDestroy() override;

	virtual void onActivation() override;

	virtual void onDeactivation() override;

	virtual void update(float dt) override;

	virtual void draw() override;

private:

	void onReelStop(int32 reel_number);

	Slot* m_slot;

	int32 m_count_reels_to_stop = 1;
};