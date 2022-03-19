#ifndef _BST_
#define _BST_

#include <stddef.h>
#include <stdbool.h>

typedef struct BST BST;

typedef struct BST {
	size_t value;
	BST *left, *right;
} BST;

void insert_bst(BST **root, const size_t value);

BST *create_node (const size_t value);

bool contains_bst(BST *root, const size_t value);
#endif //_BST_