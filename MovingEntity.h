#pragma once

#include "entity.h"

#ifndef MOVINGENTITY_H
#define MOVINGENTITY_H

class MovingEntity : public Entity
{
public:
	MovingEntity(void);
	virtual ~MovingEntity(void);

	void setVelocity(glm::vec2*);

	glm::vec2* getVelocity(void);

	void updatePosition(void);

private:
	glm::vec2* velocity;
};

#endif
