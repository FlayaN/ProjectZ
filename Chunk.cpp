#include "Chunk.h"

Chunk::Chunk(glm::ivec2 coord, std::vector<TypeTile> tileTypes, std::vector<std::shared_ptr<TypeItem> > itemTypes) : coord(coord)
{
	for(int x = 0; x < TileAmount; x++)
	{
		for(int y = 0; y < TileAmount; y++)
		{
			/*double tmp = PerlinNoise::getInstance().GetHeight(TileAmount*coord.x+x, TileAmount*coord.y+y);
			//double tmp = SimplexNoise::noise(TileAmount*coord->x+x, TileAmount*coord->y+y);
			//std::cout << tmp << std::endl;
			
			int i = 0;

			if(tmp < 0)
				i = 1;
			if(tmp > 0)
				i = 2;*/

			int i = Utility::getRandInt(0, tileTypes.size()-1);
			tiles[x][y] = std::make_shared<Tile>(Tile(i, tileTypes[i].friction, glm::ivec2(TileAmount*coord.x+x, TileAmount*coord.y+y)));
		}
	}
	addGroundItem(std::make_shared<GroundItem>(Utility::getRandInt(0, itemTypes.size()-1), glm::vec2((TileAmount*coord.x + Utility::getRandInt(0, TileAmount-1))*Settings::Tile::width, (TileAmount*coord.y + Utility::getRandInt(0, TileAmount-1))*Settings::Tile::height)));
}

Chunk::~Chunk(void)
{

}

std::shared_ptr<Tile> Chunk::getTile(const glm::ivec2& pos)
{
	return tiles[pos.x][pos.y];
}

glm::ivec2 Chunk::getCoord(void)
{
	return coord;
}

std::vector<std::shared_ptr<GroundItem> > Chunk::getGroundItems(void)
{
	return groundItems;
}

void Chunk::removeGroundItem(int id, glm::vec2 pos)
{
	std::shared_ptr<GroundItem> tmpGroundItem = nullptr;
	for(int i = 0; i < groundItems.size(); i++)
	{
		if(groundItems[i]->getId() == id && groundItems[i]->getPosition() == pos)
			tmpGroundItem = groundItems[i];
	}

	if(tmpGroundItem != nullptr)
		groundItems.erase(std::find(groundItems.begin(), groundItems.end(), tmpGroundItem));
}

void Chunk::addGroundItem(std::shared_ptr<GroundItem> item)
{
	groundItems.push_back(item);
}