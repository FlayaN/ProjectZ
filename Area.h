#pragma once
#include "Vec3.h"

#include <vector>
#include <string>

class Area
{
public:
	Area(std::vector<Vec3*>, bool);
	~Area(void);

	std::vector<Vec3*> getCorners();
	void setCorners(std::vector<Vec3*>);

	unsigned long getCornerCount();
	std::string getAreaType();

private:
	std::vector<Vec3*> corners;
	bool collidable;
};

