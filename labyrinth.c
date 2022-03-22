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
size_t array_rep_to_number_rep(const NumbersArray *array, const Labyrinth *labyrinth) {
	size_t result = 0;
	bool overflow = false;

	for (size_t i = 0; i < array->size; i++)
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

void number_rep_to_array_rep(const size_t number, const Labyrinth *labyrinth,
                             NumbersArray *result) {
	size_t previous_alfa = number;
	bool overflow = false;
	for (size_t i = 0; i < result->size; i++) {
		result->array[i] = get_alfa(labyrinth, previous_alfa, i) /
		                   array_product(&labyrinth->dimensions, &overflow, i + 1, labyrinth->dimensions.size) + 1;
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
			position += (helper_array->array[i] - 1) * labyrinth->partial_array.array[i];
		}
		if (position >= labyrinth->walls_hexal_version.size)
			return false;

		return labyrinth->walls_hexal_version.content[position] == '1';
	}
	return false;
}



void get_new_neighbours(size_t block, Labyrinth *labyrinth, NumFIFO *result, BST *visited, NumbersArray *helper_array) {
	size_t i = 0;
	size_t neighbour;


	NumbersArray array_rep;
	init_numbers_array(&array_rep);
	array_rep.array = malloc_wrapper(sizeof(size_t) * labyrinth->dimensions.size);
	array_rep.size = labyrinth->dimensions.size;
	array_rep.allocated_size = labyrinth->dimensions.size;

	//printf("Block : ");
	number_rep_to_array_rep(block, labyrinth, &array_rep);
	//printf_array(&array_rep);
	for (; i < array_rep.size; i++) {
		if (array_rep.array[i] - 1 > 0) {
			array_rep.array[i] = array_rep.array[i] - 1;

			neighbour = array_rep_to_number_rep(&array_rep, labyrinth);
			if(!contains_bst(visited, neighbour) && !is_wall(neighbour, labyrinth, helper_array)) {
				enqueue(result, neighbour);
				//printf_array(&array_rep);
			}

			array_rep.array[i] = array_rep.array[i] + 1;
		}
		if (array_rep.array[i] + 1 <= labyrinth->dimensions.array[i]) {
			array_rep.array[i] = array_rep.array[i] + 1;
			neighbour = array_rep_to_number_rep(&array_rep, labyrinth);

			if(!contains_bst(visited, neighbour) && !is_wall(neighbour, labyrinth, helper_array)) {
				enqueue(result, neighbour);
				//printf_array(&array_rep);
			}
			array_rep.array[i] = array_rep.array[i] - 1;
		}
	}
	//printf("\n\n");
	free_numbers_array(&array_rep);
}


//todo if edge case
size_t get_result(Labyrinth *labyrinth) {
	size_t length = 1;
	bool found = false;

	NumFIFO queue_0;
	init_fifo(&queue_0);
	queue_0.array.array = malloc_wrapper(sizeof(size_t) * START_ARRAY_SIZE);
	queue_0.array.allocated_size = START_ARRAY_SIZE;
	queue_0.array.size = 0;

	NumFIFO queue_1;
	init_fifo(&queue_1);
	queue_1.array.array = malloc_wrapper(sizeof(size_t) * START_ARRAY_SIZE);
	queue_1.array.allocated_size = START_ARRAY_SIZE;
	queue_1.array.size = 0;

	NumFIFO *active_queue = &queue_0;
	NumFIFO *non_active_queue = &queue_1;

	//printf("wpisuje: %zu, %zu, %zu\n", active_queue->array.allocated_size, active_queue->array.size, active_queue->first_pos);
	//printf("wpisuje: %zu, %zu, %zu\n", non_active_queue->array.allocated_size, non_active_queue->array.size, non_active_queue->first_pos);


	bool queue_0_active = true;
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
	debug.array = malloc_wrapper(sizeof(size_t) * labyrinth->dimensions.size);
	debug.size = labyrinth->dimensions.size;
	debug.allocated_size = labyrinth->dimensions.size;


	insert_bst(&visited, block);
	get_new_neighbours(block, labyrinth, active_queue, visited, &helper_array);
	while (!(is_empty_queue(&queue_0) && is_empty_queue(&queue_1))) {
		//printf("len: %zu\n ", length);
		block = dequeue(active_queue, &queue_end);
		if (queue_end) {
			active_queue = queue_0_active ? &queue_1 : &queue_0;
			non_active_queue = queue_0_active ? &queue_0 : &queue_1;
			queue_0_active = !queue_0_active;
			length++;
			continue;
		}

		if (contains_bst(visited, block)) {
			continue;
		}

		if(block == labyrinth->finish) {
			found = true;
			break;
		}

		insert_bst(&visited, block);
		get_new_neighbours(block, labyrinth, non_active_queue, visited, &helper_array);
	}

	free_queue(&queue_0);
	free_queue(&queue_1);
	free_numbers_array(&helper_array);
	free_tree(visited);
	free_numbers_array(&debug);
	if (found)
		return length;
	else
		return 0;
}