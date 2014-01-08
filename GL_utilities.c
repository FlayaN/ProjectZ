// GL utilities, bare essentials
// By Ingemar Ragnemalm

// August 2012:
// FBO creation/usage routines.
// Geometry shader support synched with preliminary version.
// September 2012: Improved infolog printouts with file names.
// 120910: Clarified error messages from shader loader.
// 120913: Re-activated automatic framebuffer checks for UseFBO().
// Fixed FUBAR in InitFBO().

//#define GL3_PROTOTYPES
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "GL_utilities.h"

// Shader loader

char* readFile(char *file)
{
	FILE *fptr;
	long length;
	char *buf;

	fptr = fopen(file, "rb"); /* Open file for reading */
	if (!fptr) /* Return NULL on failure */
		return NULL;
	fseek(fptr, 0, SEEK_END); /* Seek to the end of the file */
	length = ftell(fptr); /* Find out how many bytes into the file we are */
	buf = (char*)malloc(length+1); /* Allocate a buffer for the entire length of the file and a null terminator */
	fseek(fptr, 0, SEEK_SET); /* Go back to the beginning of the file */
	fread(buf, length, 1, fptr); /* Read the contents of the file in to the buffer */
	fclose(fptr); /* Close the file */
	buf[length] = 0; /* Null terminator */
	
	return buf; /* Return the buffer */
}

// Infolog: Show result of shader compilation
void printShaderInfoLog(GLuint obj, const char *fn)
{
	GLint infologLength = 0;
	GLint charsWritten  = 0;
	char *infoLog;

	glGetShaderiv(obj, GL_INFO_LOG_LENGTH, &infologLength);

	if (infologLength > 2)
	{
		printf("[From %s:]\n", fn);
		infoLog = (char *)malloc(infologLength);
		glGetShaderInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
		free(infoLog);
	}
}

void printProgramInfoLog(GLuint obj, const char *vfn, const char *ffn, const char *gfn)
{
	GLint infologLength = 0;
	GLint charsWritten  = 0;
	char *infoLog;

	glGetProgramiv(obj, GL_INFO_LOG_LENGTH,&infologLength);

	if (infologLength > 2)
	{
		if (gfn == NULL)
			printf("[From %s+%s:]\n", vfn, ffn);
		else
			printf("[From %s+%s+%s:]\n", vfn, ffn, gfn);
		infoLog = (char *)malloc(infologLength);
		glGetProgramInfoLog(obj, infologLength, &charsWritten, infoLog);
		printf("%s\n",infoLog);
		free(infoLog);
	}
}

// Compile a shader, return reference to it
GLuint compileShaders(const char *vs, const char *fs, const char *gs, const char *vfn, const char *ffn, const char *gfn)
{
	GLuint v,f,g,p;
	
	v = glCreateShader(GL_VERTEX_SHADER);
	f = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(v, 1, &vs, NULL);
	glShaderSource(f, 1, &fs, NULL);
	glCompileShader(v);
	glCompileShader(f);
	if (gs != NULL)
	{
		g = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(g, 1, &gs, NULL);
		glCompileShader(g);
	}
	
	p = glCreateProgram();
	glAttachShader(p,v);
	glAttachShader(p,f);
	if (gs != NULL)
		glAttachShader(p,g);
	glLinkProgram(p);
	glUseProgram(p);
	
	printShaderInfoLog(v, vfn);
	printShaderInfoLog(f, ffn);
	if (gs != NULL)	printShaderInfoLog(g, gfn);
	
	printProgramInfoLog(p, vfn, ffn, gfn);
	
	return p;
}

GLuint loadShaders(const char *vertFileName, const char *fragFileName)
{
	return loadShadersG(vertFileName, fragFileName, NULL);
}

GLuint loadShadersG(const char *vertFileName, const char *fragFileName, const char *geomFileName)
// With geometry shader support
{
	char *vs, *fs, *gs;
	GLuint p = 0;
	
	vs = readFile((char *)vertFileName);
	fs = readFile((char *)fragFileName);
	//gs = readFile((char *)geomFileName);
	if (vs==NULL)
		printf("Failed to read %s from disk.\n", vertFileName);
	if (fs==NULL)
		printf("Failed to read %s from disk.\n", fragFileName);
	//if ((gs==NULL) && (geomFileName != NULL))
	//	printf("Failed to read %s from disk.\n", geomFileName);
	if ((vs!=NULL)&&(fs!=NULL))
		p = compileShaders(vs, fs, NULL, vertFileName, fragFileName, geomFileName);
	if (vs != NULL) free(vs);
	if (fs != NULL) free(fs);
	//if (gs != NULL) free(gs);
	return p;
}

// End of Shader loader

void dumpInfo(void)
{
   printf ("Vendor: %s\n", glGetString (GL_VENDOR));
   printf ("Renderer: %s\n", glGetString (GL_RENDERER));
   printf ("Version: %s\n", glGetString (GL_VERSION));
   printf ("GLSL: %s\n", glGetString (GL_SHADING_LANGUAGE_VERSION));
   printError ("dumpInfo");
}

static GLenum lastError = 0;
static char lastErrorFunction[1024] = "";

/* report GL errors, if any, to stderr */
void printError(const char *functionName)
{
   GLenum error;
   while (( error = glGetError() ) != GL_NO_ERROR)
   {
       if ((lastError != error) || (strcmp(functionName, lastErrorFunction)))
       {
	       fprintf (stderr, "GL error 0x%X detected in %s\n", error, functionName);
	       strcpy(lastErrorFunction, functionName);
	       lastError = error;
       }
   }
}
