#include <stdlib.h>

#include "types.h"
#include "memory_managment.h"

void init_numbers_array (NumbersArray *num_array) {
	num_array->array = malloc_wrapper(START_ARRAY_SIZE*sizeof(size_t));
	check_alloc(num_array->array);
	num_array->array_size = 0;
	num_array->allocated_size = START_ARRAY_SIZE;
}

void init_block (Block *block) {
	block->coordinates_size = 0;
}

void init_labyrinth (Labyrinth *labyrinth) {
	labyrinth->dimensions = NULL;
	labyrinth->dimensions_size = 0;
	init_block(&labyrinth->start);
	init_block(&labyrinth->finish);
	labyrinth->walls = NULL;
}
