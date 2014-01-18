#include "Tile.h"

void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

Tile::Tile(int tId, float frictionIn, glm::ivec2 positionIn)
{
	textureId = tId;
	friction = frictionIn;
    position = positionIn;
	size = glm::ivec2(Settings::Tile::width, Settings::Tile::height);
	if(Utility::getRandInt(1, 10) < 3)
	{
		bb = new RectangleShape(new glm::vec2(), 0.0, new glm::vec2(Settings::Tile::width, Settings::Tile::height));
	}
	else
	{
		bb = nullptr;
	}
}

Tile::~Tile(void)
{
}

glm::ivec2 Tile::getPosition(void)
{
	return position;
}

RectangleShape* Tile::getBB(void)
{
	return bb;
}

glm::ivec2 Tile::getSize(void)
{
	return size;
}

int Tile::getTextureId(void)
{
	return textureId;
}

float Tile::getFriction(void)
{
	return friction;
}