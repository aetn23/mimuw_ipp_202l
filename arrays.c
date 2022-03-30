#include <stdint.h>

#include "arrays.h"
#include "memory_managment.h"

//todo not needed
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
	if (size != 0) {
		bool_array->array = malloc(size * sizeof(bool));
		bool_array->allocated_size = size;
		bool_array->size = 0;
		check_alloc(bool_array->array);
	} else {
		bool_array->array = NULL;
		bool_array->size = 0;
		bool_array->allocated_size = 0;
	}
}

void push_back_bool(BoolArray *num_array, const size_t value) {
	if (num_array->allocated_size == num_array->size) {
		num_array->array = realloc_wrapper(num_array->array,
		                                   REALLOC_MULTIPLIER * num_array->allocated_size * sizeof(size_t));
		num_array->allocated_size = REALLOC_MULTIPLIER * num_array->allocated_size;
	}

	num_array->array[num_array->size] = value;
	num_array->size++;
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

void init_numbers_array(NumbersArray *num_array, size_t alloc_size) {
	if (alloc_size > 0) {
		num_array->array = malloc_wrapper(alloc_size * sizeof(size_t));
		num_array->size = 0;
		num_array->allocated_size = alloc_size;
	} else {
		num_array->array = NULL;
		num_array->size = 0;
		num_array->allocated_size = 0;
	}
}

void printf_array(NumbersArray *array) {
	for (size_t i = 0; i < array->size; i++) {
		printf("%zu,", array->array[i]);
	}
	printf("\n");
}

void printf_bool_array(BoolArray *array) {
	for (size_t i = 0; i < array->size; i++) {
		printf("%d,", array->array[i]);
	}
	printf("\n");
}

void calculate_partial_products(NumbersArray *array, NumbersArray *result, bool *overflow) {
	push_back_number(result, 1);
	for (size_t i = 1; i < array->size + 1; i++) {
		if (result->array[i-1] > SIZE_MAX && array->array[i-1]) {
			*overflow = true;
			return;
		} else {
		push_back_number(result, result->array[i - 1] * array->array[i - 1]);
		*overflow = false;
		}
	}

}

size_t back_num_array(NumbersArray *array) {
	return array->array[array->size - 1];
}