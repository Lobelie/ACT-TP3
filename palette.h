#ifndef _PALETTE_H
#define _PALETTE_H

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#include "header.h"
#include "image.h"


struct palette_t {
	COLOR_TYPE* data;
	size_t size;
};

struct palette_coeff_t {
	struct palette_t* model;
	unsigned int* coeff;
};

/*
 *	Create palette and palette_coeff struct. this two structure are owned by caller
 */
struct palette_coeff_t* create_palette(struct image_t* image);

COLOR_TYPE meilleurGris(struct palette_coeff_t* palette, unsigned int index_min, unsigned int index_max);

unsigned int distanceMin(struct palette_coeff_t* palette, unsigned int index_min, unsigned int index_max);

#endif
