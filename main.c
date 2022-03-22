#include <stdio.h>

#include "labyrinth.h"
#include "parse.h"
#include "memory_managment.h"

int main() {
	Labyrinth labyrinth;
	bool good_indput = parse(&labyrinth);

	printf("%s\n", labyrinth.walls_hexal_version.content);

	if(good_indput)
		printf("%zu\n" ,get_result(&labyrinth));

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