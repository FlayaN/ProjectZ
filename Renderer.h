#pragma once

#include "Graphics.h"
#include "Defines.h"
#include "ChunkUtility.h"
#include "EntityPlayer.h"
#include "PlayerMP.h"
#include "RectangleShape.h"
#include "GL_utilities.h"
#include "lib/glm/gtc/type_ptr.hpp"
#include "lib/glm/mat4x4.hpp"
#include "lib/glm/gtc/matrix_transform.hpp"
#include "Camera.h"

#ifndef RENDERER_H
#define RENDERER_H

class Renderer
{
public:
	Renderer(EntityPlayer*, Camera*);
	~Renderer(void);
	void render(std::HashMap<glm::ivec2, Chunk*> , EntityPlayer*, std::vector<PlayerMP*>);

	void renderTile(std::HashMap<glm::ivec2, Chunk*>, EntityPlayer*);
	void renderGrid(EntityPlayer*);
	void renderEntity(EntityPlayer*, std::vector<PlayerMP*>);

	unsigned int generateModel(RectangleShape<Entity>*, GLuint);

	GLuint surfaceToOGLTexture(SDL_Surface* tex);
private:
	int w, h;
	unsigned int entityProg;
	unsigned int playerVao;
	GLint playerTex;
	RectangleShape<Entity>* playerModel;

	unsigned int tileVao;
	GLint tileTex;
	RectangleShape<Tile>* tileModel;

	unsigned int tileBBVao;
	GLint tileBBTex;
	RectangleShape<Tile>* tileBBModel;

	Camera* cam;
};

#endif