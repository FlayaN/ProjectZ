#ifndef SIMPLEFONT_H
#define SIMPLEFONT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "GL_utilities.h"

#include <stdlib.h>
#include <string.h>

#include <stdio.h>
#include <stdarg.h>

void sfMakeRasterFont(void);
//void sfDrawString(int h, int v, const char *s, ...);
void sfDrawString(int h, int v, char *s);
void sfSetRasterSize(int h, int v);

#ifdef __cplusplus
}
#endif

#endif
