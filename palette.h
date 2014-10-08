#ifndef _PALETTE_H
#define _PALETTE_H

#include <stdlib.h>

#define COLOR_TYPE char

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

struct image_t {
    COLOR_TYPE* pixels;
    size_t width;
    size_t height;
};
typedef struct image_t image_t;

COLOR_TYPE meilleurGris(struct palette_coeff_t* palette, unsigned int valeur_min, unsigned int valeur_max);
float distanceMin(palette_coeff_t* palette, unsigned int valeur_min, unsigned int valeur_max);

#endif
