#pragma once

#include "Graphics.h"
#include "Defines.h"
#include "ChunkUtility.h"
#include "EntityPlayer.h"
#include "PlayerMP.h"

#ifndef RENDERER_H
#define RENDERER_H

class Renderer
{
public:
	Renderer(void);
	~Renderer(void);
	void render(std::HashMap<Vec2, Chunk*> , EntityPlayer*, std::vector<PlayerMP*>);

	void renderTile(std::HashMap<Vec2, Chunk*>, EntityPlayer*);
	void renderGrid(EntityPlayer*);
	void renderEntity(EntityPlayer*, std::vector<PlayerMP*>);

private:
	int w, h;
};

#endif