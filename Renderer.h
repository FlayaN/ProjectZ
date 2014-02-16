#ifndef RENDERER_H
#define RENDERER_H

#include "lib/glm/gtc/type_ptr.hpp"
#include "lib/glm/mat4x4.hpp"
#include "lib/glm/gtc/matrix_transform.hpp"
#include "simplefont.h"

#include "Graphic.h"
#include "Defines.h"
#include "ChunkUtility.h"
#include "EntityPlayer.h"
#include "PlayerMP.h"
#include "RectangleShape.h"
#include "Camera.h"
#include "ModelSquare.h"
#include "TypeTile.h"
#include "TypeMaterial.h"
#include "Chat.h"
#include "InventoryManager.h"

class Renderer
{
public:
	Renderer(std::shared_ptr<Graphic>, EntityPlayer, std::shared_ptr<Camera>, SDL_Surface, std::vector<std::shared_ptr<TypeTile> >, SDL_Surface, int);
	~Renderer(void);
	void render(std::HashMap<glm::ivec2, std::shared_ptr<Chunk> > , EntityPlayer, std::vector<std::shared_ptr<PlayerMP> >, Chat, std::shared_ptr<InventoryManager>);

	void renderItem(std::HashMap<glm::ivec2, std::shared_ptr<Chunk> >, EntityPlayer);
	void renderTile(std::HashMap<glm::ivec2, std::shared_ptr<Chunk> >, EntityPlayer);
	void renderGrid(EntityPlayer);
	void renderPlayer(EntityPlayer);
	void renderOnlinePlayers(std::vector<std::shared_ptr<PlayerMP> >, EntityPlayer);

	void renderInventory(std::shared_ptr<Inventory>);
	void renderHotbar(std::shared_ptr<Inventory>);
	void renderMouseItem(std::shared_ptr<Mouse>);
	void renderGui(EntityPlayer, std::shared_ptr<InventoryManager>);
	void renderChat(Chat);
	void renderTimedChat(Chat);

	GLuint pathToOGLTexture(std::string);
	GLuint surfaceToOGLTexture(SDL_Surface);

private:
	void initShaders(void);

	int w, h;

	std::unique_ptr<ModelSquare> modelPlayer;
	GLint texPlayer;

	std::unique_ptr<ModelSquare> modelOnlinePlayer;
	GLuint texOnlinePlayer;

	std::unique_ptr<ModelSquare> modelTile;
	GLuint texTile;

	std::unique_ptr<ModelSquare> modelItem;
	GLuint texItem;

	std::unique_ptr<ModelSquare> modelGui;
	GLuint texSlot;
	GLuint texSlotHover;

	GLuint texChat;

	std::shared_ptr<Camera> cam;
    std::shared_ptr<Graphic> graphic;
    
	char buff[1400];
};

#endif