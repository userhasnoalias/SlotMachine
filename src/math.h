#pragma once

#include "constants.h"

namespace math
{
	template<class T>
	inline T clamp(const T x, const T min, const T max)
	{
		return x < min ? min : x > max ? max : x;
	}

	template<class T>
	inline T square(const T x)
	{
		return x * x;
	}

	inline float interpConstantTo(float start, float end, float dt, float speed)
	{
		const float dist = end - start;

		// If distance is too small, just set the desired location
		if (square(dist) < kSmallNumber)
		{
			return end;
		}

		const float step = dt * speed;
		return start + clamp(dist, -step, step);
	}
}