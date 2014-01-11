#include "Settings.h"

#define HashMap unordered_map
#define TileAmount 5						//Number of tiles in each chunk TileAmount*TileAmount
#define ChunkWidth (Settings::Tile::width*TileAmount)
#define ChunkHeight (Settings::Tile::height*TileAmount)