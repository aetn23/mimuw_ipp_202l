#include <stdio.h>

#include "labyrinth.h"
#include "parse.h"
#include "memory_managment.h"

int main() {
	Labyrinth labyrinth;
	bool good_indput = parse(&labyrinth);

	labyrinth.partial_array.array = malloc_wrapper(labyrinth.dimensions.size * sizeof(size_t));
	labyrinth.partial_array.size = labyrinth.dimensions.size;
	labyrinth.partial_array.allocated_size = labyrinth.dimensions.size;

	calculate_partial_sums(&labyrinth.dimensions, &labyrinth.partial_array);

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