#ifndef TYPEPLAYER_H
#define TYPEPLAYER_H

#include <string>

#include "lib/glm/vec2.hpp"

struct TypePlayer
{
	glm::vec2 startPos;
	float rotation;
	glm::vec2 size;
	std::string texture;
	float acceleration;
	float maxSpeed;
	std::string bb;
};

#endif