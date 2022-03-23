#include <stdio.h>

#include "labyrinth.h"
#include "parse.h"
#include "memory_managment.h"
#include "error_handling.h"

int main() {
	Labyrinth labyrinth;
	bool good_indput = parse(&labyrinth);

	//printf("%s\n", labyrinth.walls_hexal_version.content);

	if(good_indput) {
		if (is_wall(labyrinth.start, &labyrinth))
			handle_wrong_input(2);
		else if (is_wall(labyrinth.finish, &labyrinth))
			handle_wrong_input(3);
		else {		
		size_t result = get_result(&labyrinth);
		if (result == 0)
			printf("NO WAY\n");
		else
			printf("%zu\n" ,result);
		}
	}

	free_labyrinth(&labyrinth);



	return 0;
}