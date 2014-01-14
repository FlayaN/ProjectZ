#include "Entity.h"


Entity::Entity(void)
{
	position = glm::vec2();
}

Entity::~Entity(void)
{
	for(int i = 0; i < shapes.size(); i++)
	{
		delete shapes[i];
	}
}

//------------------------------------------------SET ----------------------------------------------//

void Entity::setPosition(glm::vec2 positionIn)
{
	position = positionIn;
}

void Entity::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

void Entity::setRotation(float rotationIn)
{
	rotation = rotationIn;
}

//------------------------------------------------GET ----------------------------------------------//

glm::vec2 Entity::getPosition(void)
{
    return position;
}

float Entity::getRotation(void)
{
	return rotation;
}

std::vector<Shape*> Entity::getShapes(void)
{
	return shapes;
}

std::vector<Entity*> Entity::getChildren(void)
{
	return children;
}

//------------------------------------------------ADD ----------------------------------------------//

void Entity::addShape(Shape* shapeIn)
{
	shapes.push_back(shapeIn);
}

void Entity::addChild(Entity* childIn)
{
	children.push_back(childIn);
}

void Entity::insertShapeAt(int indexIn, Shape* shapeIn)
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