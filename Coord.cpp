#include "Coord.h"

Coord::Coord(int xIn, int yIn) : x(xIn), y(yIn)
{

}

Coord::Coord(Vec2 pos)
{
	Coord((int)pos.x, (int)pos.y);
}

Coord::Coord(Vec3 pos)
{
	Coord((int)pos.x, (int)pos.y);
}