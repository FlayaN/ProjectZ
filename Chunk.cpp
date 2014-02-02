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
	addGroundItem(std::make_shared<GroundItemStack>(Utility::getRandInt(0, itemTypes.size()-1), glm::vec2((TileAmount*coord.x + Utility::getRandInt(0, TileAmount-1))*Settings::Tile::width, (TileAmount*coord.y + Utility::getRandInt(0, TileAmount-1))*Settings::Tile::height), 1));
}

Chunk::~Chunk(void)
{

}

std::shared_ptr<Tile> Chunk::getTile(glm::ivec2 pos)
{
	return tiles[pos.x][pos.y];
}

glm::ivec2 Chunk::getCoord(void)
{
	return coord;
}

std::vector<std::shared_ptr<GroundItemStack> > Chunk::getGroundItemStacks(void)
{
	return groundItemStacks;
}

void Chunk::removeGroundItem(int id, glm::vec2 pos, int amount)
{
	std::shared_ptr<GroundItemStack> tmpGroundItemStack = nullptr;
	for(int i = 0; i < groundItemStacks.size(); i++)
	{
		if(groundItemStacks[i]->getId() == id && groundItemStacks[i]->getPosition() == pos && groundItemStacks[i]->getAmount() == amount)
			tmpGroundItemStack = groundItemStacks[i];
	}

	if(tmpGroundItemStack != nullptr)
		groundItemStacks.erase(std::find(groundItemStacks.begin(), groundItemStacks.end(), tmpGroundItemStack));
}

void Chunk::addGroundItem(std::shared_ptr<GroundItemStack> groundItemStack)
{
	groundItemStacks.push_back(groundItemStack);
}