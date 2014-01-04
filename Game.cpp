#include "Game.h"

Game::Game(void) : _running(false)
{
    
}

Game::~Game(void)
{
    destroy();
}

int Game::init(void)
{
	online=true;

	// Initialize the SDL library.
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "SDL_Init() failed: %s\n", SDL_GetError());
		return APP_FAILED;
	}

	if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
	{
		return false;
	}

	music = Mix_LoadWAV("res/music/CSLIVE.wav");

	renderer = new Renderer();

	//Load json files
	loadJson();

	if(online)
	{
		net = new Network("127.0.0.1");
	}

	return APP_OK;
}

void Game::destroy()
{
	/*if (win)
	{
		SDL_DestroyWindow(win);
		SDL_DestroyRenderer(renderer->getRenderer());
		SDL_Quit();
	}*/
}

int Game::run(void)
{
	// Initialize application.
	int state = init();
	if (state != APP_OK) return state;
	
	// Enter to the SDL event loop.
	SDL_Event ev;
	_running = true;

	//Mix_PlayMusic(music, -1);
	Mix_PlayChannel(-1, music, -1);
	
	while(_running)
	{
		//Events
		while( SDL_PollEvent(&ev)) 
		{
			player->keyDown(&ev);
			onEvent(&ev);
		}
		
		//Logic
		ChunkUtility::generateSurroundingChunk(&chunks, ChunkDistance, player);
		collision();
		player->update();
		
		//Rendering
		render();
        
        if(std::strcmp(SDL_GetError(), ""))
            std::cout << "SDL_ERROR: " << SDL_GetError() << std::endl;


		if(online)
		{
			net->send(player);
			net->recv(players, player);

			//std::cout << players.size() << std::endl;
		}
	}
	
	return APP_OK;
}

void Game::onEvent(SDL_Event* ev)
{
	switch (ev->type)
	{
		case SDL_QUIT:
			_running = false;
			break;
			
		case SDL_KEYDOWN:
		{
			if (ev->key.keysym.sym == SDLK_ESCAPE)
			{
				_running = false;
			}
		}
	}
}

void Game::render()
{
	renderer->render(chunks, player, players);
}

void Game::collision(void)
{
	std::vector<Tile*> v = ChunkUtility::getSurroundingTiles(chunks, CollisionDistance, player);
	
	for(auto tile: v)
    {
		Tile* currTile = tile;
		Vec2 tileCoord = *currTile->getPosition();
		
		if(currTile != nullptr)
		{
			SDL_Rect* bb = currTile->getBB();
			if(bb != nullptr)
			{
				bb->x = (tileCoord.x)*bb->w;
				bb->y = (tileCoord.y)*(bb->h);
			}
			//CollisionHandler::intersects(&playerBB, bb);

			if(CollisionHandler::intersects(player->getBB(), bb))
			{
				//std::cout << "Collision at X: " << bb->x << " Y: " << bb->y << std::endl;
			}
		}
	}
}

void Game::loadJson(void)
{
	std::string texturePath = "res/config/textures.json";
	std::string playerPath = "res/config/player.json";
#ifdef __APPLE__
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourceURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char p[PATH_MAX];
    if(!CFURLGetFileSystemRepresentation(resourceURL, TRUE, (UInt8 *)p, PATH_MAX))
        std::cout << "ERROROROROR" << std::endl;
    CFRelease(resourceURL);
    
    chdir(p);
    
    std::string path = p;
    
    std::string texturePath = path + "/" + texturePath;
	std::string playerPath = path + "/" + playerPath;
#endif
	std::cout << "--------------------Loading textures.json--------------------" << std::endl;
	loadTextures(texturePath);
	std::cout << "--------------------Loading player.json--------------------" << std::endl;
	loadPlayer(playerPath);
}

void Game::loadTextures(std::string texturePath)
{
	FILE* pFile = fopen(texturePath.c_str(), "rb");
    rapidjson::FileStream fs(pFile);
    rapidjson::Document doc;
    doc.ParseStream<0>(fs);
    
    const rapidjson::Value& a = doc["textures"];
    assert(a.IsArray());
    
	

	TextureManager::getInstance().init(a);

	fclose(pFile);
}

void Game::loadPlayer(std::string playerPath)
{
	FILE* pFile = fopen(playerPath.c_str(), "rb");
    rapidjson::FileStream fs(pFile);
    rapidjson::Document doc;
    doc.ParseStream<0>(fs);

	assert(doc.IsObject());

	assert(doc["startPos"]["x"].IsInt());
	assert(doc["startPos"]["y"].IsInt());
	Vec2* pos = new Vec2(doc["startPos"]["x"].GetInt(), doc["startPos"]["y"].GetInt());

	assert(doc["size"]["width"].IsInt());
	assert(doc["size"]["height"].IsInt());
	Vec2* size = new Vec2(doc["size"]["width"].GetInt(), doc["size"]["height"].GetInt());
	
	assert(doc["tex"].IsString());
	std::string tex = doc["tex"].GetString();
	
	assert(doc["speed"].IsDouble());
	float speed = (float)doc["speed"].GetDouble();

	const rapidjson::Value& bb = doc["bb"];

	assert(bb["tex"].IsString());
	std::string bbTex = bb["tex"].GetString();

	assert(bb["size"]["width"].IsInt());
	assert(bb["size"]["height"].IsInt());
	Vec2* bbSize = new Vec2(bb["size"]["width"].GetInt(), bb["size"]["height"].GetInt());

	assert(bb["offset"]["x"].IsInt());
	assert(bb["offset"]["y"].IsInt());
	Vec2* bbOffset = new Vec2(bb["offset"]["x"].GetInt(), bb["offset"]["y"].GetInt());

	std::cout << "StartPos: " << *pos << std::endl;
	std::cout << "Size: " << *size << std::endl;
	std::cout << "Tex: " << tex << std::endl;
	std::cout << "Speed: " << speed << std::endl;
	std::cout << "BBSize: " << *bbSize << std::endl;
	std::cout << "BBOffset: " << *bbOffset << std::endl;
	std::cout << "BBTex: " << bbTex << std::endl;

	player = new EntityPlayer(pos, size, tex, speed, bbSize, bbOffset, bbTex);
	
	fclose(pFile);
}