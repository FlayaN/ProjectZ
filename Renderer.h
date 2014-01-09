#pragma once

#ifndef RENDERER_H
#define RENDERER_H

#include "lib/glm/gtc/type_ptr.hpp"
#include "lib/glm/mat4x4.hpp"
#include "lib/glm/gtc/matrix_transform.hpp"

#include "Graphics.h"
#include "Defines.h"
#include "ChunkUtility.h"
#include "EntityPlayer.h"
#include "PlayerMP.h"
#include "RectangleShape.h"
#include "Camera.h"
#include "ModelSquare.h"

class Renderer
{
public:
	Renderer(EntityPlayer*, Camera*);
	~Renderer(void);
	void render(std::HashMap<glm::ivec2, Chunk*> , EntityPlayer*, std::vector<PlayerMP*>);

	void renderTile(std::HashMap<glm::ivec2, Chunk*>, EntityPlayer*);
	void renderGrid(EntityPlayer*);
	void renderPlayer(EntityPlayer*);
	void renderOnlinePlayers(std::vector<PlayerMP*>, EntityPlayer*);

	GLuint surfaceToOGLTexture(SDL_Surface* tex);
private:
	void initShaders(void);

	int w, h;

	ModelSquare* modelPlayer;
	GLint texPlayer;

	ModelSquare* modelOnlinePlayer;
	GLuint texOnlinePlayer;

	ModelSquare* modelTile;
	GLuint texTile;

	Camera* cam;
};

#endif