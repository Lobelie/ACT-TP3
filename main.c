#include "image_reader.h"
#include "palette.h"

void print_command_line() {
	printf("./pgm <image-pathname> <gray-level>\n");
}


int main(int argc, char** argv) {

	struct image_t* image;
	struct palette_coeff_t* palette;

	if(argc < 2) {
		print_command_line();
        return EXIT_FAILURE;
	}
	else {
		image = read_image(argv[1]);
	}

	fflush(stdout);
	palette = create_palette(image);

    printf("meilleurGris = %d\n", meilleurGris(palette, 0, palette->model->size));
    printf("distanceMin = %f\n", distanceMin(palette, 0, 256));

	free(image->pixels);
	free(image);

	free(palette->model->data);
	free(palette->model);
	free(palette->coeff);
	free(palette);

	return EXIT_SUCCESS;
}
