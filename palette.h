#ifndef _PALETTE_H
#define _PALETTE_H

#include <stdlib.h>

#define COLOR_TYPE char

struct palette_t {
    COLOR_TYPE* data;
    size_t size;
};

struct palette_coeff_t {
    struct palette_t* model;
    unsigned int* coeff;
};

struct image_t {
    COLOR_TYPE* pixels;
    size_t width;
    size_t height;
};

COLOR_TYPE meilleurGris(struct palette_coeff_t* palette, unsigned int valeur_min, unsigned int valeur_max);

#endif
