#ifndef _TYPES_H
#define _TYPES_H

#include <stddef.h>


//todo think if it is good enough

typedef size_t dimension_t;
typedef size_t coordinate_t;

typedef struct NumbersArray {
	size_t *array;
	size_t array_size;
	size_t allocated_size;
} NumbersArray;

typedef struct Block {
	coordinate_t *coordinates;
} Block;

typedef struct Labyrinth {
	dimension_t *dimensions;
	size_t dimensions_size;
	Block start, finish;
	Block *walls;
} Labyrinth;

void init_labyrinth (Labyrinth *labyrinth);
void init_block (Block *block);
void init_numbers_array (NumbersArray *num_array);

#endif //_TYPES_H