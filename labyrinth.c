#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#include "labyrinth.h"
#include "memory_managment.h"


void init_labyrinth(Labyrinth *labyrinth) {
	labyrinth->dimensions = NULL;
	labyrinth->dimensions_size = 0;
	labyrinth->start = 0;
	labyrinth->finish = 0;
	labyrinth->is_hexal_version = false;
	labyrinth->walls_hexal_version.content = NULL;
}



