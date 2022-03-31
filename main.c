#include <stdio.h>

#include "labyrinth.h"
#include "parse.h"
#include "memory_managment.h"
#include "error_handling.h"

int main() {
	Labyrinth labyrinth;
	init_labyrinth(&labyrinth, START_ARRAY_SIZE);
	bool good_indput = parse(&labyrinth);
/*
	for(size_t i = 0; i < 20; i++)
		printf("%zu: %d\n", i, is_wall(i, &labyrinth));
	return 0;*/
	//printf("%s\n", labyrinth.walls_hexal_version.content);
	if (good_indput) {
		if (is_wall(labyrinth.finish, &labyrinth) || is_wall(labyrinth.start, &labyrinth))
			handle_wrong_input(4);
		else if (labyrinth.start == labyrinth.finish) {
			printf("0\n");
		} else {
			size_t result = get_result(&labyrinth);

			if (result == 0)
				printf("NO WAY\n");
			else
				printf("%zu\n", result);
		}
	}
	free_labyrinth(&labyrinth);



	return 0;
}