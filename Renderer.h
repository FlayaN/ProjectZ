#ifndef RENDERER_H
#define RENDERER_H

#include "lib/glm/gtc/type_ptr.hpp"
#include "lib/glm/mat4x4.hpp"
#include "lib/glm/gtc/matrix_transform.hpp"
#include "simplefont.h"

#include "Graphics.h"
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

class Renderer
{
public:
	Renderer(EntityPlayer, std::shared_ptr<Camera>, SDL_Surface, std::vector<TypeTile>, SDL_Surface, int);
	~Renderer(void);
	void render(std::HashMap<glm::ivec2, std::shared_ptr<Chunk> > , EntityPlayer, std::vector<std::shared_ptr<PlayerMP> >, Chat);

	void renderItem(std::HashMap<glm::ivec2, std::shared_ptr<Chunk> >, EntityPlayer);
	void renderTile(std::HashMap<glm::ivec2, std::shared_ptr<Chunk> >, EntityPlayer);
	void renderGrid(EntityPlayer);
	void renderPlayer(EntityPlayer);
	void renderOnlinePlayers(std::vector<std::shared_ptr<PlayerMP> >, EntityPlayer);
	void renderGui(EntityPlayer);
	void renderChat(Chat);

	GLuint pathToOGLTexture(std::string);
	GLuint surfaceToOGLTexture(SDL_Surface);

private:
	void initShaders(void);

	int w, h;

	ModelSquare* modelPlayer;
	GLint texPlayer;

	ModelSquare* modelOnlinePlayer;
	GLuint texOnlinePlayer;

	ModelSquare* modelTile;
	GLuint texTile;

	ModelSquare* modelItem;
	GLuint texItem;

	ModelSquare* modelGui;
	GLuint texGui;

	std::shared_ptr<Camera> cam;

	char buff[1400];
};

#endif