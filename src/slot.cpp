#include "button.h"
#include "buttoninfo.h"
#include "sharedcontext.h"
#include "slot.h"

#include <algorithm>

Slot::Slot(SharedContext* context) : m_context{ context }
{
	TextureManager* texture_mgr = m_context->m_texture_manager;
	texture_mgr->requireResource(IDR_BG);

	m_background.setTexture(*texture_mgr->getResource(IDR_BG), true);

	createButtons();
}

Slot::~Slot()
{
	TextureManager* texture_mgr = m_context->m_texture_manager;
	texture_mgr->releaseResource(IDR_BG);
}

void Slot::update(float dt)
{

}

void Slot::draw()
{
	Window* window = m_context->m_window;
	window->draw(m_background);

	for (auto& button : m_buttons)
	{
		button.draw();
	}
}

const sf::RectangleShape* Slot::getButtonByName(const std::string& name)
{
	const sf::RectangleShape* shape = nullptr;
	auto it = std::find(m_buttons.begin(), m_buttons.end(), name);
	if (it != m_buttons.end())
	{
		shape = it->getShape();
	}

	return shape;
}

void Slot::createButtons()
{
	ButtonInfo start;
	start.label = "Start";
	start.character_size = 60;
	start.size = { 208.f, 104.f };
	start.button_position = { 900.f, 200.f };
	start.label_color = sf::Color::Magenta;
	start.button_color = sf::Color::Red;
	start.font = IDR_CYR;

	ButtonInfo stop;
	stop.label = "Stop";
	stop.character_size = 60;
	stop.size = { 208.f, 104.f };
	stop.button_position = { 900.f, 500.f };
	stop.label_color = sf::Color::Magenta;
	stop.button_color = sf::Color::Red;
	stop.font = IDR_CYR;

	m_buttons.emplace_back(m_context, start);
	m_buttons.emplace_back(m_context, stop);
}
