
#include "TextureManager.h"

using namespace pugi;

TextureManager::TextureManager(void)
{
	init();
}

void TextureManager::init(void)
{
	xml_document doc;

	xml_parse_result result = doc.load_file("res/config/textures.xml");

	xml_node nodes = doc.child("textures");
	
	for (xml_node node = nodes.first_child(); node; node = node.next_sibling("texture"))
	{
		textures[node.attribute("name").value()] = IMG_LoadTexture(Graphics::getInstance().getRenderer(), node.attribute("file").value());
	}
}

SDL_Texture* TextureManager::getTexture(std::string id)
{
	return textures[id];
}