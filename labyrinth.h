#ifndef _TYPES_H
#define _TYPES_H

#include <stddef.h>
#include <stdbool.h>

#include "arrays.h"
#include "my_string.h"
#include "queue.h"

typedef struct Labyrinth {
	NumbersArray dimensions;
	size_t block_count;
	size_t start, finish;
	union {
		NumbersArray walls_R_version;
		String walls_hexal_version;
	};
	bool is_hexal_version;

} Labyrinth;

void init_labyrinth (Labyrinth *labyrinth);

size_t array_rep_to_number_rep (const NumbersArray *array, const Labyrinth *labyrinth);

void number_rep_to_array_rep (size_t number, const Labyrinth *labyrinth,
                              NumbersArray *result);

void get_neighbours(size_t block, const Labyrinth *labyrinth, NumFIFO *result);

bool is_wall(size_t block, Labyrinth *labyrinth, NumbersArray *helper_array);

size_t get_result (Labyrinth *labyrinth);

#endif //_TYPES_H