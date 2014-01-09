#include "ModelSquare.h"

ModelSquare::ModelSquare(std::string vert, std::string frag)
{
	prog = loadShaders(vert.c_str(), frag.c_str());
	glGenVertexArrays(1, &vertexArrayObj);

	vertexArray.push_back(glm::vec2(0.0, 0.0));
	vertexArray.push_back(glm::vec2(0.0, 1.0));
	vertexArray.push_back(glm::vec2(1.0, 0.0));
	vertexArray.push_back(glm::vec2(1.0, 1.0));

	texCoordArray.push_back(glm::vec2(0.0f, 1.0f));
	texCoordArray.push_back(glm::vec2(0.0f, 0.0f));
	texCoordArray.push_back(glm::vec2(1.0f, 1.0f));
	texCoordArray.push_back(glm::vec2(1.0f, 0.0f));

	printError("ModelSquare|ModelSquare");
}

ModelSquare::~ModelSquare(void)
{
	
}

void ModelSquare::addUniform(GLchar* uniform)
{
	GLuint uniformLoc = glGetUniformLocation(prog, uniform);
	std::cout << std::string("Uniform ") + std::string(uniform) + std::string(" with ID: ") << uniformLoc << std::endl;
	uniformLocations[uniform] = uniformLoc;
}

void ModelSquare::addAttrib(BUFFTYPE type, GLchar* attrib)
{
	int size = 2;
	switch (type)
	{
	case BUFFTYPE::VERTEX:
		size = 2;
		glGenBuffers(1, &vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, getNumVertices()*size*sizeof(GLfloat), getVertexArray(), GL_STATIC_DRAW);
		break;
	case BUFFTYPE::TEXCOORD:
		size = 2;
		glGenBuffers(1, &texCoordBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
		glBufferData(GL_ARRAY_BUFFER, getNumVertices()*size*sizeof(GLfloat), getTexCoordArray(), GL_STATIC_DRAW);
		break;
	case BUFFTYPE::NORMAL:
		size = 2;
		glGenBuffers(1, &normalBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glBufferData(GL_ARRAY_BUFFER, getNumVertices()*size*sizeof(GLfloat), getNormalArray(), GL_STATIC_DRAW);
		break;
	case BUFFTYPE::INDEX:
		size = 2;
		glGenBuffers(1, &indexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ARRAY_BUFFER, getNumIndices()*size*sizeof(GLfloat), getIndexArray(), GL_STATIC_DRAW);
		break;
	case BUFFTYPE::COLOR:
		size = 3;
		glGenBuffers(1, &colorBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
		glBufferData(GL_ARRAY_BUFFER, getNumVertices()*size*sizeof(GLfloat), getColorArray(), GL_STATIC_DRAW);
		break;
	default:
		break;
	}

	glBindVertexArray(vertexArrayObj);
	GLuint attribLoc = glGetAttribLocation(prog, attrib);
	glVertexAttribPointer(attribLoc, size, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attribLoc);
	std::cout << std::string("Attribute ") + std::string(attrib) + std::string(" with ID: ") << attribLoc << std::endl;
	attribLocations[attrib] = attribLoc;
}

//GET

GLuint ModelSquare::getBuffer(BUFFTYPE type)
{
	switch (type)
	{
	case BUFFTYPE::VERTEX:
		if(glIsBuffer(vertexBuffer))
			return vertexBuffer;
		else
		{
			std::cout << "VertexBuffer is not initialized" << std::endl;
			return 0;
		}
		break;
	case BUFFTYPE::TEXCOORD:
		if(glIsBuffer(texCoordBuffer))
			return texCoordBuffer;
		else
		{
			std::cout << "TexCoordBuffer is not initialized" << std::endl;
			return 0;
		}
		break;
	case BUFFTYPE::NORMAL:
		if(glIsBuffer(normalBuffer))
			return normalBuffer;
		else
		{
			std::cout << "NormalBuffer is not initialized" << std::endl;
			return 0;
		}
		break;
	case BUFFTYPE::INDEX:
		if(glIsBuffer(indexBuffer))
			return indexBuffer;
		else
		{
			std::cout << "IndexBuffer is not initialized" << std::endl;
			return 0;
		}
		break;
	case BUFFTYPE::COLOR:
		if(glIsBuffer(colorBuffer))
			return colorBuffer;
		else
		{
			std::cout << "ColorBuffer is not initialized" << std::endl;
			return 0;
		}
		break;
	default:
		break;
	}
	return 0;
}

GLuint ModelSquare::getUniform(GLchar* uniform)
{
	return uniformLocations[uniform];
}

GLuint ModelSquare::getAttrib(GLchar* attrib)
{
	return attribLocations[attrib];
}

GLuint ModelSquare::getVAO(void)
{
	return vertexArrayObj;
}

GLuint ModelSquare::getProg(void)
{
	return prog;
}

float* ModelSquare::getVertexArray(void)
{
	if(vertexArray.size() == 0)
		return nullptr;
	return &vertexArray[0].x;
}

float* ModelSquare::getTexCoordArray(void)
{
	if(texCoordArray.size() == 0)
		return nullptr;
	return &texCoordArray[0].x;
}

float* ModelSquare::getNormalArray(void)
{
	if(normalArray.size() == 0)
		return nullptr;
	return &normalArray[0].x;
}

int* ModelSquare::getIndexArray(void)
{
	if(indexArray.size() == 0)
		return nullptr;
	return &indexArray[0].x;
}

float* ModelSquare::getColorArray(void)
{
	if(colorArray.size() == 0)
		return nullptr;
	return &colorArray[0].x;
}

int ModelSquare::getNumVertices(void)
{
	return vertexArray.size();
}

int ModelSquare::getNumIndices(void)
{
	return indexArray.size();
}