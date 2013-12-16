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

void Entity::setPosition(Coordinate* positionIn)
{
	delete position;
	position = positionIn;
}

void Entity::setVelocity(Coordinate* velocityIn)
{
	delete velocity;
	velocity = velocityIn;
}

//------------------------------------------------GET ----------------------------------------------//

Coordinate* Entity::getPosition(void)
{
	return position;
}

Coordinate* Entity::getVelocity(void)
{
	return velocity;
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
