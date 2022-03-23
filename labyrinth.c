#include <string.h>

#include "labyrinth.h"
#include "memory_managment.h"
#include "queue.h"

//todo fix init_container functions MOSTEST IMPORTANT DONE
//todo change hashing to the one in the task descrpiton MOST IMPORTANT DONE
//todo implement rev_partial_product to faster compute vars LEAST IMPORTANT DEPENDS ON POINT UP; MAY NOT BE REQUIRED; NOT REQUIREDC
//todo get rid of bst and hold visited in array LESS IMPORTANT; IF TESTS TURN OUT OK MAY NOT BE NEEDED
//todo implement the R fourth line version IMPORTANT
//todo implement shrinking of queue after constant has been reached LEASTEST IMPORTANT
//todo find out about the last line shenenigans, particulary in reading the hex line

void init_labyrinth(Labyrinth *labyrinth, size_t alloc_size) {
	init_numbers_array(&labyrinth->dimensions, alloc_size);
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
		result += (array->array[i] - 1) * labyrinth->partial_array.array[i];
	/*
	printf("ARRAY: ");
	printf_array(array);
	printf("%zu\n", result);
*/
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
	/*
	printf("NUMBER: ");
	printf("%zu\n", number);
	printf("ARRAY: ");
	printf_array(result);
	printf("\n");
	 */

}

//todo think if emplace calculation is better and think of speeding up array_prodcut by
//calculating it in array
bool is_wall(size_t block, Labyrinth *labyrinth, NumbersArray *helper_array) {


	if (labyrinth->is_hexal_version) {
		if (labyrinth->walls_hexal_version.size >= block) {
			printf("WALL: %zu\n", block);
			return labyrinth->walls_hexal_version.content[block] == '1';
		}
	}
	return false;
}

void get_new_neighbours(size_t block, Labyrinth *labyrinth, NumFIFO *result, BST *visited, NumbersArray *helper_array1,
                        NumbersArray *helper_array2) {
	size_t i = 0;
	size_t neighbour;

	//printf("Block : ");
	number_rep_to_array_rep(block, labyrinth, helper_array1);
	//printf_array(helper_array1);
	for (; i < helper_array1->size; i++) {
		if (helper_array1->array[i] - 1 > 0) {
			helper_array1->array[i] = helper_array1->array[i] - 1;

			neighbour = array_rep_to_number_rep(helper_array1, labyrinth);
			if (!contains_bst(visited, neighbour) && !is_wall(neighbour, labyrinth, helper_array2)) {
				enqueue(result, neighbour);
				insert_bst(&visited, neighbour);
				//printf_array(helper_array1);
			}

			helper_array1->array[i] += 1;
		}
		if (helper_array1->array[i] + 1 <= labyrinth->dimensions.array[i]) {
			helper_array1->array[i] = helper_array1->array[i] + 1;
			neighbour = array_rep_to_number_rep(helper_array1, labyrinth);

			if (!contains_bst(visited, neighbour) && !is_wall(neighbour, labyrinth, helper_array2)) {
				enqueue(result, neighbour);
				insert_bst(&visited, neighbour);
				//printf_array(helper_array1);
			}
			helper_array1->array[i] -= 1;
		}
	}
	//printf("\n\n");
}


//todo if edge case
size_t get_result(Labyrinth *labyrinth) {
	size_t length = 1;
	bool found = false;

	NumFIFO queue_0;
	init_fifo(&queue_0, START_ARRAY_SIZE);

	NumFIFO queue_1;
	init_fifo(&queue_1, START_ARRAY_SIZE);

	NumFIFO *active_queue = &queue_0;
	NumFIFO *non_active_queue = &queue_1;

	//printf("wpisuje: %zu, %zu, %zu\n", active_queue->array.allocated_size, active_queue->array.size, active_queue->first_pos);
	//printf("wpisuje: %zu, %zu, %zu\n", non_active_queue->array.allocated_size, non_active_queue->array.size, non_active_queue->first_pos);


	bool queue_0_active = true;
	bool queue_end = false;

	NumbersArray helper_array1;
	init_numbers_array(&helper_array1, labyrinth->dimensions.size);
	helper_array1.size = labyrinth->dimensions.size;

	NumbersArray helper_array2;
	init_numbers_array(&helper_array2, labyrinth->dimensions.size);
	helper_array2.size = labyrinth->dimensions.size;

	BST *visited;
	visited = NULL;

	size_t block = labyrinth->start;

	//debug
	NumbersArray debug;
	debug.array = malloc_wrapper(sizeof(size_t) * labyrinth->dimensions.size);
	debug.size = labyrinth->dimensions.size;
	debug.allocated_size = labyrinth->dimensions.size;


	insert_bst(&visited, block);
	get_new_neighbours(block, labyrinth, active_queue, visited, &helper_array1, &helper_array2);
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


		if (block == labyrinth->finish) {
			found = true;
			break;
		}

		//insert_bst(&visited, block);
		get_new_neighbours(block, labyrinth, non_active_queue, visited, &helper_array1, &helper_array2);
	}
	/*
	printf("%zu\n", queue_0.array.size);
	printf("%zu\n", queue_1.array.size);
	if (contains_bst(visited, 383970))
	
		printf("Zaweira 383970");*/
	//print_tree(visited);
	//printf("%zu\n", visited);


	free_queue(&queue_0);
	free_queue(&queue_1);
	free_numbers_array(&helper_array1);
	free_numbers_array(&helper_array2);
	free_tree(visited);
	free_numbers_array(&debug);
	if (found)
		return length;
	else
		return 0;
}