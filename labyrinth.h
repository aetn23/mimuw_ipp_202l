#ifndef _TYPES_H
#define _TYPES_H

#include <stddef.h>
#include <stdbool.h>

#include "arrays.h"
#include "my_string.h"


typedef size_t dimension_t;
typedef size_t coordinate_t;

typedef struct Labyrinth {
	dimension_t *dimensions;
	size_t dimensions_size, block_count;
	size_t start, finish;
	union {
		NumbersArray walls_R_version;
		String walls_hexal_version;
	};
	bool is_hexal_version;

} Labyrinth;

void init_labyrinth (Labyrinth *labyrinth);

#endif //_TYPES_H