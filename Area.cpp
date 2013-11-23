#include "Area.h"


Area::Area(std::vector<Position*> cornersIn, bool collidableIn)
{
	corners = cornersIn;
	collidable = collidableIn;
}


Area::~Area(void)
{
	/* Behövs ej då ~Position sköter destrueringen?
	for each (Position* corner in corners)
	{
		delete corner;
	}
	*/
}

std::vector<Position*> Area::getCorners()
{
	return corners;
}

void Area::setCorners(std::vector<Position*> cornersIn)
{
	corners = cornersIn;
}

int Area::getCornerCount()
{
	return corners.size;
}

std::string Area::getAreaType()
{
	if(corners.size == 3)
		return "Triangle";
	else if(corners.size == 4)
		return "Square";
	else
		return "Unidentified";
}