
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
        textures[a[i]["name"].GetString()] = IMG_LoadTexture(Graphics::getInstance().getRenderer(), a[i]["file"].GetString());
    }
}

SDL_Texture* TextureManager::getTexture(std::string id)
{
	return textures[id];
}