#pragma once

#include "basestate.h"

class Slot;
class Window;

using WinningPositionsContainer = std::vector<sf::Vector2f>;
using WinLinesContainer = std::vector<sf::Vector2f>;

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

	void drawWinPositions(Window* window);

	void drawLines(Window* window);

	void drawWinText(Window* window);

	std::string chooseWinningString(int32 string_num);

	void initializeText(const std::string& str);

	Slot* m_slot;
	// Winning text
	sf::Text m_text;

	// Game time when this state has been activated
	float m_activation_time = 0.f;

	const float m_show_text_time = 3.f;

	WinLinesContainer m_win_lines;

	WinningPositionsContainer m_win_positions;

	// This is set to false when winning message is shown more than m_show_text_time seconds
	bool m_draw = true;

	// This will be true if there is at least 1 winning line
	bool m_win = false;
};