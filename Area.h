#pragma once
#include "Coordinate.h"
#include <vector>
#include <string>

class Area
{
public:
	Area(std::vector<Coordinate*>, bool);
	~Area(void);

	std::vector<Coordinate*> getCorners();
	void setCorners(std::vector<Coordinate*>);

	unsigned long getCornerCount();
	std::string getAreaType();

private:
	std::vector<Coordinate*> corners;
	bool collidable;
};

