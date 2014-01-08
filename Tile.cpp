#include "Tile.h"

//using namespace std;

void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

Tile::Tile(std::string s, glm::vec2* positionIn, glm::vec3* colorModIn)
{
    position = positionIn;
    
	if(Utility::getRandInt(1, 10) < 3)
	{
		bb = new RectangleShape<Tile>(new glm::vec2(), this, new glm::vec2(TileWidth, TileHeight), "block");
        colorMod = new glm::vec3(255, 255, 255);
	}
	else
	{
		bb = new RectangleShape<Tile>(new glm::vec2(), this, new glm::vec2(TileWidth, TileHeight), s);
        colorMod = colorModIn;
	}
}

Tile::~Tile(void)
{
}

glm::vec2* Tile::getPosition(void)
{
	return position;
}

glm::vec3* Tile::getColorMod(void)
{
    return colorMod;
}

RectangleShape<Tile>* Tile::getBB(void)
{
	return bb;
}