#include "image_reader.h"
#include "palette.h"
void print_command_line() {
	printf("./pgm <image-pathname> <gray-level>\n");
}


int main(int argc, char** argv) {

	struct image_t* image;
	struct palette_coeff_t* palette;
	unsigned int k;

	if(argc < 2) {
		print_command_line();
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


	free(image->pixels);
	free(image);

	free(palette->model->data);
	free(palette->model);
	free(palette->coeff);
	free(palette);

	return EXIT_SUCCESS;
}
