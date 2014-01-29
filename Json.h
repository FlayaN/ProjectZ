#ifndef JSON_H
#define JSON_H

#ifdef __APPLE__
    #include <dirent.h>
	#include <SDL2/SDL.h>
	#include <SDL2_image/SDL_image.h>
#else
    #include "dirent.h"
	#include "SDL.h"
	#include "SDL_image.h"
#endif

#include <string>
#include <memory>
#include <regex>

#include <curl/curl.h>
#include "lib/rapidjson/document.h"
#include "lib/rapidjson/filestream.h"

#include "Utility.h"
#include "TypeClothing.h"
#include "TypeConsumable.h"
#include "TypeMaterial.h"
#include "TypeWeapon.h"
#include "TypeTile.h"
#include "TypePlayer.h"

class Json
{
public:
	Json(void);
	~Json(void);

	std::vector<TypeTile> getTileTypes(void);
	std::vector<std::shared_ptr<TypeItem> > getItemTypes(void);
	TypePlayer getPlayerType(void);
	SDL_Surface getTileTexture(void);
	SDL_Surface getItemTexture(void);
	std::string getIp(void);
private:
	void loadJson(void);
	void loadSettings(void);
	void loadTiles(void);
	void loadItems(void);

	void combineTileTextures(void);
	void combineItemTextures(void);

	std::vector<TypeTile> tileTypes;
	std::vector<std::shared_ptr<TypeItem> > itemTypes;

	TypePlayer playerType;
	
	SDL_Surface tileTexture;
	SDL_Surface itemTexture;
	std::string ip;
};

#endif