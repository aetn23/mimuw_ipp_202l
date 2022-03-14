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



void *realloc_wrapper(void *ptr, size_t size) {
	ptr = realloc(ptr, size);
	check_alloc(ptr);

	return ptr;
}

void free_numbers_array(NumbersArray *array) {
	if (array->array != NULL)
		free(array->array);
}

void free_string(String *str) {
	if (str->content != NULL)
		free(str->content);
}

//todo add freeing of walls
void free_labyrinth(Labyrinth *labyrinth) {
	if (labyrinth->dimensions != NULL)
		free(labyrinth->dimensions);
	if (labyrinth->is_hexal_version && labyrinth->walls_hexal_version.content != NULL)
		free(labyrinth->walls_hexal_version.content);
	else if (!labyrinth->is_hexal_version && labyrinth->walls_R_version.array != NULL)
		free(labyrinth->walls_R_version.array);
}