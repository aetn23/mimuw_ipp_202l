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

void printf_array(NumbersArray *array);

void calculate_partial_products(NumbersArray *array, NumbersArray *result, bool *overflow);

size_t back_num_array(const NumbersArray *array);

bool is_array_greater (const NumbersArray *array1, const NumbersArray *array2);

#endif //_ARRAYS_