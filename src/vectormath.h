#pragma once

#include "commontypes.h"
#include "math.h"

#include <SFML/System/Vector2.hpp>

#include <limits>

namespace vec
{
	float invSqrt(float number)
	{
		union 
		{
			float f;
			uint32 i;
		} un;

		un.f = number;
		un.i = 0x5f3759df - (un.i >> 1);
		un.f *= 1.5F - (number * 0.5F * un.f * un.f);

		return un.f;
	}

	float length(const sf::Vector2f& v)
	{
		return std::sqrtf(v.x * v.x + v.y * v.y);
	}

	bool normalize(sf::Vector2f& vec, float tolerance = std::numeric_limits<float>::epsilon())
	{
		const float square_sum = vec.x * vec.x + vec.y * vec.y;
		if (square_sum > tolerance)
		{
			vec = vec * invSqrt(square_sum);
			return true;
		}
		
		return false;
	}
}