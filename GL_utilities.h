#ifndef GLUTILITIES_H
#define GLUTILITIES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <GL/glew.h>

void printError(const char *functionName);
GLuint loadShaders(const char *vertFileName, const char *fragFileName);
GLuint loadShadersG(const char *vertFileName, const char *fragFileName, const char *geomFileName);
void dumpInfo(void);

#ifdef __cplusplus
}
#endif

#endif
