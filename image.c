#include "image.h"
#include "palette.h"

#define OUTPUT_BUFFER_SIZE 256

struct image_t* construct_image(COLOR_TYPE* palette_array, unsigned int palette_size, struct image_t* old_image,  struct palette_t* old_palette) {

	struct image_t* new_image;
	COLOR_TYPE* palette_assoc;
	unsigned int i;
	unsigned int palette_cursor;
	unsigned int max_palette;
	unsigned int min_palette;

	unsigned int max_color = pow(2, sizeof(COLOR_TYPE)*8)*sizeof(COLOR_TYPE);
	unsigned int* old_color_assoc = malloc(max_color*sizeof(unsigned int));

	new_image = malloc(sizeof(struct image_t));

	new_image->height = old_image->height;
	new_image->width = old_image->width;
	new_image->pixels = malloc(old_image->height*old_image->width*sizeof(COLOR_TYPE));

	/*
	 * construct new palette
	 */
	palette_assoc = malloc(old_palette->size*sizeof(COLOR_TYPE));

	palette_cursor = 1;


	min_palette = INT_MAX;
	max_palette = 0;

	for(i=0; i<old_palette->size; i++) {

		if(old_palette->data[i] > max_palette)
			max_palette = old_palette->data[i];

		if(old_palette->data[i] < min_palette)
			min_palette = old_palette->data[i];
	}

	for(i=0; i<old_palette->size; i++) {
		unsigned int min, max;

		palette_assoc[i] = palette_cursor > palette_size ? palette_array[palette_size-1] : palette_array[palette_cursor-1];

		min = palette_cursor == 0 ? min_palette : palette_array[palette_cursor-1];
		max = palette_cursor == palette_size ? max_palette : palette_array[palette_cursor];


		if((max+min)/2 < old_palette->data[i]) {
			palette_cursor++;
		}
	}

	for(i=0; i<old_palette->size; i++) {
		old_color_assoc[old_palette->data[i]] = i;
	}


	for(i=0; i<max_color; i++) {

	}


	for(i=0; i<new_image->height*new_image->width; i++) {
		new_image->pixels[i] = palette_assoc[old_color_assoc[old_image->pixels[i]]];
	}

	free(palette_assoc);
	free(old_color_assoc);

	return new_image;

}

void save_image(const char* name, struct image_t* image) {
	char buffer[OUTPUT_BUFFER_SIZE];
	FILE* file;
	unsigned int size;

	if((file = fopen(name, "w+")) == NULL) {
		FATAL_ERROR("Can't open file");
	}

	size = snprintf(buffer, OUTPUT_BUFFER_SIZE, "P5\n");

	fwrite(buffer, size, 1, file);

	size = snprintf(buffer, OUTPUT_BUFFER_SIZE, "%d %d\n", image->width, image->height);

	fwrite(buffer, size, 1, file);

	size = snprintf(buffer, OUTPUT_BUFFER_SIZE, "%d\n", (int)pow(2.0, sizeof(COLOR_TYPE)*8)-1);

	fwrite(buffer, size, 1, file);

	fwrite(image->pixels, sizeof(COLOR_TYPE)*image->height*image->width, 1, file);
}
