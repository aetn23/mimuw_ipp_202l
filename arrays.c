#include <stdint.h>

#include "arrays.h"
#include "memory_managment.h"

#define SIZE_T_SIZE_IN_BITS (sizeof(size_t) * 8)

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

size_t back_num_array(const NumbersArray *array) {
	return array->array[array->size - 1];
}


// Greater in the sense that every element of first array is greater than correspodnig element in second one. This function assumes the arrays are of equal length.
bool is_array_greater (const NumbersArray *array1, const NumbersArray *array2) {
	for (size_t i = 0; i < array1->size; i++) {
		if (array2->array[i] > array1->array[i])
			return false;
	}
	return true;
}

// Asumption: arguments are correct in the sense that bit_index will always be within
// the bounds of allocated memory. 
void toggle_bit (NumbersArray *bit_array, size_t position) {
	while (bit_array->allocated_size <= position) {
		bit_array->array = realloc_wrapper(bit_array->array,
											REALLOC_MULTIPLIER * bit_array->allocated_size * sizeof(size_t));
		bit_array->allocated_size = REALLOC_MULTIPLIER * bit_array->allocated_size * SIZE_T_SIZE_IN_BITS;
	}

	size_t bit_index = position / SIZE_T_SIZE_IN_BITS;
	size_t bit_position = position % SIZE_T_SIZE_IN_BITS;

	size_t one_at_bit_position = 1 << bit_position;

	bit_array->array[bit_index] |= one_at_bit_position;

	bit_array->size++;
}

bool read_bit (NumbersArray *bit_array, size_t position) {
	size_t bit_index = position / SIZE_T_SIZE_IN_BITS;
	size_t bit_position = position % SIZE_T_SIZE_IN_BITS;

	size_t one_at_bit_position = 1 << bit_position;

	return (bool)(bit_array->array[bit_index] & one_at_bit_position);
}

void init_bit_array(NumbersArray *bit_array, size_t alloc_size) {
	if (alloc_size > 0) {
		bit_array->array = calloc_wraper(alloc_size, sizeof(size_t));
		bit_array->size = 0;
		bit_array->allocated_size = alloc_size * SIZE_T_SIZE_IN_BITS;
	} else {
		bit_array->array = NULL;
		bit_array->size = 0;
		bit_array->allocated_size = 0;
	}
}