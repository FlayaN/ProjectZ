#version 150

in vec2 inPosition;
in vec2 inTexCoord;

uniform mat4 projMatrix;
uniform mat4 modelViewMatrix;

out vec2 texCoord;

void main(void)
{
	texCoord = inTexCoord;
	gl_Position = projMatrix * modelViewMatrix * vec4(inPosition, 0.0, 1.0);
	//gl_Position = vec4(inPosition, 0.0, 1.0);
}