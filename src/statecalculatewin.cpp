#include "engine.h"
#include "statecalculatewin.h"
#include "statemanager.h"
#include "vectormath.h"

#include <algorithm>
#include <cmath>
#include <iterator>

StateCalculateWin::StateCalculateWin(StateManager* state_mgr) : BaseState{ state_mgr },
	m_slot{ m_state_manager->getContext()->m_slot }
{
	m_transparent = true;
}

void StateCalculateWin::onCreate()
{
	FontManager* font_mgr = m_state_manager->getContext()->m_font_manager;
	font_mgr->requireResource(IDR_CYR);
}

void StateCalculateWin::onDestroy()
{
	FontManager* font_mgr = m_state_manager->getContext()->m_font_manager;
	font_mgr->releaseResource(IDR_CYR);
}

void StateCalculateWin::onActivation()
{
	m_activation_time = Engine::get().getGameTimeSeconds();

	m_win = calculateWin();
	std::string winning_str = chooseWinningString(m_win_lines.size() / 3);
	initializeText(winning_str);

	m_state_manager->switchTo(StateType::StartGame);
}

void StateCalculateWin::onDeactivation()
{}

void StateCalculateWin::update([[maybe_unused]] float dt)
{
	if (Engine::get().getGameTimeSeconds() - m_activation_time >= m_show_text_time)
	{
		m_draw = false;
	}
}

void StateCalculateWin::draw()
{
	if (m_draw && m_win)
	{
		Window* window = m_state_manager->getContext()->m_window;
		
		drawLines(window);
		drawWinPositions(window);
		drawWinText(window);
	}
}

// Hardcoded for 3x3 field
bool StateCalculateWin::calculateWin()
{
	if (kReelsCount != 3 || kVisibleIcons != 3)
	{
		assert(false && "Current implementation only supports 3x3 field!\n");
		return false;
	}

	auto icons = m_slot->getAllVisibleIcons();

	/*	Indicies for visible icons look like this:
	*	0---1---2
	*	3---4---5
	*	6---7---8
	*/

	// Bigwin acts as wild symbol
	for (int32 i = 0; i < kReelsCount * kVisibleIcons; i += 3)
	{
		if (icons[i].first == icons[i + 1].first && icons[i].first == icons[i + 2].first
			|| icons[i].first == "Bigwin" && icons[i + 1].first == icons[i + 2].first
			|| icons[i + 1].first == "Bigwin" && icons[i].first == icons[i + 2].first
			|| icons[i + 2].first == "Bigwin" && icons[i].first == icons[i + 1].first)
		{
			//m_win_lines.insert(m_win_lines.end(), std::next(icons.begin(), i), std::next(icons.begin(), i + 3));
			m_win_lines.emplace_back(icons[i].second);
			m_win_lines.emplace_back(icons[i + 1].second);
			m_win_lines.emplace_back(icons[i + 2].second);
		}
	}

	/*	
	*	0---|---2
	*	|---|---|
	*	|---7---|
	*/
	if (icons[0].first == icons[7].first && icons[0].first == icons[2].first
		|| icons[0].first == "Bigwin" && icons[7].first == icons[2].first
		|| icons[7].first == "Bigwin" && icons[0].first == icons[2].first
		|| icons[2].first == "Bigwin" && icons[0].first == icons[7].first)
	{
		m_win_lines.emplace_back(icons[0].second);
		m_win_lines.emplace_back(icons[7].second);
		m_win_lines.emplace_back(icons[2].second);
	}

	/*
	*	|---1---|
	*	|---|---|
	*	6---|---8
	*/
	if (icons[6].first == icons[1].first && icons[6].first == icons[8].first
		|| icons[6].first == "Bigwin" && icons[1].first == icons[8].first
		|| icons[1].first == "Bigwin" && icons[6].first == icons[8].first
		|| icons[8].first == "Bigwin" && icons[6].first == icons[1].first)
	{
		m_win_lines.emplace_back(icons[6].second);
		m_win_lines.emplace_back(icons[1].second);
		m_win_lines.emplace_back(icons[8].second);
	}

	for (auto& value : m_win_lines)
	{
		auto it = std::find(m_win_positions.begin(), m_win_positions.end(), value);
		if (it == m_win_positions.end())
		{
			m_win_positions.emplace_back(value);
		}
	}

	return !m_win_lines.empty();
}

void StateCalculateWin::drawWinPositions(Window* window)
{
	constexpr float shape_size = 25.f;

	for (auto& position : m_win_positions)
	{
		sf::RectangleShape rect{ sf::Vector2f{shape_size, shape_size} };
		rect.setOrigin(sf::Vector2f{ shape_size / 2.f, shape_size / 2.f }); // Origin to center
		rect.setFillColor(sf::Color{ 255, 215, 0 }); // Gold
		rect.setPosition(sf::Vector2f{ position.x + kIconWidth / 2, position.y + kIconHeight / 2 });
		window->draw(rect);
	}
}

void StateCalculateWin::drawLines(Window* window)
{
	constexpr float line_thickness = 8.f;

	for (int32 i = 0; i < m_win_lines.size() - 1; ++i)
	{
		// We do not draw at 2, 5, and 8 indicies
		if (i % kReelsCount == kReelsCount - 1) { continue; }

		sf::Vector2f dist = m_win_lines[i + 1] - m_win_lines[i];
		const float length = vec::length(dist); // Save distance vector length before normalizing
		
		vec::normalize(dist);
		const float angle = std::atan2f(dist.y, dist.x) * 180.f / PI;

		sf::RectangleShape rect{ sf::Vector2f{ length, line_thickness } };
		rect.setOrigin(sf::Vector2f{ 0.f, line_thickness / 2.f });
		rect.setFillColor(sf::Color{ 255, 215, 0 }); // Gold
		rect.setPosition(m_win_lines[i].x + kIconWidth / 2, m_win_lines[i].y + kIconHeight / 2); // Center of icon
		rect.setRotation(angle);
		window->draw(rect);
	}
}

void StateCalculateWin::drawWinText(Window* window)
{
	//sf::Vector2u wnd_size = window->size();
	//m_text.setPosition(wnd_size.x / 2.f, wnd_size.y / 4.f);
	window->draw(m_text);
}

std::string StateCalculateWin::chooseWinningString(int32 string_num)
{
	std::string result;
	switch (string_num)
	{
	case 1:
		result = "Win!";
		break;
	case 2:
		result = "Big Win!";
		break;
	case 3:
		result = "Huge Win!";
		break;
	case 4:
		result = "Mega Win!";
		break;
	case 5:
		result = "Ultra Win!";
		break;
	default:
		result = "Error! Slot broken!";
	}

	return result;
}

void StateCalculateWin::initializeText(const std::string& str)
{
	FontManager* font_mgr = m_state_manager->getContext()->m_font_manager;
	m_text.setFont(*font_mgr->getResource(IDR_CYR));
	m_text.setString(str);
	m_text.setCharacterSize(120);
	m_text.setStyle(sf::Text::Bold);
	m_text.setFillColor(sf::Color::Green);
	sf::FloatRect rect = m_text.getLocalBounds();
	m_text.setOrigin(rect.left + rect.width / 2.f, rect.top + rect.height / 2.f);

	auto icons = m_slot->getAllVisibleIcons();
	m_text.setPosition(icons[1].second.x + kIconWidth / 2, 50.f);
}
