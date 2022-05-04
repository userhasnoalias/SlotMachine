#include "constants.h"
#include "reel.h"
#include "slot.h"
#include "window.h"

Reel::Reel(Slot* owner, const sf::Vector2f& position) : m_slot{ owner }, m_position{ position }
{
	std::vector<std::string> icon_order = ReelIconOrders::getIconOrderForReel();
	for (int32 i = 0; i < icon_order.size(); ++i)
	{
		m_icons.emplace_back(icon_order[i], sf::Vector2f{ m_position.x, m_position.y + kIconHeight * i });
	}
}

void Reel::update(float dt)
{
	for (auto& icon : m_icons)
	{
		icon.second.y += m_speed * dt;
	}
}

void Reel::draw(Window* window)
{
	if (!window) { return; }

	const IconContainer* icon_sprites = m_slot->getIconSprites();
	for (auto& icon : m_icons)
	{
		auto it = icon_sprites->find(icon.first);
		if (it != icon_sprites->end())
		{
			sf::Sprite* sprite = it->second;
			sprite->setPosition(icon.second);
			window->draw(*sprite);
		}
	}
}
