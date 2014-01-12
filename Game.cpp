#include "Game.h"

Game::Game(void) : _running(false)
{
    
}

Game::~Game(void)
{
	delete net;
}

int Game::init(void)
{
	// Initialize the SDL library.
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "SDL_Init() failed: %s\n", SDL_GetError());
		return APP_FAILED;
	}

	if(Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1)
	{
		return false;
	}

	//music = Mix_LoadWAV("../assets/music/CSLIVE.wav");

	

	//Load json files
	loadJson();
	Graphics::getInstance();
	cam = new Camera(player);
	renderer = new Renderer(player, cam);

	net = new Network("81.237.237.250");
	online = net->getSuccess();

	return APP_OK;
}

int Game::run(void)
{
	// Initialize application.
	int state = init();
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
		ChunkUtility::generateSurroundingChunk(chunks, Settings::Engine::chunkDistance, player);
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
				net->send(player, currTime);
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
	renderer->render(chunks, player, players);
}

void Game::collision(void)
{
	std::vector<Tile*> v = ChunkUtility::getSurroundingTiles(chunks, Settings::Engine::collisionDistance, player);
	
	for(auto tile: v)
    {
		Tile* currTile = tile;
		glm::vec2 tileCoord = *currTile->getPosition();
		
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
	std::string texturePath = "../assets/config/textures.json";
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
	glm::vec2* pos = new glm::vec2(doc["startPos"]["x"].GetInt(), doc["startPos"]["y"].GetInt());

	assert(doc["rotation"].IsDouble());
	float rotation = (float)doc["rotation"].GetDouble();

	assert(doc["size"]["width"].IsInt());
	assert(doc["size"]["height"].IsInt());
	glm::vec2 size(doc["size"]["width"].GetInt(), doc["size"]["height"].GetInt());
	
	assert(doc["tex"].IsString());
	std::string tex = doc["tex"].GetString();
	
	assert(doc["acceleration"].IsDouble());
	float acceleration = (float)doc["acceleration"].GetDouble();

	assert(doc["maxSpeed"].IsDouble());
	float maxSpeed = (float)doc["maxSpeed"].GetDouble();

	assert(doc["friction"].IsDouble());
	float friction = (float)doc["friction"].GetDouble();

	const rapidjson::Value& bb = doc["bb"];

	assert(bb["tex"].IsString());
	std::string bbTex = bb["tex"].GetString();

	assert(bb["size"]["width"].IsInt());
	assert(bb["size"]["height"].IsInt());
	glm::vec2* bbSize = new glm::vec2(bb["size"]["width"].GetInt(), bb["size"]["height"].GetInt());

	assert(bb["offset"]["x"].IsInt());
	assert(bb["offset"]["y"].IsInt());
	glm::vec2* bbOffset = new glm::vec2(bb["offset"]["x"].GetInt(), bb["offset"]["y"].GetInt());

	player = new EntityPlayer(pos, rotation, size, tex, bbSize, bbOffset, bbTex, acceleration, maxSpeed, friction); // change 0.0 to rot

	fclose(pFile3);

	std::cout << "----------Loading tile.json----------" << std::endl;
	FILE* pFile4 = fopen(settingsTilePath.c_str(), "rb");
	rapidjson::FileStream fs4(pFile4);
	doc.ParseStream<0>(fs4);

	assert(doc["width"].IsInt());
	Settings::Tile::width = doc["width"].GetInt();

	assert(doc["height"].IsInt());
	Settings::Tile::height = doc["height"].GetInt();

	fclose(pFile3);

	std::cout << "--------------------Loading textures.json--------------------" << std::endl;
	FILE* pFile5 = fopen(texturePath.c_str(), "rb");
	rapidjson::FileStream fs5(pFile5);
	doc.ParseStream<0>(fs5);
	
	const rapidjson::Value& a = doc["textures"];
	assert(a.IsArray());
	
	TextureManager::getInstance().init(a);

	fclose(pFile5);

}