#include <string.h>

#include "labyrinth.h"
#include "memory_managment.h"
#include "queue.h"

//todo implement shrinking of queue after constant has been reached LEASTEST IMPORTANT
void init_labyrinth(Labyrinth *labyrinth, size_t alloc_size) {
	init_numbers_array(&labyrinth->dimensions, 0);
	init_numbers_array(&labyrinth->partial_array, alloc_size);
	init_bool_array(&labyrinth->walls, 0);
	labyrinth->start = 0;
	labyrinth->finish = 0;
	labyrinth->is_hexal_version = false;
}

//todo describe what is happening
size_t array_rep_to_number_rep(const NumbersArray *array, const Labyrinth *labyrinth) {
	size_t result = 0;

	for (size_t i = 0; i < array->size; i++)
		result += (array->array[i] - 1) * labyrinth->partial_array.array[i];

	return result;
}

size_t get_alfa(const Labyrinth *labyrinth, size_t previous_alfa, size_t n) {
	return previous_alfa % labyrinth->partial_array.array[n];
}

void number_rep_to_array_rep(const size_t number, const Labyrinth *labyrinth,
                             NumbersArray *result) {
	size_t previous_alfa = number;
	for (size_t i = result->size - 1;; i--) {
		result->array[i] = (previous_alfa / labyrinth->partial_array.array[i]) + 1;
		previous_alfa = get_alfa(labyrinth, previous_alfa, i);

		if (i == 0)
			break;
	}
}

inline bool is_wall(size_t block, Labyrinth *labyrinth) {
	return labyrinth->walls.array[block];
}

void get_new_neighbours_helper (size_t block, Labyrinth *labyrinth, NumFIFO *result, size_t neighbour, size_t i) {

	size_t a = block / labyrinth->partial_array.array[i + 1];
	size_t b = neighbour / labyrinth->partial_array.array[i + 1];

	if (neighbour < labyrinth->block_count && !is_wall(neighbour, labyrinth) && a == b) {
		enqueue(result, neighbour);
		labyrinth->walls.array[neighbour] = true;
		//printf(" NEIGHBOUR %zu ", neighbour);
	}
}

void new_get_new_neighbours(size_t block, Labyrinth *labyrinth, NumFIFO *result, NumbersArray *helper_array1) {
	size_t i = 0;
	size_t neighbour;

	//printf("BLOCK %zu: ", block);
	for (; i < labyrinth->partial_array.size - 1; i++) {
		//printf("\n%zu\n", i);
		if (labyrinth->block_count - labyrinth->partial_array.array[i] >=  block ) {
			neighbour = block + labyrinth->partial_array.array[i];
			get_new_neighbours_helper(block, labyrinth, result, neighbour, i);
		}

		if (block >= labyrinth->partial_array.array[i]) {
			neighbour = block - labyrinth->partial_array.array[i];
			get_new_neighbours_helper(block, labyrinth, result, neighbour, i);
		}
	}
	//printf("\n");
}

//todo describe what is happening
size_t get_result(Labyrinth *labyrinth) {
	size_t length = 1;
	bool found = false;

	NumFIFO queue_0;
	init_fifo(&queue_0, START_ARRAY_SIZE);

	NumFIFO queue_1;
	init_fifo(&queue_1, START_ARRAY_SIZE);

	NumFIFO *active_queue = &queue_0;
	NumFIFO *non_active_queue = &queue_1;

	bool queue_0_active = true;
	bool queue_end = false;

	NumbersArray helper_array1;
	init_numbers_array(&helper_array1, labyrinth->dimensions.size);
	helper_array1.size = labyrinth->dimensions.size;

	size_t block = labyrinth->start;

	//printf("%zu\n\n", labyrinth->walls.size);
	labyrinth->walls.array[block] = true;
	new_get_new_neighbours(block, labyrinth, active_queue, &helper_array1);
	while (!(is_empty_queue(&queue_0) && is_empty_queue(&queue_1))) {

		block = dequeue(active_queue, &queue_end);
		if (queue_end) {
			active_queue = queue_0_active ? &queue_1 : &queue_0;
			non_active_queue = queue_0_active ? &queue_0 : &queue_1;
			queue_0_active = !queue_0_active;
			length++;
			continue;
		}
		//printf("block: %zu\n ", block);

		if (block == labyrinth->finish) {
			found = true;
			break;
		}

		new_get_new_neighbours(block, labyrinth, non_active_queue, &helper_array1);
	}

	free_queue(&queue_0);
	free_queue(&queue_1);
	free_numbers_array(&helper_array1);

	if (found)
		return length;
	else
		return 0;
}

