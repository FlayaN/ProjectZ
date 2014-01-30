#ifndef UTILITY_H
#define UTILITY_H

#ifdef __APPLE__
    #include <CoreFoundation/CoreFoundation.h>
#endif

#include <random>
#include <math.h>
#include <iostream>
#include <string>

#include "lib/glm/vec2.hpp"
#include <curl/curl.h>

#include "Defines.h"

namespace Utility
{
	int getRandInt(int min, int max);
	int clamp(int value, int min, int max);
	int mod(int v, int m);
	
	bool hasEnding(std::string const &, std::string const &);

	glm::ivec2 inChunkCoord(glm::vec2);
	glm::ivec2 inTileCoord(glm::vec2);
	glm::ivec2 withinRange(glm::ivec2);
    
    std::string getBasePath(void);
	std::string doWebRequest(std::string url);
};

#endif