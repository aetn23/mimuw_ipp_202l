#include <stdio.h>

#include "labyrinth.h"
#include "parse.h"
#include "memory_managment.h"

int main() {
	Labyrinth labyrinth;
	bool good_indput = parse(&labyrinth);
	/*
	NumbersArray array;
	init_numbers_array(&array);
	array.array = malloc_wrapper(sizeof(size_t) * labyrinth.dimensions.size);
	array.size = labyrinth.dimensions.size;
	//printf("%s\n", labyrinth.walls_hexal_version.content);
	for (size_t i = 0; i < labyrinth.block_count; i++) {
		bool result = is_wall(i, &labyrinth, &array);
		if (result) {
			if (i != 0 ) printf_array(&array);
		}
		//is_wall(i, &labyrinth, &array);
	}
	free_numbers_array(&array);
	 */
	if(good_indput)
		get_result(&labyrinth);

	free_labyrinth(&labyrinth);



	BST *tree = NULL;
	insert_bst(&tree, 4);
	insert_bst(&tree, 5);
	insert_bst(&tree, 6);
	insert_bst(&tree, 7);
	insert_bst(&tree, 1);
	insert_bst(&tree, 123);
	contains_bst(tree, 123);
	free_tree(tree);

	return 0;
}