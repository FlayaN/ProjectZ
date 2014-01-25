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
	combineItemTextures();

	Graphics::getInstance();
	player = std::make_shared<EntityPlayer>(playerType);
	cam = std::make_shared<Camera>(player);
	renderer = std::unique_ptr<Renderer>(new Renderer(*player, cam, tileTexture, tileTypes, itemTexture, itemTypes.size()));

	net = std::make_shared<Network>(ip.c_str());
	//net = std::make_shared<Network>("81.237.237.250");

	online = net->getSuccess();
	keyFocus = false;

	chat = std::make_shared<Chat>(10);
	//sfMakeRasterFont();
}

Game::~Game(void)
{

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

	const Uint8* keyStates = SDL_GetKeyboardState(NULL);

	
	while(_running)
	{
		oldTime = currTime;
		currTime = SDL_GetTicks();
		delta = (currTime - oldTime) / 1000.0f;

		//Events
		while( SDL_PollEvent(&ev)) 
		{
			onEvent(&ev);
			if(keyFocus)
				chat->handleKeyInput(&ev, keyStates);
			else
				player->onEvent(&ev);
		}
		
		//Logic
		ChunkUtility::generateSurroundingChunk(chunks, Settings::Engine::chunkDistance, *player, tileTypes, itemTypes);
		collision();
		if(keyFocus)
			player->update2(delta);
		else
			player->update(delta, keyStates);
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
			net->recv(players, player, currTime, chat);
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
			if(ev->key.keysym.sym == SDLK_ESCAPE)
			{
				_running = false;
			}
			else if(ev->key.keysym.sym == SDLK_RETURN)
			{
				if(online)
				{
					if(!keyFocus)
					{
						keyFocus = true;
						chat->setOpen(true);
						SDL_StartTextInput();
					}
					else
					{
						keyFocus = false;
						chat->setOpen(false);
						SDL_StopTextInput();

						if(chat->getCurrText() != "")
						{
							net->sendMessage(*player, TimeChat(chat->getCurrText(), SDL_GetTicks()));
							chat->setCurrText("");
						}
					}
				}
			}
			break;
		}
	}
}

void Game::render()
{
	renderer->render(chunks, *player, players, *chat);
}

void Game::collision(void)
{
	for(auto tile: ChunkUtility::getSurroundingTiles(chunks, Settings::Engine::collisionDistance, *player))
    {
		if(tile != nullptr)
		{
			glm::ivec2 tileCoord = tile->getPosition();
			glm::ivec2 playerInTileCoord = Utility::inTileCoord(player->getCenterPosition());

			if(playerInTileCoord == tileCoord)
			{
				player->setFriction(tile->getFriction());
			}
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

	glm::ivec2 centerPosInChunk = Utility::inChunkCoord(player->getCenterPosition());

	for(int x = centerPosInChunk.x - 1; x <= centerPosInChunk.x + 1; x++)
	{
		for(int y = centerPosInChunk.y - 1; y <= centerPosInChunk.y + 1; y++)
		{
			std::shared_ptr<Chunk> tmpChunk = chunks[glm::ivec2(x, y)];
			
			if(tmpChunk != nullptr)
			{
				std::vector<std::shared_ptr<GroundItem> > t2 = tmpChunk->getGroundItems();
				
				for(int i = 0; i < t2.size(); i++)
				{
					glm::vec2 playerPos = player->getCenterPosition();
					glm::vec2 itemPos = glm::vec2(t2[i]->getPosition().x * Settings::Tile::width, t2[i]->getPosition().y * Settings::Tile::height);
					glm::ivec2 chunkPos = Utility::inChunkCoord(itemPos);

					if(	playerPos.x > (itemPos.x - 100) && playerPos.x < (itemPos.x + 100) && playerPos.y > (itemPos.y - 100) && playerPos.y < (itemPos.y + 100))
					{
						if(player->getInventory()->addItem(t2[i]))
							tmpChunk->removeGroundItem(t2[i]);
					}
				}
			}
		}
	}
}

size_t writeToString(void *ptr, size_t size, size_t count, void *stream)
{
	((std::string*)stream)->append((char*)ptr, 0, size * count);
	return size * count;
}

std::string doWebRequest(std::string url)
{
	CURL* curl_handle = NULL;
	std::string response;

	/* initializing curl and setting the url */
	curl_handle = curl_easy_init();
	curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl_handle, CURLOPT_HTTPGET, 1);

	/* follow locations specified by the response header */
	curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1);

	/* setting a callback function to return the data */
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, writeToString);

	/* passing the pointer to the response as the callback parameter */
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &response);

	/* perform the request */
	curl_easy_perform(curl_handle);

	/* cleaning all curl stuff */
	curl_easy_cleanup(curl_handle);

	return response;
}

