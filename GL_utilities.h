#ifndef GLUTILITIES_H
#define GLUTILITIES_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __APPLE__
    #include "glew.h"
    #include <OpenGL/gl3.h>
#else
    #include <GL/glew.h>
#endif

void printError(const char *functionName);
GLuint loadShaders(const char *vertFileName, const char *fragFileName);
GLuint loadShadersG(const char *vertFileName, const char *fragFileName, const char *geomFileName);
void dumpInfo(void);

#ifdef __cplusplus
}
#endif

#endif
