#include "button.h"
#include "buttoninfo.h"
#include "constants.h"
#include "reel.h"
#include "sharedcontext.h"
#include "slot.h"

#include <algorithm>
#include <cassert>

Slot::Slot(SharedContext* context, int32 reel_count) : m_context{ context }
{
	TextureManager* texture_mgr = m_context->m_texture_manager;
	texture_mgr->requireResource(IDR_BG);
	texture_mgr->requireResource(IDR_ICONS);

	m_background.setTexture(*texture_mgr->getResource(IDR_BG), true);

	createButtons();
	createIconSprites();
	createReels(reel_count);
}

Slot::~Slot()
{
	for (auto& icon : m_icons)
	{
		delete icon.second;
	}

	TextureManager* texture_mgr = m_context->m_texture_manager;
	texture_mgr->releaseResource(IDR_BG);
	texture_mgr->releaseResource(IDR_ICONS);
}

void Slot::spinReels(float dt)
{
	for (auto& reel : m_reels)
	{
		reel.spin(dt);
	}
}

void Slot::spinCountReelsFromEnd(float dt, int32 count)
{
	if (count < 0 || count > m_reels.size())
	{
		assert(false && "Slot::spinCountReelsFromEnd count is less then 0 or greater than reels total count");
		return;
	}

	int32 size = m_reels.size();
	// Start from last element and go till 0 element if count = size
	for (int32 i = size - 1; i > size - 1 - count; --i)
	{
		m_reels[i].spin(dt);
	}
}

void Slot::stopReels(float dt, int32 count /* = 1*/)
{
	for (int i = 0; i < count; ++i)
	{
		m_reels[i].setSpeed(kMinSpinSpeed);
		m_reels[i].stop(dt);
	}
}

void Slot::resetReelsSpeed(float speed)
{
	for (auto& reel : m_reels)
	{
		reel.setSpeed(speed);
	}
}

void Slot::draw()
{
	Window* window = m_context->m_window;
	window->draw(m_background);

	for (auto& button : m_buttons)
	{
		button.draw();
	}

	for (auto& reel : m_reels)
	{
		reel.draw(m_context->m_window);
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

const IconContainer* Slot::getIconSprites() const
{
	return &m_icons;
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

void Slot::createIconSprites()
{
	sf::Texture* fruit_texture = m_context->m_texture_manager->getResource(IDR_ICONS);

	std::vector<sf::IntRect> rects{ k7Rect, kWatermelonRect, kPlumRect, kLemonRect, kBananaRect, kBigwinRect, kCherryRect, kOrangeRect };
	assert(rects.size() == kIconCount);
	
	std::vector<std::string> names{ "7", "Watermelon", "Plum", "Lemon", "Banana", "Bigwin", "Cherry", "Orange" };
	assert(names.size() == kIconCount);

	for (int32 i = 0; i < names.size(); ++i)
	{
		m_icons.emplace(names[i], new sf::Sprite(*fruit_texture, rects[i]));
	}
}

void Slot::createReels(int32 count)
{
	for (int32 i = 0; i < count; ++i)
	{
		m_reels.emplace_back(Reel(this, kFirstReelPosition * static_cast<float>(i + 1)));
	}
}
