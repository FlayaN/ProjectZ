#define HashMap unordered_map
#define ChunkAmount 5
#define TileAmount 5						//Number of tiles in each chunk TileAmount*TileAmount
#define TileWidth 100						//Width of each tile
#define TileHeight (TileWidth/2)
#define ChunkWidth (TileWidth*TileAmount)
#define ChunkHeight (TileHeight*TileAmount)
#define RenderDistance 2					//How far to render tiles around player
#define CollisionDistance 1					//How far to calculate collision around player
#define ChunkDistance 1
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600