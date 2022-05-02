#pragma once

#include "basestate.h"
#include "buttoninfo.h"

class StateIdle : public BaseState
{
public:

	StateIdle(StateManager* state_mgr);

	~StateIdle() = default;

	virtual void onCreate() override;

	virtual void onDestroy() override;

	virtual void onActivation() override;

	virtual void onDeactivation() override;

	virtual void update(const sf::Time& delta_seconds) override;

	virtual void draw() override;

	void onButtonClick(EventDetails* details);
private:
	
	sf::Text m_button_text;

	sf::RectangleShape m_button_shape;

	ButtonInfo m_button;
};
