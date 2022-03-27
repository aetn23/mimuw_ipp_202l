#include "memory_managment.h"
#include "error_handling.h"


void check_alloc(void *pointer) {
	if (pointer == NULL)
		handle_alloc_failure();
}

void *malloc_wrapper(size_t size) {
	void *result = malloc(size);
	check_alloc(result);

	return result;
}

void *calloc_wraper(size_t num, size_t size) {
	void *result = calloc(num, size);
	check_alloc(result);

	return result;
}

void *realloc_wrapper(void *ptr, size_t size) {
	ptr = realloc(ptr, size);
	check_alloc(ptr);

	return ptr;
}

void free_numbers_array(NumbersArray *array) {
	if (array->array != NULL)
		free(array->array);
}

void free_bool_array(BoolArray *array) {
	if (array->array != NULL)
		free(array->array);
}

void free_string(String *str) {
	if (str->content != NULL)
		free(str->content);
}

void free_labyrinth(Labyrinth *labyrinth) {
	if (labyrinth->walls.array != NULL)
		free_bool_array(&labyrinth->walls);
	if (labyrinth->dimensions.array != NULL)
		free_numbers_array(&labyrinth->dimensions);
	if (labyrinth->partial_array.array != NULL)
		free_numbers_array(&labyrinth->partial_array);
}

void free_queue(NumFIFO *fifo) {
	free_numbers_array(&fifo->array);
}
