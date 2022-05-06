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
	texture_mgr->requireResource(IDR_SLOT);

	m_background.setTexture(*texture_mgr->getResource(IDR_BG), true);
	//sf::IntRect rect{ 0, 0, 180, 180 };
	m_slot_tile.setTexture(*texture_mgr->getResource(IDR_SLOT), true);
	//m_slot_tile.setTextureRect(rect);

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
	texture_mgr->releaseResource(IDR_SLOT);
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
		// Sets the target speed to speed when player pressed stop button
		const float cur_speed = m_reels[i].getCurrentSpeed();
		m_reels[i].setTargetSpeed(cur_speed);
		m_reels[i].spin(dt);
	}
}

void Slot::stopReels(float dt, int32 count /* = 1*/)
{
	for (int i = 0; i < count; ++i)
	{
		m_reels[i].setTargetSpeed(kMinSpinSpeed);
		m_reels[i].stop(dt);
	}
}

void Slot::resetReelsSpeed(float speed)
{
	for (auto& reel : m_reels)
	{
		reel.setTargetSpeed(speed);
	}
}

void Slot::draw()
{
	Window* window = m_context->m_window;
	window->draw(m_background);

	for (int32 i = 0; i < kVisibleIcons; ++i)
	{
		for (int32 j = 0; j < kReelsCount; ++j)
		{
			m_slot_tile.setPosition(kFirstSlotTilePosition.x + kSlotTileWidth * j, 
				kFirstSlotTilePosition.y + kSlotTileWidth * i);
			window->draw(m_slot_tile);
		}
	}

	for (auto& button : m_buttons)
	{
		button.draw();
	}

	for (auto& reel : m_reels)
	{
		reel.draw(m_context->m_window);
	}
}

int32 Slot::getReelsCount() const
{
	return m_reels.size();
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

/*	Indicies for visible icons (for 3 reels) look like this:
*	0---1---2
*	3---4---5
*	6---7---8
*/
IconWheelContainer Slot::getAllVisibleIcons() const
{
	IconWheelContainer result(m_reels.size() * kVisibleIcons);

	for (int32 i = 0; i < m_reels.size(); ++i)
	{
		// We need to map index 0 to 0, 1 to 3, and 2 to 6 etc.
		auto temp = m_reels[i].getVisibleIcons();
		int32 j = i;
		for (auto& val : temp)
		{
			result[j] = std::move(val);
			j += kReelsCount;
		}
	}

	return result;
}

void Slot::onReelStop(int32 reel_number)
{
	if (m_on_reel_stop)
	{
		std::cout << __FUNCTION__ << '\n';
		std::cout << "Reel num: " << reel_number << '\n';
		m_on_reel_stop(reel_number);
	}
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
		// Shift each reel
		m_reels.emplace_back(Reel(this, sf::Vector2f{kFirstReelPosition.x + (kIconWidth + kIconIndentX) * i, kFirstReelPosition.y}));
	}
}
