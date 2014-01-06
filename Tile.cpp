#include "Tile.h"

//using namespace std;

void logSDLError(std::ostream &os, const std::string &msg){
	os << msg << " error: " << SDL_GetError() << std::endl;
}

Tile::Tile(std::string s, glm::vec2* positionIn, glm::vec3* colorModIn)
{
    //std::cout << "x: " << colorMod.x << " y: " << colorMod.y << " z: " << colorMod.z << std::endl;
	/*bb = new SDL_Rect();
	bb->h = TileSize/2;
	bb->w = TileSize;*/
    position = positionIn;
    
	if(Utility::getRandInt(1, 10) < 3)
	{
		tex = TextureManager::getInstance().getTexture("block");
        colorMod = new glm::vec3(255, 255, 255);
		bb = new SDL_Rect();
		bb->h = TileHeight;
		bb->w = TileWidth;
	}
	else
	{
		tex = TextureManager::getInstance().getTexture(s);
        colorMod = colorModIn;
		bb = nullptr;
	}
}

Tile::~Tile(void)
{
}

SDL_Texture* Tile::getTexture(void)
{
	return tex;
}

SDL_Rect* Tile::getBB(void)
{
	return bb;
}

glm::vec2* Tile::getPosition(void)
{
	return position;
}

glm::vec3* Tile::getColorMod(void)
{
    return colorMod;
}