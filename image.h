#ifndef _IMAGE_H
#define _IMAGE_H

#include <stdlib.h>
#include <math.h>
#include <limits.h>

#include "header.h"

struct palette_t;

struct image_t {
	COLOR_TYPE* pixels;
	size_t width;
	size_t height;
};
typedef struct image_t image_t;

/*
 *	Return new iamge owned by caller
 */
struct image_t* construct_image(COLOR_TYPE* palette_array, unsigned int palette_size, struct image_t* old_image,  struct palette_t* old_palette);

void save_image(const char* name, struct image_t* image);


#endif
