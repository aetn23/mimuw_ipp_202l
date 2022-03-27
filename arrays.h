#ifndef _ARRAYS_
#define _ARRAYS_

#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>

//There is no need to reallocate this array, since its size is constant after
//the data has been parsed.
typedef struct BoolArray {
	bool *array;
	size_t size;
	size_t allocated_size;
} BoolArray;

typedef struct NumbersArray {
	size_t *array;
	size_t size;
	size_t allocated_size;
} NumbersArray;


void init_numbers_array(NumbersArray *num_array, size_t alloc_size);
void push_back_number(NumbersArray *num_array, size_t number);

void init_bool_array(BoolArray *bool_array, size_t size);

void push_back_bool(BoolArray *num_array, size_t value);

size_t array_product(const NumbersArray *array, bool *overflow, size_t begin, size_t end);

void printf_array(NumbersArray *array);

void calculate_partial_sums (NumbersArray *array, NumbersArray *result);
#endif //_ARRAYS_