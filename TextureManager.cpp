
#include "TextureManager.h"

//using namespace pugi;

TextureManager::TextureManager(void)
{

}

void TextureManager::init(const rapidjson::Value& a)
{

    for (rapidjson::SizeType i = 0; i < a.Size(); i++) {
        std::cout << a[i]["name"].GetString() << std::endl;

		assert(a[i]["name"].IsString());
		assert(a[i]["file"].IsString());
		SDL_Surface* tmp = IMG_Load(a[i]["file"].GetString());
		if(tmp != nullptr)
			surfaces[a[i]["name"].GetString()] = tmp;
		else
			std::cout << "couldn't find : " << a[i]["file"].GetString() << std::endl;
    }
}

SDL_Surface* TextureManager::getSurface(std::string id)
{
	return surfaces[id];
}