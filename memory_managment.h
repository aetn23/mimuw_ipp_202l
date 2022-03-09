#ifndef _MEMORY_MANAGMENT_
#define _MEMORY_MANAGMENT_

#include <stdlib.h>


#define REALLOC_MULTIPLIER 2
#define START_ARRAY_SIZE 8


void check_alloc(void *pointer);

void *malloc_wrapper(size_t size);

#endif //_MEMORY_MANAGMENT_