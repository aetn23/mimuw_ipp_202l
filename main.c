#include "containers.h"
#include "parse.h"
#include "memory_managment.h"

int main() {
	Labyrinth labyrinth;
	parse(&labyrinth);
	free_labyrinth(&labyrinth);
	return 0;
}