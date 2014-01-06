#include "Shape.h"

template<class T>
Shape<T>::Shape(glm::vec2* posOffsetIn, float rotOffsetIn, T* ownerIn)
{
	posOffset = posOffsetIn;
	rotOffset = rotOffsetIn;
	owner = ownerIn;
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
	owner = ownerIn;
}

template<class T>
void Shape<T>::setPosOffset(glm::vec2* offsetIn)
{
	delete posOffset;
	offset = offsetIn;
}

template<class T>
void Shape<T>::setAbsPos(glm::vec2* absPosIn)
{
	delete offset;
	offset = new glm::vec2((*absPosIn)-(*owner->getPosition()));
}

template<class T>
void Shape<T>::setRotOffset(float rotOffsetIn)
{
	rotOffset = rotOffsetIn;
}

template<class T>
void Shape<T>::setAbsRot(float absRotIn)
{
	rotOffset = absRotIn-(*owner->getRotation());
}

//------------------------------------------------GET ----------------------------------------------//

template<class T>
T* Shape<T>::getOwner(void)
{
	return owner;
}

template<class T>
glm::vec2 Shape<T>::getPosOffset(void)
{
	return *posOffset;
}

template<class T>
glm::vec2 Shape<T>::getAbsPos(void)
{
	return (*owner->getPosition())+(*posOffset);
}

template<class T>
float Shape<T>::getRotOffset(void)
{
	return rotOffset;
}

template<class T>
float Shape<T>::getAbsRot(void)
{
	return (*owner->getRotation())+rotOffset;
}

//float getArea(void) = 0;
//std::string getShapeType(void) = 0;