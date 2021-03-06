#include "palette.h"

#define UNINITIAZLIZED_UINT 0xFFFFFFFF

static unsigned int* back_trace_array = NULL;

COLOR_TYPE meilleurGris(struct palette_coeff_t* palette, unsigned int index_min, unsigned int index_max) {
	int i;
    double average = 0;
	unsigned int total_coeff = 0;

	for(i=index_min; i<index_max; i++) {
        average += palette->coeff[i] * palette->model->data[i];
        total_coeff += palette->coeff[i];
	}

    return round(average/(double)total_coeff);

}

unsigned int distanceMin(palette_coeff_t* palette, unsigned int index_min, unsigned int index_max) {
	unsigned int distance = 0;
	unsigned int i;

	COLOR_TYPE best_gray = meilleurGris(palette, index_min, index_max);

	for(i=index_min; i<index_max; i++) {
		distance += (palette->model->data[i]-best_gray)*(palette->model->data[i]-best_gray)*palette->coeff[i];
	}

	return distance;
}

unsigned int reduce_palette(struct palette_coeff_t* palette, unsigned int current_index, unsigned int k) {
	static unsigned int* save_array = NULL;


	if(save_array == NULL) {
		unsigned int i;
		save_array = malloc(palette->model->size*(k+1)*sizeof(unsigned int));
		back_trace_array = malloc(palette->model->size*(k+1)*sizeof(unsigned int));

		for(i=0; i<palette->model->size*(k+1); i++)
			save_array[i] = UNINITIAZLIZED_UINT;
	}

	if(save_array[k*palette->model->size+current_index] != UNINITIAZLIZED_UINT) {
		return save_array[k*palette->model->size+current_index];
	}

	if(k == 1) {
		save_array[k*palette->model->size+current_index] = distanceMin(palette, current_index, palette->model->size);
		return save_array[k*palette->model->size+current_index];
	}
	else {
		unsigned int min = INT_MAX;
		unsigned int min_index = INT_MAX;
		unsigned int i;

		for(i = current_index+1; i < palette->model->size; i++) {
			unsigned int current = distanceMin(palette, current_index, i)+reduce_palette(palette, i, k-1);

			if(current < min) {
				min = current;
				min_index = i;
			}
		}


		save_array[k*palette->model->size+current_index] = min;
		back_trace_array[k*palette->model->size+current_index] = min_index;
		return min;
	}
}

struct palette_coeff_t* create_palette(struct image_t* image)  {
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
	palette_coeff_return->coeff = malloc(color_count*sizeof(unsigned int));
	palette_coeff_return->model->size = color_count;

	for(i=0; i<max_color; i++) {
		if(max_tab_color[i] != 0) {
			palette_coeff_return->model->data[palette_cursor] = i;
			palette_coeff_return->coeff[palette_cursor] = max_tab_color[i];
			palette_cursor++;
		}

	}

	free(max_tab_color);

	return palette_coeff_return;

}

COLOR_TYPE* backtrace_palette_index(unsigned int palette_size, unsigned int current_index, unsigned int k, unsigned int* size, struct palette_coeff_t* palette) {
	unsigned int i, last_max = 0;
	COLOR_TYPE* return_array;

	assert(back_trace_array != NULL);

	*size = k;
	return_array = malloc(*size*sizeof(COLOR_TYPE));

	i = 0;

	while(1 < k) {
		current_index = back_trace_array[k*palette_size+current_index];
		return_array[i] = meilleurGris(palette, last_max, current_index);
		last_max = current_index;
		i++;
		k--;

	}

	return_array[i] = meilleurGris(palette, last_max, palette->model->size);

	return return_array;

}
