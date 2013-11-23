#pragma once
#include "Position.h"
#include <vector>

class Area
{
public:
	Area(std::vector<Position*>, bool);
	~Area(void);

	std::vector<Position*> getCorners();
	void setCorners(std::vector<Position*>);

	int getCornerCount();
	std::string getAreaType();

private:
	std::vector<Position*> corners;
	bool collidable;
};

