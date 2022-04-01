#ifndef _MEMORY_MANAGMENT_
#define _MEMORY_MANAGMENT_

#include <stdlib.h>

#include "labyrinth.h"
#include "queue.h"

#define START_ARRAY_SIZE 32
#define REALLOC_MULTIPLIER 2

void check_alloc(void *pointer);

void *malloc_wrapper(size_t size);

void *calloc_wraper(size_t num, size_t size);

void *realloc_wrapper(void *ptr, size_t size);

void free_numbers_array(NumbersArray *array);

void free_string(String *str);

void free_labyrinth(Labyrinth *labyrinth);

void free_queue(NumFIFO *fifo);



#endif //_MEMORY_MANAGMENT_
