#include "engine.h"
#include "statecalculatewin.h"
#include "statemanager.h"

StateCalculateWin::StateCalculateWin(StateManager* state_mgr) : BaseState{ state_mgr },
	m_slot{ m_state_manager->getContext()->m_slot }
{
	m_transparent = true;
}

void StateCalculateWin::onCreate()
{
	FontManager* font_mgr = m_state_manager->getContext()->m_font_manager;
	font_mgr->requireResource(IDR_CYR);
	std::cout << __FUNCTION__ << '\n';
}

void StateCalculateWin::onDestroy()
{
	std::cout << __FUNCTION__ << '\n';
	FontManager* font_mgr = m_state_manager->getContext()->m_font_manager;
	font_mgr->releaseResource(IDR_CYR);
}

void StateCalculateWin::onActivation()
{
	m_activation_time = Engine::get().getGameTimeSeconds();

	initializeText();

	m_state_manager->switchTo(StateType::StartGame);
}

void StateCalculateWin::onDeactivation()
{
	std::cout << __FUNCTION__ << '\n';
}

void StateCalculateWin::update(float dt)
{
	if (Engine::get().getGameTimeSeconds() - m_activation_time >= m_show_text_time)
	{
		m_draw = false;
	}
}

void StateCalculateWin::draw()
{
	if (m_draw)
	{
		Window* window = m_state_manager->getContext()->m_window;
		sf::Vector2u wnd_size = window->size();

		m_text.setPosition(wnd_size.x / 2.f, wnd_size.y / 4.f);
		window->draw(m_text);
	}
}

void StateCalculateWin::initializeText()
{
	FontManager* font_mgr = m_state_manager->getContext()->m_font_manager;
	m_text.setFont(*font_mgr->getResource(IDR_CYR));
	m_text.setString("  You've won! Congrats!\nDo you wish to play again?");
	m_text.setCharacterSize(60);
	m_text.setFillColor(sf::Color::Magenta);
	sf::FloatRect rect = m_text.getLocalBounds();
	m_text.setOrigin(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);
}
