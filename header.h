#ifndef _HEADER_H
#define _HEADER_H

#include <stdio.h>
#include <stdlib.h>

#define FATAL_ERROR(MSG) { fprintf(stderr, MSG "\n"); exit(EXIT_FAILURE); }
#define VERBOSE(MSG) { fprintf(stdout, MSG "\n"); }

#define COLOR_TYPE unsigned char

#endif
