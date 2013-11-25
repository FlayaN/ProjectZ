#pragma once
#include "Position.h"
#include <vector>
#include <string>

class Area
{
public:
	Area(std::vector<Position*>, bool);
	~Area(void);

	std::vector<Position*> getCorners();
	void setCorners(std::vector<Position*>);

	unsigned long getCornerCount();
	std::string getAreaType();

private:
	std::vector<Position*> corners;
	bool collidable;
};

