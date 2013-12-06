#include "Entity.h"


Entity::Entity(void) {
	position = new Coordinate();
	velocity = new Coordinate();
}

Entity::~Entity(void) {
	delete position;
	delete velocity;
}

Coordinate* Entity::getPosition() {
	return position;
}

Coordinate* Entity::getVelocity() {
	return velocity;
}