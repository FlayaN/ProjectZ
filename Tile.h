#pragma once
#include "Position.h"
#include "Area.h"

class Tile
{
public:
	Tile(Position*, Area*, Area*, Area*, Area*);
	~Tile(void);

private:
	Position* position;

	Area* northArea;
	Area* southArea;
	Area* westArea;
	Area* eastArea;
};

