#version 150

in vec2 inPosition;

uniform mat4 projMatrix;
uniform mat4 modelViewMatrix;

void main(void)
{
	gl_Position = projMatrix * modelViewMatrix * vec4(inPosition, 0.0, 1.0);
}