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

void free_numbers_array(NumbersArray *array) {
	free(array->array);
}

void free_string(String *str) {
	free(str->content);
}

void *realloc_wrapper(void *ptr, size_t size) {
	ptr = realloc(ptr, size);
	check_alloc(ptr);

	return ptr;
}

//todo add freeing of walls
void free_labyrinth(Labyrinth *labyrinth) {
	if (labyrinth->dimensions != NULL)
		free(labyrinth->dimensions);
	if (labyrinth->start.coordinates != NULL)
		free(labyrinth->start.coordinates);
	if (labyrinth->finish.coordinates != NULL)
		free(labyrinth->finish.coordinates);
}