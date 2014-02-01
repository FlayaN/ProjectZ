#include "Json.h"

Json::Json(void)
{
	loadJson();
}

Json::~Json(void)
{

}

std::vector<TypeTile> Json::getTileTypes(void)
{
	return tileTypes;
}

std::vector<std::shared_ptr<TypeItem> > Json::getItemTypes(void)
{
	return itemTypes;
}

TypePlayer Json::getPlayerType(void)
{
	return playerType;
}

SDL_Surface Json::getTileTexture(void)
{
	return tileTexture;
}

SDL_Surface Json::getItemTexture(void)
{
	return itemTexture;
}

void Json::loadJson(void)
{
	loadSettings();
	loadTiles();
	loadItems();

	combineTileTextures();
	combineItemTextures();
}

void Json::loadSettings(void)
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

void Json::loadTiles(void)
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
	}
	else
	{
		std::cout << "Cannot open dir" << std::endl;
	}
}

void Json::loadItems(void)
{
	std::string clothingPath = Utility::getBasePath() + "assets/config/items/clothing/";
	std::string consumablesPath = Utility::getBasePath() + "assets/config/items/consumables/";
	std::string materialPath = Utility::getBasePath() + "assets/config/items/materials/";
	std::string weaponPath = Utility::getBasePath() + "assets/config/items/weapons/";

	DIR* dir;
	struct dirent* ent;

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

				assert(doc["id"].IsInt());
				tmp->id = doc["id"].GetInt();

				itemTypes.push_back(tmp);
				
				fclose(pFile);
			}
		}
	}
	else
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

				assert(doc["id"].IsInt());
				tmp->id = doc["id"].GetInt();

				itemTypes.push_back(tmp);

				fclose(pFile);
			}
		}
	}
	else
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

				assert(doc["id"].IsInt());
				tmp->id = doc["id"].GetInt();

				itemTypes.push_back(tmp);

				fclose(pFile);
			}
		}
	}
	else
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

				assert(doc["id"].IsInt());
				tmp->id = doc["id"].GetInt();

				itemTypes.push_back(tmp);

				fclose(pFile);
			}
		}
	}
	else
	{
		std::cout << "Cannot open dir: " << weaponPath << std::endl;
	}
}

void Json::combineTileTextures(void)
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

void Json::combineItemTextures(void)
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