#include <string.h>

#include "labyrinth.h"
#include "memory_managment.h"
#include "queue.h"


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

//todo check if neighbour is a wall
void get_neighbours(size_t block, const Labyrinth *labyrinth, NumFIFO *result) {
	bool overflow = false;
	size_t neighbour_distance = 0;
	size_t i = 0;

	while(neighbour_distance != 1) {
		 neighbour_distance = array_product(&labyrinth->dimensions,
																							&overflow, i + 1,
																							labyrinth->dimensions.size);

		if (block >= neighbour_distance)
			enqueue(result, block - neighbour_distance);
		if (block + neighbour_distance < labyrinth->block_count)
			enqueue(result, block + neighbour_distance);


		//printf("%zu\n", neighbour_distance);
		i++;
	}
}

//todo think if emplace calculation is better and think of speeding up array_prodcut by
//calculating it in array
bool is_wall(size_t block, Labyrinth *labyrinth, NumbersArray *helper_array) {
	if (labyrinth->is_hexal_version) {
		number_rep_to_array_rep(block, labyrinth, helper_array);
		//printf_array(helper_array);
		bool overflow = false;
		size_t position = 0;

		for (size_t i = 0; i < helper_array->size; i++) {
			position += (helper_array->array[i] - 1) * array_product(&labyrinth->dimensions, &overflow, 0, i);
		}

		return labyrinth->walls_hexal_version.content[position] == '1';
	}
	return false;
}

//todo get length
size_t get_result (Labyrinth *labyrinth) {
	NumFIFO queue;
	init_fifo(&queue);
	queue.array.array = malloc_wrapper(sizeof(size_t) * START_ARRAY_SIZE);
	queue.array.allocated_size = START_ARRAY_SIZE;
	bool queue_end = false;

	NumbersArray helper_array;
	init_numbers_array(&helper_array);
	helper_array.array = malloc_wrapper(sizeof(size_t) * labyrinth->dimensions.size);
	helper_array.allocated_size = labyrinth->dimensions.size;
	helper_array.size = labyrinth->dimensions.size;

	BST *visited;
	visited = NULL;

	size_t block = labyrinth->start;

	//debug
	NumbersArray debug;
	debug.array = malloc_wrapper(sizeof(size_t)*labyrinth->dimensions.size);
	debug.size = labyrinth->dimensions.size;
	debug.allocated_size = labyrinth->dimensions.size;


	insert_bst(&visited, block);
	get_neighbours(block, labyrinth, &queue);

	while(!is_empty_queue(&queue)) {
		if (block == labyrinth->finish) {
			number_rep_to_array_rep(block, labyrinth, &debug);
			printf("Znalezione: %zu\n", block);
			printf_array(&debug);
			break;
		}

		insert_bst(&visited, block);

		do {
			block = dequeue(&queue, &queue_end);
			if (queue_end)
				break;
		} while(is_wall(block, labyrinth, &helper_array) || contains_bst(visited, block));
		get_neighbours(block, labyrinth, &queue);

	}

	free_queue(&queue);
	free_numbers_array(&helper_array);
	free_tree(visited);
	free_numbers_array(&debug);
	return 0;
}