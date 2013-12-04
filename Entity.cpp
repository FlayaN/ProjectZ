#include "Entity.h"


Entity::Entity(void) {
	position = new Position();
	velocity = new Position();
}

Entity::~Entity(void) {
	delete position;
	delete velocity;
}

Position* Entity::getPosition() {
	return position;
}

Position* Entity::getVelocity() {
	return velocity;
}