#include <stdint.h>

#include "arrays.h"
#include "memory_management.h"

void init_numbers_array(NumbersArray *num_array, const size_t alloc_size) {
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

void push_back_number(NumbersArray *num_array, const size_t number) {
  if (num_array->allocated_size == num_array->size) {
    num_array->allocated_size *= REALLOC_MULTIPLIER;
    num_array->array = realloc_wrapper(
        num_array->array, num_array->allocated_size * sizeof(size_t));
  }

  num_array->array[num_array->size] = number;
  num_array->size++;
}

// First index of result is 1, since empty product is 1.
void calculate_partial_products(const NumbersArray *array, NumbersArray *result,
                                bool *overflow) {
  push_back_number(result, 1);
  for (size_t i = 1; i < array->size + 1; i++) {
    bool is_next_multiplication_overflowing =
        result->array[i - 1] > SIZE_MAX / array->array[i - 1] &&
        array->array[i - 1];
    if (is_next_multiplication_overflowing) {
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

// Greater in the sense that every element of first array is greater than
// corresponding element in second one. This function assumes the arrays are of
// equal length.
bool is_array_greater(const NumbersArray *array1, const NumbersArray *array2) {
  for (size_t i = 0; i < array1->size; i++) {
    if (array2->array[i] > array1->array[i])
      return false;
  }
  return true;
}

void init_bit_array(NumbersArray *bit_array, const size_t alloc_size) {
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

void toggle_bit(NumbersArray *bit_array, const size_t position) {
  while (bit_array->allocated_size <= position) {
    bit_array->array = realloc_wrapper(
        bit_array->array,
        REALLOC_MULTIPLIER * bit_array->allocated_size * sizeof(size_t));
    bit_array->allocated_size =
        REALLOC_MULTIPLIER * bit_array->allocated_size * SIZE_T_SIZE_IN_BITS;
  }

  size_t bit_index = position / SIZE_T_SIZE_IN_BITS;
  size_t bit_position = position % SIZE_T_SIZE_IN_BITS;

  size_t one_at_bit_position = (size_t)1 << bit_position;

  bit_array->array[bit_index] |= one_at_bit_position;

  bit_array->size++;
}

bool read_bit(const NumbersArray *bit_array, const size_t position) {
  size_t bit_index = position / SIZE_T_SIZE_IN_BITS;
  size_t bit_position = position % SIZE_T_SIZE_IN_BITS;

  size_t one_at_bit_position = (size_t)1 << bit_position;

  return ((bit_array->array[bit_index] & one_at_bit_position) != 0);
}