#include "eventmanager.h"
#include "statemanager.h"
#include "stateidle.h"

#include <iostream>

StateIdle::StateIdle(StateManager* state_mgr) : BaseState{ state_mgr }
{
	m_info.label = "Start";
	m_info.character_size = 60;
	m_info.size = { 208.f, 104.f };
	m_info.button_position = { 900.f, 200.f };
	m_info.label_color = sf::Color::Magenta;
	m_info.button_color = sf::Color::Red;
}

void StateIdle::onCreate()
{
	m_transparent = true;

	EventManager* ev_mgr = m_state_manager->getContext()->m_event_manager;
	ev_mgr->addDelegate(StateType::StartGame, "LMB", this, &StateIdle::onButtonClick);

	FontManager* font_mgr = m_state_manager->getContext()->m_font_manager;
	font_mgr->requireResource(IDR_CYR);

	m_button_text.setFont(*font_mgr->getResource(IDR_CYR));
	m_button_text.setString(m_info.label);
	m_button_text.setCharacterSize(m_info.character_size);
	m_button_text.setFillColor(m_info.label_color);

	// Set button text origin to center
	sf::FloatRect rect = m_button_text.getLocalBounds();
	m_button_text.setOrigin(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);

	m_button_shape.setSize(m_info.size);
	m_button_shape.setFillColor(sf::Color{ 255, 0, 0, 200 });
}

void StateIdle::onDestroy()
{
	EventManager* ev_mgr = m_state_manager->getContext()->m_event_manager;
	ev_mgr->removeDelegate(StateType::StartGame, "LMB");

	FontManager* font_mgr = m_state_manager->getContext()->m_font_manager;
	font_mgr->releaseResource(IDR_CYR);

	std::cout << __FUNCTION__ << '\n';
}

void StateIdle::onActivation()
{
	m_active = true;
	std::cout << __FUNCTION__ << '\n';
}

void StateIdle::onDeactivation()
{
	//m_active = false;
	std::cout << __FUNCTION__ << '\n';
}

void StateIdle::update(const sf::Time& delta_seconds)
{}

void StateIdle::draw()
{
	Window* window = m_state_manager->getContext()->m_window;
	sf::Vector2u window_size = window->size();

	m_button_shape.setPosition(m_info.button_position);
	sf::FloatRect rect = m_button_shape.getGlobalBounds();
	m_button_text.setPosition(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);

	window->draw(m_button_shape);
	window->draw(m_button_text);
}

void StateIdle::onButtonClick(EventDetails* details)
{
	if (!m_active) { return; }

	sf::Vector2f mouse_pos = static_cast<sf::Vector2f>(details->m_mouse_pos);
	if (m_button_shape.getGlobalBounds().contains(mouse_pos))
	{
		std::cout << "Clicked Start!\n";
		m_state_manager->switchTo(StateType::Game);
	}
}