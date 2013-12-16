#include "Utility.h"

int Utility::getRandInt(int min, int max)
{
	std::random_device rd;
	std::uniform_int_distribution<int> distribution(min, max);

	return distribution(rd);
}

int Utility::clamp(int value, int min, int max)
{
	return std::min(max, std::max(min, value));
}