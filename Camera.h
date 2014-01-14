#ifndef CAMERA_H
#define CAMERA_H

#include "lib/glm/mat4x4.hpp"
#include "lib/glm/vec3.hpp"
#include "lib/glm/gtc/matrix_transform.hpp"

#include "Defines.h"
#include "EntityPlayer.h"

class Camera
{
public:
	Camera(EntityPlayer*);
	~Camera(void);

	glm::mat4 getOrthoMatrix(void);

	glm::vec2 getPos(void);

	void update(void);
private:
	glm::mat4 orthoMatrix;
	EntityPlayer* player;
};

#endif