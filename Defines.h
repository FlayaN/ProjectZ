#define HashMap unordered_map
#define TileAmount 5						//Number of tiles in each chunk TileAmount*TileAmount
#define TileWidth 80						//Width of each tile
#define TileHeight (TileWidth/2)
#define ChunkWidth (TileWidth*TileAmount)
#define ChunkHeight (TileHeight*TileAmount)
#define RenderDistance 4					//How far to render tiles around player
#define CollisionDistance 2					//How far to calculate collision around player
#define ChunkDistance 1						//How many chunks to generate around the player
#define SCREEN_WIDTH 1280					//Width of the screen
#define SCREEN_HEIGHT 720					//Height of the screen