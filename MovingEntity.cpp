#include "MovingEntity.h"

MovingEntity::MovingEntity(void)
{
	velocity = new glm::vec2();
}

MovingEntity::~MovingEntity(void)
{
	delete velocity;
}

//------------------------------------------------SET ----------------------------------------------//

void MovingEntity::setVelocity(glm::vec2* velocityIn)
{
	delete velocity;
	velocity = velocityIn;
}

//------------------------------------------------GET ----------------------------------------------//

glm::vec2* MovingEntity::getVelocity(void)
{
	return velocity;
}

//------------------------------------------------UPDATE -------------------------------------------//

void MovingEntity::updatePosition(void)
{
	position->x += velocity->x;
	position->y += velocity->y;

	for (Entity* child : children)
	{
		MovingEntity* movingChild = dynamic_cast<MovingEntity*> (child);  // Null if not CircleShape
		if(movingChild != NULL)
			movingChild->updatePosition();
	}
}
