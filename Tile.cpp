#include "Tile.h"

//using namespace std;

void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

Tile::Tile(std::string s, glm::vec2* positionIn)
{
    position = positionIn;
	size = glm::vec2(Settings::Tile::width, Settings::Tile::height);
	if(Utility::getRandInt(1, 10) < 3)
	{
		bb = new RectangleShape(new glm::vec2(), 0.0, new glm::vec2(Settings::Tile::width, Settings::Tile::height), "block");
	}
	else
	{
		//bb = new RectangleShape<Tile>(new glm::vec2(), this, new glm::vec2(TileWidth, TileHeight), s);
		bb = nullptr;
	}
}

Tile::~Tile(void)
{
}

glm::vec2* Tile::getPosition(void)
{
	return position;
}

RectangleShape* Tile::getBB(void)
{
	return bb;
}

glm::vec2 Tile::getSize(void)
{
	return size;
}