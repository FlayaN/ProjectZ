#include "Game.h"

Game::Game(void) : _running(false)
{
	state = APP_OK;
    // Initialize the SDL library.
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "SDL_Init() failed: %s\n", SDL_GetError());
		state = APP_FAILED;
	}

	if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1)
	{
		state = APP_FAILED;
	}

	//music = Mix_LoadWAV("../assets/music/CSLIVE.wav");

	//Load json files
	loadJson();

	PerlinNoise::getInstance().SetValues(0.25, 6.0, (double)tileTypes.size(), 1, 1337);
	SimplexNoise::init();

	combineTileTextures();

	Graphics::getInstance();
	player = new EntityPlayer(playerType);
	cam = new Camera(player);
	renderer = new Renderer(*player, cam, ct, tileTypes);

	net = new Network("81.237.237.250");
	online = net->getSuccess();
}

Game::~Game(void)
{
	/*if(online)
		delete net;*/
}

int Game::run(void)
{
	// Initialize application.
	if (state != APP_OK) return state;
	
	// Enter to the SDL event loop.
	SDL_Event ev;
	_running = true;

	//Mix_PlayChannel(-1, music, 0);

	Uint32 oldTime, currTime;
	float delta;
	float tmpTime = 0;
	currTime = SDL_GetTicks();

	const Uint8* keystates = SDL_GetKeyboardState(NULL);

	
	while(_running)
	{
		oldTime = currTime;
		currTime = SDL_GetTicks();
		delta = (currTime - oldTime) / 1000.0f;

		//Events
		while( SDL_PollEvent(&ev)) 
		{
			onEvent(&ev);
		}
		
		//Logic
		ChunkUtility::generateSurroundingChunk(chunks, Settings::Engine::chunkDistance, *player, tileTypes);
		collision();
		player->update(delta, keystates);
		if(online)
		{
			for(auto p : players)
			{
				p->update();
			}
		}
		
		//Rendering
		render();

		//Network
		if(online)
		{
			tmpTime += (currTime - oldTime);
			if(tmpTime >= 50) //How often to send data to the server in ms (50 = 20times/second)
			{
				net->send(*player, currTime);
				tmpTime = 0;
			}
			net->recv(players, player, currTime);
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
	renderer->render(chunks, *player, players);
}

void Game::collision(void)
{
	std::vector<Tile*> v = ChunkUtility::getSurroundingTiles(chunks, Settings::Engine::collisionDistance, *player);
	
	for(auto tile: v)
    {
		Tile* currTile = tile;
		glm::ivec2 tileCoord = *currTile->getPosition();
		glm::ivec2 playerInTileCoord = Utility::inTileCoord(player->getCenterPosition());

		if(playerInTileCoord == tileCoord)
		{
			player->setFriction(tile->getFriction());
		}
		
		if(currTile != nullptr)
		{
			/*SDL_Rect* bb = currTile->getBB();
			if(bb != nullptr)
			{
				bb->x = (tileCoord.x)*bb->w;
				bb->y = (tileCoord.y)*(bb->h);
			}
			//CollisionHandler::intersects(&playerBB, bb);

			if(CollisionHandler::intersects(player->getBB(), bb))
			{
				//std::cout << "Collision at X: " << bb->x << " Y: " << bb->y << std::endl;
			}*/
		}
	}
}

void Game::loadJson(void)
{
	std::string settingsChunkPath = "../assets/config/settings/chunk.json";
	std::string settingsEnginePath = "../assets/config/settings/engine.json";
	std::string settingsGraphicPath = "../assets/config/settings/graphic.json";
	std::string settingsPlayerPath = "../assets/config/settings/player.json";
	std::string settingsTilePath = "../assets/config/settings/tile.json";
	//std::string texturePath = "../assets/config/textures.json";
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
	rapidjson::Document doc;
	std::cout << "--------------------Loading Settings--------------------" << std::endl;
	std::cout << "----------Loading engine.json----------" << std::endl;
	FILE* pFile1 = fopen(settingsEnginePath.c_str(), "rb");
	rapidjson::FileStream fs1(pFile1);
	doc.ParseStream<0>(fs1);

	assert(doc["renderDistance"].IsInt());
	Settings::Engine::renderDistance = doc["renderDistance"].GetInt();

	assert(doc["collisionDistance"].IsInt());
	Settings::Engine::collisionDistance = doc["collisionDistance"].GetInt();

	assert(doc["chunkDistance"].IsInt());
	Settings::Engine::chunkDistance = doc["chunkDistance"].GetInt();

	fclose(pFile1);

	std::cout << "----------Loading graphic.json----------" << std::endl;
	FILE* pFile2 = fopen(settingsGraphicPath.c_str(), "rb");
	rapidjson::FileStream fs2(pFile2);
	doc.ParseStream<0>(fs2);

	assert(doc["screenWidth"].IsInt());
	Settings::Graphics::screenWidth = doc["screenWidth"].GetInt();

	assert(doc["screenHeight"].IsInt());
	Settings::Graphics::screenHeight = doc["screenHeight"].GetInt();

	fclose(pFile2);

	std::cout << "----------Loading player.json----------" << std::endl;
	FILE* pFile3 = fopen(settingsPlayerPath.c_str(), "rb");
	rapidjson::FileStream fs3(pFile3);
	doc.ParseStream<0>(fs3);

	assert(doc["startPos"]["x"].IsInt());
	assert(doc["startPos"]["y"].IsInt());
	playerType.startPos = glm::vec2(doc["startPos"]["x"].GetInt(), doc["startPos"]["y"].GetInt());

	assert(doc["rotation"].IsDouble());
	playerType.rotation = (float)doc["rotation"].GetDouble();

	assert(doc["size"]["width"].IsInt());
	assert(doc["size"]["height"].IsInt());
	playerType.size = glm::vec2(doc["size"]["width"].GetInt(), doc["size"]["height"].GetInt());

	assert(doc["texture"].IsString());
	playerType.texture = doc["texture"].GetString();
	
	assert(doc["acceleration"].IsDouble());
	playerType.acceleration = (float)doc["acceleration"].GetDouble();

	assert(doc["maxSpeed"].IsDouble());
	playerType.maxSpeed = (float)doc["maxSpeed"].GetDouble();

	assert(doc["bb"].IsString());
	playerType.bb = doc["bb"].GetString();

	fclose(pFile3);

	std::cout << "----------Loading tile.json----------" << std::endl;
	FILE* pFile4 = fopen(settingsTilePath.c_str(), "rb");
	rapidjson::FileStream fs4(pFile4);
	doc.ParseStream<0>(fs4);

	assert(doc["width"].IsInt());
	Settings::Tile::width = doc["width"].GetInt();

	assert(doc["height"].IsInt());
	Settings::Tile::height = doc["height"].GetInt();

	fclose(pFile4);

	loadTiles();
}

void Game::loadTiles(void)
{
	std::string path = "../assets/config/tiles/";

	DIR* dir;
	struct dirent* ent;

	dir = opendir(path.c_str());
	if(dir != nullptr)
	{
		while((ent = readdir(dir)) != nullptr)
		{
			std::string tmpFile(ent->d_name);
			std::string end = ".tile";
			if(Utility::hasEnding(tmpFile, end))
			{
				FILE* pFile = fopen((path+tmpFile).c_str(), "rb");
				rapidjson::Document doc;
				rapidjson::FileStream fs(pFile);
				doc.ParseStream<0>(fs);

				
				TypeTile tmpTile;
				tmpTile.name = tmpFile.erase(tmpFile.size() - 5);

				assert(doc["texture"].IsString());
				tmpTile.texture = doc["texture"].GetString();

				assert(doc["friction"].IsDouble());
				tmpTile.friction = (float)doc["friction"].GetDouble();

				tileTypes.push_back(tmpTile);

				fclose(pFile);
			}
		}
	}else
	{
		std::cout << "Cannot open dir" << std::endl;
	}
}

void Game::combineTileTextures(void)
{
	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif

	ct = *SDL_CreateRGBSurface(0, tileTypes.size()*256, 128, 32, rmask, gmask, bmask, amask);
	SDL_Rect pos;
	pos.y = 0;
	pos.x = 0;

	for(auto t : tileTypes)
	{
		SDL_Surface* tmp = IMG_Load(t.texture.c_str());
		if(tmp != nullptr)
		{
			SDL_BlitSurface(tmp, NULL, &ct, &pos);
			pos.x += tmp->w;
		}
	}
}