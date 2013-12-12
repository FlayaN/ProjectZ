#include "CollisionHandler.h"


CollisionHandler::CollisionHandler(void)
{
}


CollisionHandler::~CollisionHandler(void)
{
}

//------------------------------------------------TEST ---------------------------------------------//

bool CollisionHandler::testCollision(Shape* shapeOne, Shape* shapeTwo)
{
	CircleShape* shapeOneIsCircle = dynamic_cast<CircleShape*> (shapeOne);  // Null if not CircleShape
	CircleShape* shapeTwoIsCircle = dynamic_cast<CircleShape*> (shapeTwo);  // Null if not CircleShape

	if(shapeOneIsCircle != NULL && shapeTwoIsCircle != NULL)
	{
		// do collision check for circle circle
	}
}
