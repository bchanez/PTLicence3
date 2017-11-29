#ifndef CRANDOM_HPP_
#define CRANDOM_HPP_

#include <random>
#include "DEBUG.hpp"

namespace CRandom
{
	void init();

	int intInRange(int low, int high);
	float floatInRange(float low, float high);
}

#endif
