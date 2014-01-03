
#include "TextureManager.h"

//using namespace pugi;

TextureManager::TextureManager(void)
{
	init();
}

void TextureManager::init(void)
{
#ifdef __APPLE__
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourceURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[PATH_MAX];
    if(!CFURLGetFileSystemRepresentation(resourceURL, TRUE, (UInt8 *)path, PATH_MAX))
        std::cout << "ERROROROROR" << std::endl;
    CFRelease(resourceURL);
    
    chdir(path);
    
    std::string tmp = path;
    std::string tmp2 = "/res/config/textures.json";
    tmp = tmp + tmp2;
    
    FILE* pFile = fopen(tmp.c_str(), "rb");
#else
    FILE* pFile = fopen("res/config/textures.json", "rb");
#endif
    
    rapidjson::FileStream fs(pFile);
    rapidjson::Document doc;
    doc.ParseStream<0>(fs);
    
    const rapidjson::Value& a = doc["textures"];
    assert(a.IsArray());
    
    for (rapidjson::SizeType i = 0; i < a.Size(); i++) {
        std::cout << a[i]["name"].GetString() << std::endl;
        textures[a[i]["name"].GetString()] = IMG_LoadTexture(Graphics::getInstance().getRenderer(), a[i]["file"].GetString());
    }
}

SDL_Texture* TextureManager::getTexture(std::string id)
{
	return textures[id];
}