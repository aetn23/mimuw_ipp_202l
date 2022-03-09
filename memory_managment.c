#include "memory_managment.h"
#include "error_handling.h"

void check_alloc(void *pointer) {
	if (pointer == NULL)
		handle_alloc_failure();
}

void *malloc_wrapper(size_t size) {
	void *result = malloc(size*START_ARRAY_SIZE);
	check_alloc(result);

	return result;
}
