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

	Graphics::getInstance();

	//Load json files
	loadJson();
	cam = new Camera(player);
	renderer = new Renderer(player, cam);

	net = new Network("81.237.237.250");
	online = net->getSuccess();

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

	//Mix_PlayChannel(-1, music, 0);

	Uint32 oldTime, currTime;
	float delta;

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
		ChunkUtility::generateSurroundingChunk(chunks, ChunkDistance, player);
		collision();
		player->update(delta, keystates);
		
		//Rendering
		render();

		if(online)
		{
			net->send(player);
			net->recv(players, player);
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
	std::string texturePath = "../assets/config/textures.json";
	std::string playerPath = "../assets/config/player.json";
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
	glm::vec2* pos = new glm::vec2(doc["startPos"]["x"].GetInt(), doc["startPos"]["y"].GetInt());

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

	player = new EntityPlayer(pos, size, tex, bbSize, bbOffset, bbTex, acceleration, maxSpeed, friction);
	
	fclose(pFile);
}