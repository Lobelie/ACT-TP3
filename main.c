#include "image_reader.h"
#include "palette.h"
void print_command_line() {
	printf("./pgm <image-pathname> <gray-level> <output-pathname>\n");
}


int main(int argc, char** argv) {

	struct image_t* image;
	struct image_t* new_image;
	struct palette_coeff_t* palette;
	unsigned int k;
	COLOR_TYPE* new_coeff;
	unsigned int new_coeff_size;
	unsigned int i;

	if(argc != 4) {
		print_command_line();
        return EXIT_FAILURE;
	}
	else {
		image = read_image(argv[1]);
		k = atoi(argv[2]);
	}

	fflush(stdout);
	palette = create_palette(image);

	printf("palette : %d\n", palette->model->size);

	printf("meilleur gris : %d\n", meilleurGris(palette, 0, palette->model->size));

	printf("distance min : %d\n", distanceMin(palette, 0, palette->model->size));

	printf("reduce palette : %d\n", reduce_palette(palette, 0, k));

	new_coeff = backtrace_palette_index(palette->model->size, 0, k, &new_coeff_size, palette->model);

	printf("Backtrace : ");
	for(i = 0; i<new_coeff_size; i++) {
		printf("%d ", new_coeff[i]);
	}
	printf("\n");

	new_image = construct_image(new_coeff, new_coeff_size, image, palette->model);

	save_image(argv[3], new_image);


	free(new_image->pixels);
	free(new_image);


	free(new_coeff);

	free(image->pixels);
	free(image);

	free(palette->model->data);
	free(palette->model);
	free(palette->coeff);
	free(palette);

	return EXIT_SUCCESS;
}
