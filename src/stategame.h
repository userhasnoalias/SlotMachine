#pragma once

#include "basestate.h"
#include "buttoninfo.h"

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

	sf::Text m_button_text;

	sf::RectangleShape m_button_shape;

	ButtonInfo m_info;
};
