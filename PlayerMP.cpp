#include "PlayerMP.h"

PlayerMP::PlayerMP(int idIn) : id(idIn), Entity()
{
	prevSnapShot = SnapShot();
	latestSnapShot = SnapShot();
	size = glm::vec2(80, 160);
}

void PlayerMP::setLatestSnapShot(float x, float y, int tick)
{
	prevSnapShot = latestSnapShot;
	latestSnapShot = SnapShot(glm::vec2(x, y), tick);
	timer = 0;
}

SnapShot PlayerMP::getLatestSnapShot(void)
{
	return latestSnapShot;
}

SnapShot PlayerMP::getPrevSnapShot(void)
{
	return prevSnapShot;
}

glm::vec2 PlayerMP::getSize(void)
{
	return size;
}

int PlayerMP::getId(void)
{
	return id;
}

void PlayerMP::update(float delta)
{
	timer += delta;
	*position =  prevSnapShot.pos + ((latestSnapShot.pos-prevSnapShot.pos) * timer);
}