void Game::loadJson(void)
{
	std::string jsonString = doWebRequest("http://hannesf.com/ProjectZ/get.php");

	std::cout << "JsonString: " << jsonString << std::endl;

	rapidjson::Document doc;

	if(!doc.Parse<0>(jsonString.c_str()).HasParseError());
	{
		const rapidjson::Value& a = doc; // Using a reference for consecutive access is handy and faster.
		for (rapidjson::SizeType i = 0; i < a.Size(); i++) // rapidjson uses SizeType instead of size_t.
		{
			ip = a[i]["ip"].GetString();
			std::cout << "Connecting to: " << ip << std::endl;
		}
	}
	
	loadSettings();
	loadTiles();
	loadItems();
}

void Game::loadSettings(void)
{
	std::string settingsEnginePath = Utility::getBasePath() + "assets/config/settings/engine.json";
	std::string settingsGraphicPath = Utility::getBasePath() + "assets/config/settings/graphic.json";
	std::string settingsPlayerPath = Utility::getBasePath() + "assets/config/settings/player.json";
	std::string settingsTilePath = Utility::getBasePath() + "assets/config/settings/tile.json";

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
	playerType.texture = std::string("assets/config/settings/")+doc["texture"].GetString();
	
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
}

void Game::loadTiles(void)
{
	std::string path = Utility::getBasePath() + "assets/config/tiles/";

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

				assert(doc["name"].IsString());
				tmpTile.name = doc["name"].GetString();

				assert(doc["texture"].IsString());
				tmpTile.texture = path+doc["texture"].GetString();

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

void Game::loadItems(void)
{
	std::string clothingPath = Utility::getBasePath() + "assets/config/items/clothing/";
	std::string consumablesPath = Utility::getBasePath() + "assets/config/items/consumables/";
	std::string materialPath = Utility::getBasePath() + "assets/config/items/materials/";
	std::string weaponPath = Utility::getBasePath() + "assets/config/items/weapons/";

	DIR* dir;
	struct dirent* ent;

	int curId = 0;

	//CLOTHING

	dir = opendir(clothingPath.c_str());
	if(dir != nullptr)
	{
		while((ent = readdir(dir)) != nullptr)
		{
			std::string tmpFile(ent->d_name);
			std::string end = ".clothing";
			if(Utility::hasEnding(tmpFile, end))
			{
				FILE* pFile = fopen((clothingPath+tmpFile).c_str(), "rb");
				rapidjson::Document doc;
				rapidjson::FileStream fs(pFile);
				doc.ParseStream<0>(fs);

				
				std::shared_ptr<TypeClothing> tmp = std::make_shared<TypeClothing>();

				assert(doc["name"].IsString());
				tmp->name = doc["name"].GetString();

				assert(doc["texture"].IsString());
				tmp->texture = clothingPath + doc["texture"].GetString();

				assert(doc["desc"].IsString());
				tmp->desc = doc["desc"].GetString();
				
				assert(doc["stackSize"].IsInt());
				tmp->stackSize = doc["stackSize"].GetInt();

				tmp->id = curId++;

				itemTypes.push_back(tmp);
				
				fclose(pFile);
			}
		}
	}else
	{
		std::cout << "Cannot open dir: " << clothingPath << std::endl;
	}

	//CONSUMABLES

	dir = opendir(consumablesPath.c_str());
	if(dir != nullptr)
	{
		while((ent = readdir(dir)) != nullptr)
		{
			std::string tmpFile(ent->d_name);
			std::string end = ".consumable";
			if(Utility::hasEnding(tmpFile, end))
			{
				FILE* pFile = fopen((consumablesPath+tmpFile).c_str(), "rb");
				rapidjson::Document doc;
				rapidjson::FileStream fs(pFile);
				doc.ParseStream<0>(fs);

				
				std::shared_ptr<TypeConsumable> tmp = std::make_shared<TypeConsumable>();
				
				assert(doc["name"].IsString());
				tmp->name = doc["name"].GetString();

				assert(doc["texture"].IsString());
				tmp->texture = consumablesPath + doc["texture"].GetString();

				assert(doc["desc"].IsString());
				tmp->desc = doc["desc"].GetString();
				
				assert(doc["stackSize"].IsInt());
				tmp->stackSize = doc["stackSize"].GetInt();

				tmp->id = curId++;

				itemTypes.push_back(tmp);

				fclose(pFile);
			}
		}
	}else
	{
		std::cout << "Cannot open dir: " << consumablesPath << std::endl;
	}

	//MATERIALS

	dir = opendir(materialPath.c_str());
	if(dir != nullptr)
	{
		while((ent = readdir(dir)) != nullptr)
		{
			std::string tmpFile(ent->d_name);
			std::string end = ".material";
			if(Utility::hasEnding(tmpFile, end))
			{
				FILE* pFile = fopen((materialPath+tmpFile).c_str(), "rb");
				rapidjson::Document doc;
				rapidjson::FileStream fs(pFile);
				doc.ParseStream<0>(fs);

				
				std::shared_ptr<TypeMaterial> tmp = std::make_shared<TypeMaterial>();
				
				assert(doc["name"].IsString());
				tmp->name = (std::string)doc["name"].GetString();

				assert(doc["texture"].IsString());
				tmp->texture = materialPath + doc["texture"].GetString();

				assert(doc["desc"].IsString());
				tmp->desc = doc["desc"].GetString();
				
				assert(doc["stackSize"].IsInt());
				tmp->stackSize = doc["stackSize"].GetInt();

				tmp->id = curId++;

				itemTypes.push_back(tmp);

				fclose(pFile);
			}
		}
	}else
	{
		std::cout << "Cannot open dir: " << materialPath << std::endl;
	}

	//WEAPONS

	dir = opendir(weaponPath.c_str());
	if(dir != nullptr)
	{
		while((ent = readdir(dir)) != nullptr)
		{
			std::string tmpFile(ent->d_name);
			std::string end = ".weapon";
			if(Utility::hasEnding(tmpFile, end))
			{
				FILE* pFile = fopen((weaponPath+tmpFile).c_str(), "rb");
				rapidjson::Document doc;
				rapidjson::FileStream fs(pFile);
				doc.ParseStream<0>(fs);

				
				std::shared_ptr<TypeWeapon> tmp = std::make_shared<TypeWeapon>();
				
				assert(doc["name"].IsString());
				tmp->name = doc["name"].GetString();

				assert(doc["texture"].IsString());
				tmp->texture = weaponPath + doc["texture"].GetString();

				assert(doc["desc"].IsString());
				tmp->desc = doc["desc"].GetString();

				assert(doc["damage"].IsDouble());
				tmp->damage = (float)doc["damage"].GetDouble();
				
				assert(doc["stackSize"].IsInt());
				tmp->stackSize = doc["stackSize"].GetInt();

				tmp->id = curId++;

				itemTypes.push_back(tmp);

				fclose(pFile);
			}
		}
	}else
	{
		std::cout << "Cannot open dir: " << weaponPath << std::endl;
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

	tileTexture = *SDL_CreateRGBSurface(0, tileTypes.size()*256, 128, 32, rmask, gmask, bmask, amask);
	SDL_Rect pos;
	pos.y = 0;
	pos.x = 0;

	for(auto t : tileTypes)
	{
		SDL_Surface* tmp = IMG_Load(t.texture.c_str());
		if(tmp != nullptr)
		{
			SDL_BlitSurface(tmp, NULL, &tileTexture, &pos);
			pos.x += tmp->w;
		}
	}
}

void Game::combineItemTextures(void)
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

	itemTexture = *SDL_CreateRGBSurface(0, itemTypes.size()*32, 32, 32, rmask, gmask, bmask, amask);
	SDL_Rect pos;
	pos.y = 0;
	pos.x = 0;

	for(auto i : itemTypes)
	{
		SDL_Surface* tmp = IMG_Load(i->texture.c_str());
		if(tmp != nullptr)
		{
			SDL_BlitSurface(tmp, NULL, &itemTexture, &pos);
			pos.x += tmp->w;
		}
	}
}