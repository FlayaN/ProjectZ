#pragma once

#include "Graphics.h"
#include "Defines.h"
#include "ChunkUtility.h"
#include "EntityPlayer.h"

#ifndef RENDERER_H
#define RENDERER_H

class Renderer
{
public:
	Renderer(void);
	~Renderer(void);
	void render(std::HashMap<Vec2, Chunk*> , EntityPlayer*);

	void renderTile(std::HashMap<Vec2, Chunk*>, EntityPlayer*);
	void renderGrid(const Vec2&);
	void renderEntity(EntityPlayer*);

private:
	int w, h;
};

#endif