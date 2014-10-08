#ifndef _PALETTE_H
#define _PALETTE_H

#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <float.h>

#include "header.h"
#include "image.h"


struct palette_t {
	COLOR_TYPE* data;
	size_t size;
};
typedef struct palette_t palette_t;

struct palette_coeff_t {
	struct palette_t* model;
	unsigned int* coeff;
};
typedef struct palette_coeff_t palette_coeff_t;


/*
 *	Create palette and palette_coeff struct. this two structure are owned by caller
 */
struct palette_coeff_t* create_palette(struct image_t* image);

COLOR_TYPE meilleurGris(struct palette_coeff_t* palette, unsigned int valeur_min, unsigned int valeur_max);
float distanceMin(palette_coeff_t* palette, unsigned int index_min, unsigned int index_max);

#endif
