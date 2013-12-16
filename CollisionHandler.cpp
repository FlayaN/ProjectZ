#include "CollisionHandler.h"

//------------------------------------------------TEST ---------------------------------------------//

bool CollisionHandler::testCollision(Shape* shapeOne, Shape* shapeTwo)
{
	CircleShape* shapeOneIsCircle = dynamic_cast<CircleShape*> (shapeOne);  // Null if not CircleShape
	CircleShape* shapeTwoIsCircle = dynamic_cast<CircleShape*> (shapeTwo);  // Null if not CircleShape

	if(shapeOneIsCircle != NULL && shapeTwoIsCircle != NULL)
	{
		// do collision check for circle circle
	}

	return true;
}

bool CollisionHandler::intersects(SDL_Rect* r1, SDL_Rect* r2)
{
	if(r1 == nullptr || r2 == nullptr)
		return false;

	int tw = r1->w;
    int th = r1->h;
    int rw = r2->w;
    int rh = r2->h;
    if (rw <= 0 || rh <= 0 || tw <= 0 || th <= 0) {
        return false;
    }
    int tx = r1->x;
    int ty = r1->y;
    int rx = r2->x;
    int ry = r2->y;
    rw += rx;
    rh += ry;
    tw += tx;
    th += ty;
    //      overflow || intersect
    return ((rw < rx || rw > tx) &&
            (rh < ry || rh > ty) &&
            (tw < tx || tw > rx) &&
            (th < ty || th > ry));
}