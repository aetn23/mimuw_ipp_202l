#include "memory_managment.h"
#include "error_handling.h"


void check_alloc(void *pointer) {
	if (pointer == NULL)
		handle_alloc_failure();
}

void *malloc_wrapper(size_t size) {
	void *result = malloc(size);
	check_alloc(result);

	return result;
}

void *realloc_wrapper(void *ptr, size_t size) {
	ptr = realloc(ptr, size);
	check_alloc(ptr);

	return ptr;
}

void free_numbers_array(NumbersArray *array) {
	if (array->array != NULL)
		free(array->array);
}

void free_string(String *str) {
	if (str->content != NULL)
		free(str->content);
}

void free_labyrinth(Labyrinth *labyrinth) {
	free_numbers_array(&labyrinth->dimensions);
	if (labyrinth->is_hexal_version && labyrinth->walls_hexal_version.content != NULL)
		free(labyrinth->walls_hexal_version.content);
	else if (!labyrinth->is_hexal_version && labyrinth->walls_R_version.array != NULL)
		free(labyrinth->walls_R_version.array);
	free_numbers_array(&labyrinth->partial_array);
}

void free_queue(NumFIFO *fifo) {
	free_numbers_array(&fifo->array);
}

void free_tree(BST *node) {

	if (node->left != NULL) {
		free_tree(node->left);
	}
	if (node->right != NULL) {
		free_tree(node->right);
	}
	if (node != NULL)
		free(node);
}