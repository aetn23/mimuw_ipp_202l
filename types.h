#ifndef _TYPES_H
#define _TYPES_H

#include <stddef.h>


//todo think if it is good enough

typedef size_t dimension_t;
typedef size_t coordinate_t;

/*
//dimensionality as in "three-dimensional plane", "one hundred-dimensional cube".
typedef struct Dimensions {
	dimension_t *sizes;
	dimension_t dimensionality;
} Dimensions;
*/

typedef struct Block {
	coordinate_t *coordinates;
	size_t coordinates_size;
} Block;

typedef struct Labyrinth {
	dimension_t *dimensions;
	size_t dimensions_size;
	Block start, finish;
	Block *walls;
} Labyrinth;

void init_labyrinth (Labyrinth *labyrinth);

#endif //_TYPES_H