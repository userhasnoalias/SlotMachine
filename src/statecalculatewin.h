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

	void initializeText();

	Slot* m_slot;

	sf::Text m_text;

	// Game time when this state has been activated
	float m_activation_time = 0.f;

	const float m_show_text_time = 3.f;

	bool m_draw = true;
};