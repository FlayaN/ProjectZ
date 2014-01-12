#pragma once

#ifndef PLAYERMP_H
#define PLAYERMP_H

#include "Utility.h"
#include "Entity.h"
#include "TextureManager.h"
#include "RectangleShape.h"
#include "SnapShot.h"

class PlayerMP : public Entity
{
public:
	PlayerMP(int);
	glm::vec2 getSize(void);

	int getId(void);

	void setLatestSnapShot(float, float, int);

	SnapShot getLatestSnapShot(void);
	SnapShot getPrevSnapShot(void);

	void update(float);
private:
	int id;
	glm::vec2 size;

	SnapShot latestSnapShot;
	SnapShot prevSnapShot;
	float timer;
};

#endif