#include "Tile.h"


Tile::Tile(Position* positionIn, Area* northAreaIn, Area* southAreaIn, Area* westAreaIn, Area* eastAreaIn)
{
	position = positionIn;
	northArea = northAreaIn;
	southArea = southAreaIn;
	westArea = westAreaIn;
	eastArea = eastAreaIn;
}


Tile::~Tile(void)
{
	delete position;
	delete northArea;
	delete southArea;
	delete westArea;
	delete eastArea;
}
