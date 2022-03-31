#include <stdio.h>

#include "labyrinth.h"
#include "parse.h"
#include "memory_managment.h"
#include "error_handling.h"

int main() {
	Labyrinth labyrinth;
	init_labyrinth(&labyrinth, START_ARRAY_SIZE);
	bool good_indput = false;//parse(&labyrinth);
/*
	for(size_t i = 0; i < 20; i++)
		printf("%zu: %d\n", i, is_wall(i, &labyrinth));*/

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

	NumbersArray bit_array;
	init_bit_array(&bit_array, START_ARRAY_SIZE);
	toggle_bit(&bit_array, 0);
	toggle_bit(&bit_array, 0);
	toggle_bit(&bit_array, 80);
	toggle_bit(&bit_array, 5);
	toggle_bit(&bit_array, 10);

	printf("%d\n\n", read_bit(&bit_array, 80));
	printf("%d\n\n", read_bit(&bit_array, 5));
	printf("%d\n\n", read_bit(&bit_array, 10));
	printf("%d\n\n", read_bit(&bit_array, 4));
	printf("%d\n\n", read_bit(&bit_array, 0));

	free_numbers_array(&bit_array);

	return 0;
}