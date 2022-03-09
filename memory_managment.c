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