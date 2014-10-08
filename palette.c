#include "palette.h"

COLOR_TYPE meilleurGris(struct palette_coeff_t* palette, unsigned int index_min, unsigned int index_max) {
	int i;
	double average = 0;
	unsigned int total_coeff = 0;

	for(i=index_min; i<index_max; i++) {
		average += palette->coeff[i]*palette->model->data[i];
		total_coeff +=palette->coeff[i];
	}

	return round(average/(double)total_coeff);

}

unsigned int distanceMin(struct palette_coeff_t* palette, unsigned int index_min, unsigned int index_max) {
	unsigned int distance = 0;
	unsigned int i;
	COLOR_TYPE best_gray = meilleurGris(palette, index_min, index_max);

	for(i = index_min; i < index_max; i++)
		distance += (palette->model->data[i]-best_gray)*(palette->model->data[i]-best_gray)*palette->coeff[i];

	return distance;
}

struct palette_coeff_t* create_palette(struct image_t* image) {
	struct palette_coeff_t* palette_coeff_return = NULL;

	unsigned int max_color = pow(2, sizeof(COLOR_TYPE)*8)*sizeof(COLOR_TYPE);
	unsigned int color_count = 0;
	unsigned int palette_cursor = 0;
	unsigned int i;

	unsigned int* max_tab_color = malloc(max_color*sizeof(unsigned int));

	memset(max_tab_color, 0, max_color*sizeof(unsigned int));

	for(i=0; i<image->width*image->height; i++) {

		assert((unsigned int)image->pixels[i] < max_color);

		if(max_tab_color[(unsigned int)image->pixels[i]] == 0) {
			color_count++;

		}

		max_tab_color[(unsigned int)image->pixels[i]]++;
	}

	palette_coeff_return = malloc(sizeof(struct palette_coeff_t));
	palette_coeff_return->model = malloc(sizeof(struct palette_t));

	/*
	 *	Remove unused color
	 */

	/* create the two array */
	palette_coeff_return->model->data = malloc(color_count*sizeof(COLOR_TYPE));
	palette_coeff_return->coeff = malloc(color_count*sizeof(COLOR_TYPE));
	palette_coeff_return->model->size = color_count;

	for(i=0; i<max_color; i++) {
		if(max_tab_color[i] != 0) {
			palette_coeff_return->model->data[palette_cursor] = i;
			palette_coeff_return->coeff[palette_cursor] = max_tab_color[i];
			palette_cursor++;
		}

	}

	return palette_coeff_return;


}
