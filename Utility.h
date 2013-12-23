#pragma once

#include <random>

#ifndef UTILITY_H
#define UTILITY_H

namespace Utility
{
	int getRandInt(int min, int max);
	int clamp(int value, int min, int max);
	int mod(int v, int m);
};

#endif