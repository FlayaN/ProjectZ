#pragma once

#ifdef __APPLE__
    #include <SDL2/SDL.h>
#else
    #include "SDL.h"
#endif

#include "Coordinate.h"
#include "Shape.h"
#include <vector>

class Entity {
public:
	Entity(void);
	~Entity(void);

	void setPosition(Coordinate*);
	void setPositionXYZ(float, float, float);
	void setPositionX(float);
	void setPositionY(float);
	void setPositionZ(float);

	void setVelocity(Coordinate*);
	void setVelocityXYZ(float, float, float);
	void setVelocityX(float);
	void setVelocityY(float);
	void setVelocityZ(float);

	Coordinate* getPosition(void);
	float getPositionX(void);
	float getPositionY(void);
	float getPositionZ(void);

	Coordinate* getVelocity(void);
	float getVelocityX(void);
	float getVelocityY(void);
	float getVelocityZ(void);

	void changePositionWithValueXYZ(float, float, float);
	void changePositionWithValueX(float);
	void changePositionWithValueY(float);
	void changePositionWithValueZ(float);

	void changeVelocityWithValueXYZ(float, float, float);
	void changeVelocityWithValueX(float);
	void changeVelocityWithValueY(float);
	void changeVelocityWithValueZ(float);

	void updatePosition(void);
	void addShape(Shape*);
	void removeShapes(void);

protected:
	Coordinate* position;
	Coordinate* velocity;
	std::vector<Shape*> shapes; // change to collision boxes based on shapes
};

