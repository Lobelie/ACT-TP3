#ifndef _IMAGE_H
#define _IMAGE_H

#include <stdlib.h>

#include "header.h"

struct image_t {
	COLOR_TYPE* pixels;
	size_t width;
	size_t height;
};
typedef struct image_t image_t;


#endif
