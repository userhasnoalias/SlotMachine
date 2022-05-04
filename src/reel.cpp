#include "constants.h"
#include "math.h"
#include "reel.h"
#include "slot.h"
#include "window.h"

#include <iterator>

const std::vector<std::string> ReelIconOrders::s_reel1{ "Orange", "Watermelon", "7", "Banana" };

Reel::Reel(Slot* owner, const sf::Vector2f& position) : m_slot{ owner }, m_position{ position }
{
	const std::vector<std::string>& icon_order = ReelIconOrders::getIconOrderForReel();
	m_icons.reserve(icon_order.size());
	for (int32 i = 0; i < icon_order.size(); ++i)
	{
		m_icons.emplace_back(icon_order[i], sf::Vector2f{ m_position.x, m_position.y + kIconHeight * i });
	}
}

void Reel::spin(float dt)
{
	update(dt);
}

void Reel::stop(float dt)
{
	update(dt);
}

void Reel::update(float dt)
{
	m_speed = math::interpConstantTo(m_speed, m_target_speed, dt, m_acceleration);
	
	for (auto& icon : m_icons)
	{
		// This check should prevent reels from not working as expected in case of huge lag
		// Value of 30 is just randomly chosen as max travelled distance per frame
		if (m_speed * dt < 30.f)
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

		// New position of the first icon will be just above current first icon Y
		sf::Vector2f new_pos{ m_icons[0].second.x, m_icons[0].second.y - kIconHeight };
		m_icons.insert(m_icons.begin(), { last_icon_name, new_pos });
	}
}

void Reel::draw(Window* window)
{
	if (!window) { return; }

	const IconContainer* icon_sprites = m_slot->getIconSprites();
	for (auto& icon : m_icons)
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

void Reel::setSpeed(float speed)
{
	m_target_speed = speed;
}
