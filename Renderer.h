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
//#include "Font.h"

class Renderer
{
public:
	Renderer(EntityPlayer, std::shared_ptr<Camera>, SDL_Surface, std::vector<TypeTile>);
	~Renderer(void);
	void render(std::HashMap<glm::ivec2, std::shared_ptr<Chunk> > , EntityPlayer, std::vector<std::shared_ptr<PlayerMP> >);

	void renderTile(std::HashMap<glm::ivec2, std::shared_ptr<Chunk> >, EntityPlayer);
	void renderGrid(EntityPlayer);
	void renderPlayer(EntityPlayer);
	void renderOnlinePlayers(std::vector<std::shared_ptr<PlayerMP> >, EntityPlayer);
	//void renderText(std::string sText, int x, int y);

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

	std::shared_ptr<Camera> cam;

	char buff[1400];
};

#endif