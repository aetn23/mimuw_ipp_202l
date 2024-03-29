#ifndef _TYPES_H
#define _TYPES_H

#include <stdbool.h>
#include <stddef.h>

#include "arrays.h"
#include "my_string.h"
#include "queue.h"

typedef struct Labyrinth {
  NumbersArray dimensions;
  NumbersArray partial_product;
  NumbersArray walls;
  size_t start, finish;
} Labyrinth;

void init_labyrinth(Labyrinth *labyrinth, size_t alloc_size);

size_t array_rep_to_number_rep(const NumbersArray *array,
                               const Labyrinth *labyrinth);

bool is_wall(size_t block, Labyrinth *labyrinth);

size_t get_result(Labyrinth *labyrinth);

#endif //_TYPES_H