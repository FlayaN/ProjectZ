#pragma once

#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include "lib/glm/vec2.hpp"

class SnapShot
{
public:

	SnapShot() : pos(glm::vec2()), time(0) {}
	SnapShot(glm::vec2 posIn, int timeIn) : pos(posIn), time(timeIn) {}

	glm::vec2 pos;
	int time;
};

#endif