#pragma once

#include "constants.h"

#include <random>

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

	inline int32 getRandomNumber(int32 min, int32 max)
	{
		static std::mt19937 mt{ std::random_device{}() };
		std::uniform_int_distribution die{ min, max };
		return die(mt);
	}

}