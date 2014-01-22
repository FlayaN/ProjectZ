#ifndef PLAYERMP_H
#define PLAYERMP_H

#include <iostream>

#include "Utility.h"
#include "Entity.h"
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

	void update(void);
private:
	int id;
	glm::vec2 size;

	SnapShot latestSnapShot;
	SnapShot prevSnapShot;
	float timer;
	Uint32 oldTime, currTime;
};

#endif