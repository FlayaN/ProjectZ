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
	int id = Utility::getRandInt(0, itemTypes.size()-1);
	groundItems.push_back(std::make_shared<GroundItem>(GroundItem(glm::vec2(TileAmount*coord.x+Utility::getRandInt(0, TileAmount-1), TileAmount*coord.y+Utility::getRandInt(0, TileAmount-1)), itemTypes[id]->name, itemTypes[id]->stackSize, itemTypes[id]->id)));
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

void Chunk::removeGroundItem(std::shared_ptr<GroundItem> item)
{
	std::cout << "Should be within: " << TileAmount*coord.x << " : " << TileAmount*coord.y << " -> " << TileAmount*coord.x + (TileAmount-1) << " : " << TileAmount*coord.y + (TileAmount-1) << std::endl;
	std::cout << "ItemPos X: " << item->getPosition().x << " Y: " << item->getPosition().y << std::endl;
	groundItems.erase(std::find(groundItems.begin(), groundItems.end(), item));
}