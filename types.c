#include "types.h"
#include "memory_managment.h"
#include <stdio.h>

void init_numbers_array (NumbersArray *num_array) {
	num_array->array = NULL;
	num_array->array_size = 0;
	num_array->allocated_size = 0;
}

void init_block (Block *block) {
	block->coordinates = NULL;
}

void init_labyrinth (Labyrinth *labyrinth) {
	labyrinth->dimensions = NULL;
	labyrinth->dimensions_size = 0;
	init_block(&labyrinth->start);
	init_block(&labyrinth->finish);
	labyrinth->walls = NULL;
}

void push_back_number(NumbersArray *num_array, size_t number) {
	if (num_array->allocated_size == num_array->array_size) {
		num_array->array = realloc_wrapper(num_array->array, REALLOC_MULTIPLIER * num_array->allocated_size * sizeof(size_t));
		num_array->allocated_size = REALLOC_MULTIPLIER * num_array->allocated_size;
	}

	num_array->array[num_array->array_size] = number;
	num_array->array_size++;
	printf("%zu   %zu\n", num_array->allocated_size, num_array->array_size);

}