#ifndef _MEMORY_MANAGMENT_
#define _MEMORY_MANAGMENT_

#include <stdlib.h>

#include "types.h"
#include "string_manipulation.h"

#define REALLOC_MULTIPLIER 2
#define START_ARRAY_SIZE 8


void check_alloc(void *pointer);

void *malloc_wrapper(size_t size);

void free_numbers_array(NumbersArray *array);

void free_string(String *str);

void *realloc_wrapper(void *ptr, size_t size);

void free_labyrinth(Labyrinth *labyrinth);

#endif //_MEMORY_MANAGMENT_
