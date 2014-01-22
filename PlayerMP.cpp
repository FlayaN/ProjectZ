#include "PlayerMP.h"

PlayerMP::PlayerMP(int idIn) : id(idIn), Entity()
{
	prevSnapShot = SnapShot();
	latestSnapShot = SnapShot();
	size = glm::vec2(80, 160);
	currTime = SDL_GetTicks();
}

void PlayerMP::setLatestSnapShot(float x, float y, int tick)
{
	if(latestSnapShot.time > tick)
		std::cout << "ERROR TIME ERRORORORORO" << std::endl;
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

void PlayerMP::update(void)
{
	oldTime = currTime;
	currTime = SDL_GetTicks();
	float tmp = (currTime - oldTime) / (float)(latestSnapShot.time - prevSnapShot.time);
	timer += tmp;
	position =  prevSnapShot.pos + ((latestSnapShot.pos-prevSnapShot.pos) * timer);
}