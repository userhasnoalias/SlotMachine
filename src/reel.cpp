#include "constants.h"
#include "math.h"
#include "reel.h"
#include "slot.h"
#include "window.h"

#include <iterator>

const std::vector<std::string> ReelIconOrders::s_reel1{ "7", "7", "7", "Cherry" };
const std::vector<std::string> ReelIconOrders::s_reel2{ "7", "7", "7", "7" };
const std::vector<std::string> ReelIconOrders::s_reel3{ "7", "7", "7", "7" };

Reel::Reel(Slot* owner, const sf::Vector2f& position) : m_slot{ owner }, m_position{ position }
{
	const std::vector<std::string>& icon_order = ReelIconOrders::getIconOrderForReel();
	m_icons.reserve(icon_order.size());
	for (int32 i = 0; i < icon_order.size(); ++i)
	{
		m_icons.emplace_back(icon_order[i], sf::Vector2f{ m_position.x, m_position.y + (kSlotTileHeight + kIconIndentY) * i });
	}
}

void Reel::spin(float dt)
{
	update(dt);
}

void Reel::stop(float dt)
{
	// If remaining distance is not set and speed is above zero, reels are slowing down
	if (m_remaining_dist < 0.f && m_speed > 0.f)
	{
		update(dt);
		if (m_speed <= m_target_speed)
		{
			// If reel reached its minimum speed calculate remaining spin distance by subtracting current y of 0 element
			// from initial y, so after reaching this distance all icons are properly aligned (with very little inaccuracy)
			m_remaining_dist = m_position.y - m_icons[0].second.y;
		}
	}
	else if (m_remaining_dist > 0.f)
	{
		// If remaining distance is set move till we align all icons
		update(dt);
		m_remaining_dist -= m_speed * dt;
		if (m_remaining_dist <= 0.f)
		{
			// Align every icon perfectly and reset speed and distance so the reel stops
			align();
			m_remaining_dist = -1.f;
			m_speed = 0.f;

			// Fire an event that this reel stopped spinning. Reel number is calculated by its X coordinate that never changes.
			// Reel number is actually X coordinate multiplier given upon creation plus 1 (because we count reels from 1).
			// See Slot::createReels
			m_slot->onReelStop(static_cast<int32>((m_icons[0].second.x - kFirstReelPosition.x) / kIconWidth) + 1);
		}
	}
}

void Reel::update(float dt)
{
	m_speed = math::interpConstantTo(m_speed, m_target_speed, dt, m_acceleration);
	
	for (auto& icon : m_icons)
	{
		// This check should prevent reels from not working as expected in case of huge lag
		// Value of 30 is just randomly chosen as max travelled distance per frame
		if (m_speed * dt < kMaxMovementPerFrame)
		{
			icon.second.y += m_speed * dt;
		}
	}

	// Icon with index 0 is the topmost icon
	// If it is below certain level we remove last icon and move it to top
	if (m_icons[0].second.y >= kSlotLoopY)
	{
		// Remember last icon name
		std::string_view last_icon_name = m_icons.back().first;
		// Get iterator to the last element
		auto it = m_icons.begin();
		std::advance(it, m_icons.size() - 1);
		m_icons.erase(it);

		// New position of the first icon will be just above current first icon Y (plus offset)
		sf::Vector2f new_pos{ m_icons[0].second.x, m_icons[0].second.y - kSlotTileHeight - kIconIndentY };
		m_icons.insert(m_icons.begin(), { last_icon_name, new_pos });
	}
}

void Reel::draw(Window* window)
{
	if (!window) { return; }

	const IconContainer* icon_sprites = m_slot->getIconSprites();
	for (auto& icon : m_icons)
	{
		// We need to draw only 4 icons at the same time for 3x3 field
		if (icon.second.y > kFirstSlotTilePosition.y - (kIconHeight + kMaxMovementPerFrame)
			&& icon.second.y < kFirstSlotTilePosition.y + kIconHeight + (kSlotTileHeight * kVisibleIcons))
		{
			auto it = icon_sprites->find(icon.first.data());
			if (it != icon_sprites->end())
			{
				sf::Sprite* sprite = it->second;
				sprite->setPosition(icon.second);
				window->draw(*sprite);
			}
		}
	}
}

void Reel::setTargetSpeed(float speed)
{
	m_target_speed = speed;
}

IconWheelContainer Reel::getVisibleIcons() const
{
	// Visible icons are always at positions 1, 2, and 3
	IconWheelContainer result;
	for (int32 i = 1; i <= kVisibleIcons; ++i)
	{
		result.emplace_back(m_icons[i]);
	}

	// should invoke move constructor
	return result;
}

float Reel::getCurrentSpeed() const
{
	return m_speed;
}

bool Reel::isStopped() const
{
	return m_speed <= 0.f;
}

void Reel::align()
{
	for (int i = 0; i < m_icons.size(); ++i)
	{
		m_icons[i].second.y = m_position.y + (kSlotTileHeight + kIconIndentY) * i;
	}
}
