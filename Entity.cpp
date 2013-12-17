#include "Entity.h"


Entity::Entity(void)
{
	position = new Vec3();
	velocity = new Vec3();
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

void Entity::setPosition(Vec3* positionIn)
{
	delete position;
	position = positionIn;
}

void Entity::setVelocity(Vec3* velocityIn)
{
	delete velocity;
	velocity = velocityIn;
}

//------------------------------------------------GET ----------------------------------------------//

Vec3* Entity::getPosition(void)
{
    return position;
}

Vec3* Entity::getVelocity(void)
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
