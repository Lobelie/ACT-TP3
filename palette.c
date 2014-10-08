#include "palette.h"

#include "math.h"

COLOR_TYPE meilleurGris(struct palette_coeff_t* palette, unsigned int valeur_min, unsigned int valeur_max) {
    double average;
    unsigned int total_coeff = 0;

    for(i=valeur_min; i<valeur_max; i++) {
        average += palette->coeff[i] * palette->model->data[i];
        total_coeff += palette->coeff[i];
    }

    return floor(average/(double)total_coeff);
}

