#include "image_reader.h"

#define PGM_MODE_AASCII 0
#define PGM_MODE_BINARY 1


static char* _next_token(char* str) {
	unsigned int cursor = 0;
	unsigned int begin;
	char* str_return;

	while(str[cursor] != '\0' && isspace(str[cursor]))
		cursor++;

	if(str[cursor] == '\0')
		return NULL;

	begin = cursor;

	while(str[cursor] != '\0' && !isspace(str[cursor]))
		cursor++;

	if(cursor == begin)
		return NULL;

	str_return = malloc(cursor-begin+1);

	memcpy(str_return, str+begin, cursor-begin);
	str_return[cursor-begin+1] = '\0';

	return str_return;


}

struct image_t* read_image(const char* pathname) {

	/*
	 *	find ext
	 */

	char* last_dot;

	last_dot = strrchr(pathname, '.');

	if(last_dot == NULL) {
		FATAL_ERROR("Image extention not found");
	}


	printf("Image extention : %s\n", last_dot+1);

	if(strcmp(last_dot+1, "pgm") == 0) {
		return read_pgm_format(pathname);
	}
	else {
		FATAL_ERROR("Unreconized format image");
	}

	return NULL;
}

struct image_t* read_pgm_format(const char* pathname) {

	FILE* file;
	char magic[3];
	char* line = NULL;
	size_t line_length = 0;
	int cont;
	char* str = NULL;
	struct image_t* image;
	unsigned int previous_size;
	unsigned int bit_per_pixel;
	int pgm_mode;


	if((file = fopen(pathname, "r")) == NULL) {
		FATAL_ERROR("Can't open file");
	}





	if(fread(magic, 1, 3, file) == -1) {
		FATAL_ERROR("Failed : read() magic");
	}

	magic[2] = '\0';

	if(strcmp(magic, "P2") == 0) { /* ASCII Mode */
		VERBOSE("PGM ASCII Mode");
		pgm_mode = PGM_MODE_AASCII;
	}
	else if(strcmp(magic, "P5") == 0) { /* Binary Mode */
		VERBOSE("PGM Binary Mode");
		pgm_mode = PGM_MODE_BINARY;
	}
	else {

		FATAL_ERROR("Magic PGM Format Unreconized");
	}

	image = malloc(sizeof(struct image_t));

	cont = 1;

	while(cont) {

		if(getline(&line, &line_length, file) == -1) {
			free(image);
			FATAL_ERROR("Require dimension");
		}

		if(line[0] != '#' && line[0] != '\r' && line[0] != '\n')
			cont = 0;
		else {
			free(line);
			line = NULL;
		}

	}

	/* read dimension */

	if((str = _next_token(line)) == NULL) {
		free(image);
		FATAL_ERROR("Require width");
	}

	previous_size = strlen(str);

	image->width = atoi(str);

	free(str);

	if((str = _next_token(line+previous_size)) == NULL) {
		free(image);
		FATAL_ERROR("Require height");
	}

	image->height = atoi(str);

	free(str);

	free(line);
	line = NULL;

	printf("Image dimension : %dx%d\n", image->width , image->height);

	/* read bit per pixel */

	if(getline(&line, &line_length, file) == -1) {
		free(image);
		FATAL_ERROR("Require gray scale");
	}

	bit_per_pixel = atoi(line);

	if(bit_per_pixel > pow(2, sizeof(COLOR_TYPE)*8)) {
		FATAL_ERROR("Not enought bit per pixel");
	}

	free(line);
	line = NULL;

	/* Read pixels */

	image->pixels = malloc(sizeof(COLOR_TYPE)*image->height*image->width);

	if(pgm_mode == PGM_MODE_BINARY) {
		fread(image->pixels, image->height*image->width, sizeof(COLOR_TYPE), file);
	}
	else {
		FATAL_ERROR("Unimplemented PGM_MODE_ASCII");
	}

	return image;
}

