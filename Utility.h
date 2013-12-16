#pragma once

#include <random>

#ifndef Utility_H
#define Utility_H

namespace Utility
{
	int getRandInt(int min, int max);
	int clamp(int value, int min, int max);
};

#endif