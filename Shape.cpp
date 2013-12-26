#include "Shape.h"

template<class T>
Shape<T>::Shape(Vec2* offsetIn, T* ownerIn)
{
	this->offset = offsetIn;
	this->owner = ownerIn;
}

template<class T>
Shape<T>::~Shape(void)
{
	delete offset;	// delete owner separately
}

//------------------------------------------------SET ----------------------------------------------//

template<class T>
void Shape<T>::setOwner(T* ownerIn)
{
	delete owner;
	owner = ownerIn;
}

template<class T>
void Shape<T>::setOffset(Vec2* offsetIn)
{
	delete offset;
	this->offset = offsetIn;
}

template<class T>
void Shape<T>::setAbsPos(Vec2* absPosIn)
{
	delete offset;
	this->offset = new Vec2((*absPosIn)-(*owner->getPosition()));
}

//------------------------------------------------GET ----------------------------------------------//

template<class T>
T* Shape<T>::getOwner(void)
{
	return owner;
}

template<class T>
Vec2 Shape<T>::getOffset(void)
{
	return *offset;
}

template<class T>
Vec2 Shape<T>::getAbsPos(void)
{
	return (*owner->getPosition())+(*offset);
}

//float getArea(void) = 0;
//std::string getShapeType(void) = 0;