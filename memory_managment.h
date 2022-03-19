#ifndef _MEMORY_MANAGMENT_
#define _MEMORY_MANAGMENT_

#include <stdlib.h>

#include "labyrinth.h"
#include "bst.h"
#include "queue.h"

#define START_ARRAY_SIZE 2
#define REALLOC_MULTIPLIER 2

void check_alloc(void *pointer);

void *malloc_wrapper(size_t size);

void free_numbers_array(NumbersArray *array);

void free_string(String *str);

void *realloc_wrapper(void *ptr, size_t size);

void free_labyrinth(Labyrinth *labyrinth);

void free_queue(NumFIFO *fifo);

//todo rewrite this iteratively
void free_tree(BST *node);


#endif //_MEMORY_MANAGMENT_
