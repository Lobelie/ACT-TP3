#ifndef _IMAGE_READER_H
#define _IMAGE_READER_H

#include <string.h>
#include <ctype.h>
#include <math.h>


#include "header.h"
#include "image.h"

/*
 *	Create image. structure returned is owned by the caller
 */
struct image_t* read_image(const char* pathname);

struct image_t* read_pgm_format(const char* pathname);


#endif
