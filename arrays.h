#ifndef _ARRAYS_
#define _ARRAYS_

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#define SIZE_T_SIZE_IN_BITS (sizeof(size_t) * 8)

typedef struct NumbersArray {
  size_t *array;
  size_t size;
  size_t allocated_size;
} NumbersArray;

typedef struct BitArray {
  size_t *array;
  size_t size;
  size_t allocated_size;
} BitArray;

void init_numbers_array(NumbersArray *num_array, size_t alloc_size);

void push_back_number(NumbersArray *num_array, size_t number);

void calculate_partial_products(const NumbersArray *array, NumbersArray *result,
                                bool *overflow);

size_t back_num_array(const NumbersArray *array);

bool is_array_greater(const NumbersArray *array1, const NumbersArray *array2);

void init_bit_array(NumbersArray *bit_array, size_t size);

void toggle_bit(NumbersArray *bit_array, size_t position);

bool read_bit(const NumbersArray *bit_array, size_t position);

#endif //_ARRAYS_