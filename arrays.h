#ifndef _ARRAYS_
#define _ARRAYS_

#include <stddef.h>
#include <stdbool.h>

//There is no need to reallocate this array, since its size is constant after
//the data has been parsed.
typedef struct BoolArray {
	bool *array;
	size_t size;
} BoolArray;

typedef struct NumbersArray {
	size_t *array;
	size_t size;
	size_t allocated_size;
} NumbersArray;

void init_numbers_array (NumbersArray *num_array);
void push_back_number(NumbersArray *num_array, const size_t number);

void init_bool_array(BoolArray *bool_array, const size_t size);
size_t array_product(const NumbersArray *array, bool *overflow);


#endif //_ARRAYS_