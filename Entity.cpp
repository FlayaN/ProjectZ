#include "Entity.h"


Entity::Entity(void)
{
	position = new Vec2();
	velocity = new Vec2();
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

void Entity::setPosition(Vec2* positionIn)
{
	delete position;
	position = positionIn;
}

void Entity::setVelocity(Vec2* velocityIn)
{
	delete velocity;
	velocity = velocityIn;
}

//------------------------------------------------GET ----------------------------------------------//

Vec2* Entity::getPosition(void)
{
    return position;
}

Vec2* Entity::getVelocity(void)
{
	return velocity;
}

//------------------------------------------------UPDATE -------------------------------------------//

void Entity::updatePosition(void)
{
	position->x += velocity->x;
	position->y += velocity->y;
	//position->z += velocity->z;
	// kanske uppdatera shapes
}

//------------------------------------------------ADD ----------------------------------------------//

void Entity::addShape(Shape<Entity>* shapeIn)
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
