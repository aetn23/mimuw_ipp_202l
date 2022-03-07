#ifndef _TYPES_H
#define _TYPES_H

#include <stddef.h>

typedef struct Block {
	size_t *coordinates;
} Block;

typedef struct Labyrinth {
	size_t *dimensions;
	Block start, finish;
	Block *walls;
	size_t k;
} Labyrinth;

#endif //_TYPES_H