#version 150

in vec2 texCoord;

uniform int textureId;
uniform int maxId;
uniform int widthPerTexture;
uniform sampler2D texUnit;

out vec4 outColor;

vec2 getTextureCoords()
{
	return vec2((textureId%widthPerTexture + texCoord.x)/maxId , texCoord.y);
}

void main(void)
{
	outColor = texture2D(texUnit,getTextureCoords());
}
