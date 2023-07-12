#pragma once
#include <cmath>


namespace jojo
{
	constexpr float Pi = 3.14159265359;
	constexpr float TwoPi = 6.28318530718;
	constexpr float HalfPi = 1.57079632679;

	constexpr float RadiansToDegrees(float radians) { return radians * 180.0f / Pi; }
	constexpr float DegreesToRadians(float degrees) { return degrees * Pi / 180.0f; }

	constexpr int Wrap(int value, int max)
	{
		return (value % max) + ((value < 0) ? max : 0);
	}

}