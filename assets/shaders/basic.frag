#version 150

in vec2 texCoord;

uniform sampler2D texUnit;

out vec4 outColor;

void main(void)
{
	//outColor = vec4(0.0, 0.0, 1.0, 1.0);
	outColor = texture2D(texUnit,texCoord);
}
