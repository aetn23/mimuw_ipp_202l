#include <stdio.h>

#include "labyrinth.h"
#include "parse.h"
#include "memory_managment.h"

int main() {
	Labyrinth labyrinth;
	bool good_indput = parse(&labyrinth);

	//printf("%s\n", labyrinth.walls_hexal_version.content);

	if(good_indput)
		printf("%zu\n" ,get_result(&labyrinth));

	free_labyrinth(&labyrinth);



	return 0;
}