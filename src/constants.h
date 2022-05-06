#pragma once

#include "commontypes.h"

#include <SFML/Graphics/Rect.hpp>

constexpr inline float kSmallNumber = 1.e-6f;
constexpr inline float PI = 3.141592653f;

constexpr inline int32 kReelsCount = 3;
// Count of visible icons we can see on screen (per reel)
constexpr inline int32 kVisibleIcons = 3;
constexpr inline int32 kButtonsCount = 2;
constexpr inline int32 kIconWidth = 160;
constexpr inline int32 kIconHeight = 160;
constexpr inline int32 kSlotTileWidth = 180;
constexpr inline int32 kSlotTileHeight = 180;
constexpr inline int32 kIconIndentX = 20;
constexpr inline int32 kIconIndentY = 0;
constexpr inline int32 kIconCount = 8;
constexpr inline float kSlotLoopY = -10.f;
constexpr inline float kMaxSpinSpeed = 500.f;
constexpr inline float kMinSpinSpeed = 80.f;
constexpr inline float kMaxMovementPerFrame = 30.f;

const sf::Vector2f kFirstSlotTilePosition{ 130.f, 90.f };
// First reel position is chosen such way that all icons are properly aligned
const sf::Vector2f kFirstReelPosition{ 140.f, 100.f - kSlotTileHeight };

const sf::IntRect k7Rect{ 14, 24, kIconWidth, kIconHeight };
const sf::IntRect kWatermelonRect{ 220, 25, kIconWidth, kIconHeight };
const sf::IntRect kPlumRect{ 425, 25, kIconWidth, kIconHeight };
const sf::IntRect kLemonRect{ 15, 230, kIconWidth, kIconHeight };
const sf::IntRect kBananaRect{ 225, 230, kIconWidth, kIconHeight };
const sf::IntRect kBigwinRect{ 428, 225,  kIconWidth, kIconHeight };
const sf::IntRect kCherryRect{ 15, 425, kIconWidth, kIconHeight };
const sf::IntRect kOrangeRect{ 425, 430, kIconWidth, kIconHeight };
