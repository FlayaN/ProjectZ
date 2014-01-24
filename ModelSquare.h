#ifndef MODELSQUARE_H
#define MODELSQUARE_H

#include <vector>
#include <iostream>
#include <unordered_map>
#include <string>

#include "lib/glm/vec2.hpp"

#include "GL_utilities.h"
#include "Defines.h"
#include "Utility.h"

enum class BUFFTYPE
{
	VERTEX,
	TEXCOORD,
	NORMAL,
	INDEX,
	COLOR
};

class ModelSquare
{
public:
	ModelSquare(std::string, std::string);
	~ModelSquare(void);

	void addUniform(GLchar*);
	void addAttrib(BUFFTYPE, GLchar*);

	GLuint getBuffer(BUFFTYPE);
	GLuint getUniform(GLchar*);
	GLuint getAttrib(GLchar*);
	GLuint getVAO(void);
	GLuint getProg(void);

	float* getVertexArray(void);
	float* getTexCoordArray(void);
	float* getNormalArray(void);
	int* getIndexArray(void);
	float* getColorArray(void);

	int getNumVertices(void);
	int getNumIndices(void);


	
private:
	GLuint vertexArrayObj;
	GLuint vertexBuffer;
	GLuint texCoordBuffer;
	GLuint normalBuffer;
	GLuint indexBuffer;
	GLuint colorBuffer;

	std::vector<glm::vec2> vertexArray;
	std::vector<glm::vec2> texCoordArray;
	std::vector<glm::vec2> normalArray;
	std::vector<glm::ivec2> indexArray;
	std::vector<glm::vec2> colorArray;

	std::HashMap<GLchar*, GLuint> uniformLocations;
	std::HashMap<GLchar*, GLuint> attribLocations;
	GLuint prog;
};

#endif