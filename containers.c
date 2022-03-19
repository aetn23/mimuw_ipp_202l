#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

#include "containers.h"
#include "memory_managment.h"

void init_numbers_array(NumbersArray *num_array) {
	num_array->array = NULL;
	num_array->size = 0;
	num_array->allocated_size = 0;
}


void init_labyrinth(Labyrinth *labyrinth) {
	labyrinth->dimensions = NULL;
	labyrinth->dimensions_size = 0;
	labyrinth->start = 0;
	labyrinth->finish = 0;
	labyrinth->is_hexal_version = false;
	labyrinth->walls_hexal_version.content = NULL;
}

void push_back_number(NumbersArray *num_array, const size_t number) {
	if (num_array->allocated_size == num_array->size) {
		num_array->array = realloc_wrapper(num_array->array,
		                                   REALLOC_MULTIPLIER * num_array->allocated_size * sizeof(size_t));
		num_array->allocated_size = REALLOC_MULTIPLIER * num_array->allocated_size;
	}

	num_array->array[num_array->size] = number;
	num_array->size++;
}

//todo this is inconsitent
void init_string(String *str) {
	str->content = malloc_wrapper(sizeof(char) * START_ARRAY_SIZE);
	check_alloc(str->content);
	str->size = 0;
	str->allocated_size = START_ARRAY_SIZE;
}

void init_line(Line *line) {
	line->content = NULL;
	line->size = 0;
	line->state = true;
}

//todo think if this function should exist
void insert(char *str, char to_insert, const size_t location) {
	str[location] = to_insert;
}

//There is no guarantee that string wil be null terminated after this operation
void insert_str(String *str, const char to_insert, const size_t location) {
	while (location >= str->allocated_size) {
		str->content = realloc_wrapper(str->content, sizeof(char) * REALLOC_MULTIPLIER * str->allocated_size);
		check_alloc(str->content);
		str->allocated_size = REALLOC_MULTIPLIER * str->allocated_size;
	}

	str->content[location] = to_insert;
	str->size++;
}

void concat_str(String *str, char *to_concat) {
	size_t to_concat_len = strlen(to_concat);
	while (to_concat_len + str->size >= str->allocated_size) {
		str->content = realloc_wrapper(str->content, sizeof(char) * REALLOC_MULTIPLIER * str->allocated_size);
		check_alloc(str->content);
		str->allocated_size = REALLOC_MULTIPLIER * str->allocated_size;
	}
	for (size_t i = 0; i < to_concat_len; i++)
		str->content[i + str->size] = to_concat[i];

	str->size += to_concat_len;
}

void clear_str(String *str) {
	for (size_t i = 0; i < str->size; i++)
		str->content[i] = '\0';
	str->size = 0;
}

size_t str_to_size_t(const String *str) {
	char *str_end;

	return strtoull(str->content, &str_end, 10);
}

void init_bool_array(BoolArray *bool_array, const size_t size) {
	bool_array->array = malloc(size * sizeof(bool));
	check_alloc(bool_array->array);
}

String hexal_to_binary(const String *hexal) {
	String result;
	init_string(&result);
	size_t i = 0;

	for (; i < hexal->size; i++) {
		char character = hexal->content[i];
		switch (tolower(character)) {
			case '0':
				insert_str(&result, '0', result.size);
				break;
			case '1':
				insert_str(&result, '1', result.size);
				break;
			case '2':
				concat_str(&result, "10");
				break;
			case '3':
				concat_str(&result, "11");
				break;
			case '4':
				concat_str(&result, "100");
				break;
			case '5':
				concat_str(&result, "101");
				break;
			case '6':
				concat_str(&result, "110");
				break;
			case '7':
				concat_str(&result, "111");
				break;
			case '8':
				concat_str(&result, "1000");
				break;
			case '9':
				concat_str(&result, "1001");
				break;
			case 'a':
				concat_str(&result, "1010");
				break;
			case 'b':
				concat_str(&result, "1011");
				break;
			case 'c':
				concat_str(&result, "1100");
				break;
			case 'd':
				concat_str(&result, "1101");
				break;
			case 'e':
				concat_str(&result, "1110");
				break;
			case 'f':
				concat_str(&result, "1111");
				break;
			default:
				break;
		}
	}

	return result;
}

//There is a possibility of overflow, hence if.
size_t array_product(const NumbersArray *array, bool *overflow) {
	size_t result = 1;

	for (size_t i = 0; i < array->size; i++) {
		if (result >= SIZE_MAX / 2 && array->array[i] != 1) {
			*overflow = true;
			return 0;
		} else {
			result *= array->array[i];
		}
	}

	*overflow = false;
	return result;
}

void init_fifo(NumFIFO *fifo) {
	init_numbers_array(&fifo->array);
	fifo->first_pos = 0;
}

void enqueue(NumFIFO *fifo, const size_t value) {
	push_back_number(&fifo->array, value);

}

//todo implement shrinking after first_pos > constant
size_t dequeue(NumFIFO *fifo, bool *end) {
	if (fifo->first_pos + 1 == fifo->array.size) {
		*end = true;
		return 0;
	} else {
		return fifo->array.array[fifo->first_pos++];
	}
}

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

		if (root_cp->value > value)
			root_cp = root_cp->right;
		else
			root_cp = root_cp->left;
	}

	return false;

}



