#include <stdint.h>

#include "arrays.h"
#include "memory_managment.h"

//There is a possibility of overflow, hence if.
size_t array_product(const NumbersArray *array, bool *overflow, size_t begin, size_t end) {
	size_t result = 1;

	for (size_t i = begin; i < end; i++) {
		if (result >= SIZE_MAX / 2 && array->array[i] != 1) {
			*overflow = true;
			return 0;
		} else {
			result *= array->array[i];
		}
	}

	*overflow = false;
	return result;
}

void init_bool_array(BoolArray *bool_array, const size_t size) {
	bool_array->array = malloc(size * sizeof(bool));
	check_alloc(bool_array->array);
}

void push_back_number(NumbersArray *num_array, const size_t number) {
	if (num_array->allocated_size == num_array->size) {
		num_array->array = realloc_wrapper(num_array->array,
		                                   REALLOC_MULTIPLIER * num_array->allocated_size * sizeof(size_t));
		num_array->allocated_size = REALLOC_MULTIPLIER * num_array->allocated_size;
	}

	num_array->array[num_array->size] = number;
	num_array->size++;
}

void init_numbers_array(NumbersArray *num_array) {
	num_array->array = NULL;
	num_array->size = 0;
	num_array->allocated_size = 0;
}

void printf_array(NumbersArray *array) {
	for(size_t i = 0; i < array->size; i++) {
		printf("%zu,", array->array[i]);
	}
	printf("\n");
}

