#include "bst.h"
#include "memory_managment.h"

BST *create_node(const size_t value) {
	BST *node = malloc_wrapper(sizeof(BST));
	node->right = NULL;
	node->left = NULL;
	node->value = value;
	return node;
}

void insert_bst(BST **root, const size_t value) {

	BST *root_cp = *root;

	BST *root_cp_trail = NULL;

	while (root_cp != NULL) {
		root_cp_trail = root_cp;
		if (value > root_cp->value)
			root_cp = root_cp->right;
		else
			root_cp = root_cp->left;
	}

	if (root_cp_trail == NULL)
		*root = create_node(value);
	else if (value > root_cp_trail->value)
		root_cp_trail->right = create_node(value);
	else
		root_cp_trail->left = create_node(value);
}

bool contains_bst(BST *root, const size_t value) {
	BST *root_cp = root;

	while (root_cp != NULL) {
		if (root_cp->value == value)
			return true;

		if (root_cp->value < value)
			root_cp = root_cp->right;
		else
			root_cp = root_cp->left;
	}

	return false;

}
