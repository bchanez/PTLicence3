#pragma once

#include <random>
#include "DEBUG.hpp"

namespace CRandom
{
	void init();

	int intInRange(int low, int high);
	float floatInRange(float low, float high);
}
