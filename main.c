#include <stdio.h>

#include "containers.h"
#include "parse.h"
#include "memory_managment.h"

int main() {
	/*
	Labyrinth labyrinth;
	parse(&labyrinth);
	free_labyrinth(&labyrinth);

*/


	BST *tree = NULL;
	insert_bst(&tree, 4);
	insert_bst(&tree, 5);
	insert_bst(&tree, 6);
	insert_bst(&tree, 7);
	insert_bst(&tree, 1);
	insert_bst(&tree, 123);
	contains_bst(tree, 123);
	printf("%zu\n", tree->value);
	free_tree(tree);

	return 0;
}