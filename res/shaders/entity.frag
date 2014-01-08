#version 150

out vec4 outColor;

uniform sampler2D texUnit;

in vec2 texCoord;

void main(void)
{
	//outColor = vec4(0.0, 1.0, 1.0, 1.0);
	outColor = texture2D(texUnit,texCoord);
}
