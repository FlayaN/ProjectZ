#include "CircleShape.h"

template<class T>
CircleShape<T>::CircleShape(Vec3* positionIn, T* ownerIn = nullptr) : Shape<T>(ownerIn)
{
	radius = radiusIn;
}

template<class T>
CircleShape<T>::~CircleShape(void)
{
}

//------------------------------------------------SET ----------------------------------------------//

template<class T>
void CircleShape<T>::setRadius(float radiusIn)
{
	radius = radiusIn;
}

//------------------------------------------------GET ----------------------------------------------//

template<class T>
float CircleShape<T>::getRadius(void)
{
	return radius;
}

template<class T>
float CircleShape<T>::getArea(void)
{
	return 4.0*3.14*pow(radius, 3.0)/3.0;
}

template<class T>
std::string CircleShape<T>::getShapeType(void)
{
	return "circle";
}