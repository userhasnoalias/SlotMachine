#pragma once

#include "basestate.h"
#include "reel.h"

#include <unordered_set>

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

	bool calculateWin();
private:

	std::string chooseWinningString(int32 string_num);

	void initializeText(const std::string& str);

	Slot* m_slot;
	// Winning text
	sf::Text m_text;

	// Game time when this state has been activated
	float m_activation_time = 0.f;

	const float m_show_text_time = 3.f;

	IconWheelContainer m_win_lines;

	// This is set to false when winning message is shown more than m_show_text_time seconds
	bool m_draw = true;

	// This will be true if there is at least 1 winning line
	bool m_win = false;
};