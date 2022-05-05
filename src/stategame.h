#pragma once

#include "basestate.h"
#include "buttoninfo.h"

class Slot;

/*	This state is responsible for actual rendering slot/reels on the screen.
**	It is done so, because we want StateCalculateWin to draw winning text on top of screen even after
**	transition to StateIdle took place. After transition to this state StateCalculateWin is always destroyed,
**	so winning text will not render when player started spinning reels.
*/
class StateGame : public BaseState
{
public:
	StateGame(StateManager* state_mgr);

	~StateGame() = default;

	virtual void onCreate() override;

	virtual void onDestroy() override;

	virtual void onActivation() override;

	virtual void onDeactivation() override;

	virtual void update(float dt) override;

	virtual void draw() override;

	void onButtonClick(EventDetails* details);
private:

	Slot* m_slot;
};
