#include "Camera.h"

Camera::Camera(EntityPlayer* playerIn)
{
	player = playerIn;
	orthoMatrix = glm::ortho(0.0f, (float)Settings::Graphics::screenWidth, 0.0f, (float)Settings::Graphics::screenHeight);
}

Camera::~Camera(void)
{

}

glm::mat4 Camera::getOrthoMatrix(void)
{
	return orthoMatrix;
}

glm::vec2 Camera::getPos(void)
{
	return *player->getPosition();
}

void Camera::update(void)
{
	//viewMa
}