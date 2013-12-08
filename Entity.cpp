#include "Entity.h"


Entity::Entity(void)
{
	position = new Coordinate();
	velocity = new Coordinate();
}

Entity::~Entity(void) {
	delete position;
	delete velocity;
	for(int i = 0; i < shapes.size(); i++)
	{
		delete shapes[i];
	}
}

//------------------------------------------------SET ----------------------------------------------//

// POSITION

void Entity::setPosition(Coordinate* positionIn)
{
	delete position;
	position = positionIn;
}

void Entity::setPositionXYZ(float xIn, float yIn, float zIn)
{
	position->x = xIn;
	position->y = yIn;
	position->z = zIn;
}

void Entity::setPositionX(float xIn)
{
	position->x = xIn;
}

void Entity::setPositionY(float yIn)
{
	position->y = yIn;
}

void Entity::setPositionZ(float zIn)
{
	position->z = zIn;
}

// VELOCITY

void Entity::setVelocity(Coordinate* velocityIn)
{
	delete velocity;
	velocity = velocityIn;
}

void Entity::setVelocityXYZ(float xIn, float yIn, float zIn)
{
	velocity->x = xIn;
	velocity->y = yIn;
	velocity->z = zIn;
}

void Entity::setVelocityX(float xIn)
{
	velocity->x = xIn;
}

void Entity::setVelocityY(float yIn)
{
	velocity->y = yIn;
}

void Entity::setVelocityZ(float zIn)
{
	velocity->z = zIn;
}

//------------------------------------------------GET ----------------------------------------------//

// POSITION

float Entity::getPositionX(void)
{
	return position->x;
}

float Entity::getPositionY(void)
{
	return position->y;
}

float Entity::getPositionZ(void)
{
	return position->z;
}

Coordinate* Entity::getPosition(void)
{
	return position;
}

// VELOCITY

float Entity::getVelocityX(void)
{
	return velocity->x;
}

float Entity::getVelocityY(void)
{
	return velocity->y;
}

float Entity::getVelocityZ(void)
{
	return velocity->z;
}

Coordinate* Entity::getVelocity(void)
{
	return velocity;
}

//------------------------------------------------CHANGE -------------------------------------------//

// POSITION

void Entity::changePositionWithValueXYZ(float xIn, float yIn, float zIn)
{
	position->x += xIn;
	position->y += yIn;
	position->z += zIn;
}

void Entity::changePositionWithValueX(float xIn)
{
	position->x += xIn;
}

void Entity::changePositionWithValueY(float yIn)
{
	position->y += yIn;
}

void Entity::changePositionWithValueZ(float zIn)
{
	position->z += zIn;
}

// VELOCITY

void Entity::changeVelocityWithValueXYZ(float xIn, float yIn, float zIn)
{
	velocity->x += xIn;
	velocity->y += yIn;
	velocity->z += zIn;
}

void Entity::changeVelocityWithValueX(float xIn)
{
	velocity->x += xIn;
}

void Entity::changeVelocityWithValueY(float yIn)
{
	velocity->y += yIn;
}

void Entity::changeVelocityWithValueZ(float zIn)
{
	velocity->z += zIn;
}

//------------------------------------------------UPDATE -------------------------------------------//

void Entity::updatePosition(void)
{
	position->x += velocity->x;
	position->y += velocity->y;
	position->z += velocity->z;
}

//------------------------------------------------ADD ----------------------------------------------//

void Entity::addShape(Shape* shapeIn)
{
	shapes.push_back(shapeIn);
}

//------------------------------------------------REMOVE -------------------------------------------//

void Entity::removeShapes()
{
	while(!shapes.empty())
	{
		delete shapes.back();
		shapes.pop_back();	
	}
}
