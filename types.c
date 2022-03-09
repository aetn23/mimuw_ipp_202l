#include <stdlib.h>

#include "types.h"
#include "memory_managment.h"

void init_block (Block *block) {
	block->coordinates = NULL;
	block->coordinates_size = 0;
}

void init_labyrinth (Labyrinth *labyrinth) {
	labyrinth->dimensions = NULL;
	labyrinth->dimensions_size = 0;
	init_block(&labyrinth->start);
	init_block(&labyrinth->finish);
	labyrinth->walls = NULL;
}
