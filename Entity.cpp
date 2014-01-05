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

void Entity::setRotation(float rotationIn)
{
	rotation = rotationIn;
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

float Entity::getRotation(void)
{
	return rotation;
}

std::vector<Shape<Entity>*> Entity::getShapes(void)
{
	return shapes;
}

std::vector<Entity*> Entity::getChildren(void)
{
	return children;
}

//------------------------------------------------UPDATE -------------------------------------------//

void Entity::updatePosition(void)
{
	position->x += velocity->x;
	position->y += velocity->y;

	for each (Entity* child in children)
	{
		child->updatePosition();
	}
}

//------------------------------------------------ADD ----------------------------------------------//

void Entity::addShape(Shape<Entity>* shapeIn)
{
	shapes.push_back(shapeIn);
}

void Entity::addChild(Entity* childIn)
{
	children.push_back(childIn);
}

void Entity::insertShapeAt(int indexIn, Shape<Entity>* shapeIn)
{
	shapes.insert(shapes.begin()+indexIn, shapeIn);
}

void Entity::insertChildAt(int indexIn, Entity* childIn)
{
	children.insert(children.begin()+indexIn, childIn);
}

//------------------------------------------------REMOVE -------------------------------------------//

void Entity::removeShapes(void)
{
	while(!shapes.empty())
	{		
		delete shapes.back();
		shapes.pop_back();
	}
}

void Entity::removeChildren(void)
{
	while(!children.empty())
	{		
		delete children.back();
		children.pop_back();
	}
}

void Entity::removeShapeAt(int indexIn)
{
	delete shapes.at(indexIn);
	shapes.erase(shapes.begin()+indexIn);
}

void Entity::removeChildAt(int indexIn)
{
	delete children.at(indexIn);
	children.erase(children.begin()+indexIn);
}

//------------------------------------------------RELEASE-------------------------------------------//

void Entity::releaseChildren(void)
{
	children.clear();
}