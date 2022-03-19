#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#include "labyrinth.h"
#include "memory_managment.h"


void init_labyrinth(Labyrinth *labyrinth) {
	init_numbers_array(&labyrinth->dimensions);
	labyrinth->start = 0;
	labyrinth->finish = 0;
	labyrinth->is_hexal_version = false;
	labyrinth->walls_hexal_version.content = NULL;
}



//todo describe what is happening
size_t array_rep_to_number_rep (const NumbersArray *array, const Labyrinth *labyrinth) {
	size_t result = 0;
	bool overflow = false;

	for(size_t i = 0; i < array->size; i++)
		result += (array->array[i] - 1) *
						(array_product(&labyrinth->dimensions, &overflow,
													 i + 1,
													 labyrinth->dimensions.size));

	return result;
}

size_t get_alfa(const Labyrinth *labyrinth, size_t previous_alfa, size_t n) {
	bool overflow = false;
	return previous_alfa % array_product(&labyrinth->dimensions,
																			 &overflow, n,
																			 labyrinth->dimensions.size);
}

void number_rep_to_array_rep (const size_t number, const Labyrinth *labyrinth,
															NumbersArray *result) {
	size_t previous_alfa = number;
	bool overflow = false;
	for (size_t i = 0; i < result->size; i++) {
		result->array[i] = get_alfa(labyrinth, previous_alfa, i) / array_product(&labyrinth->dimensions, &overflow, i + 1, labyrinth->dimensions.size) + 1;
	}
}

void get_neighbours(size_t block, const Labyrinth *labyrinth, NumbersArray *result) {
	bool overflow = false;
	size_t neighbour_distance = 0;
	size_t i = 0, j = 0;

	while(neighbour_distance != 1) {
		 neighbour_distance = array_product(&labyrinth->dimensions,
																							&overflow, j + 1,
																							labyrinth->dimensions.size);

		if (block >= neighbour_distance) {
			result->array[i] = block - neighbour_distance;
			result->size++;
			++i;
		}
		if (block + neighbour_distance < labyrinth->block_count) {
			result->array[i] = block + neighbour_distance;
			result->size++;
			i++;
		}

		//printf("%zu\n", neighbour_distance);
		j++;
	}
}
