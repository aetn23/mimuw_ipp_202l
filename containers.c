#include "containers.h"
#include "memory_managment.h"
#include <stdio.h>

void init_numbers_array (NumbersArray *num_array) {
	num_array->array = NULL;
	num_array->array_size = 0;
	num_array->allocated_size = 0;
}

void init_block (Block *block) {
	block->coordinates = NULL;
}

void init_labyrinth (Labyrinth *labyrinth) {
	labyrinth->dimensions = NULL;
	labyrinth->dimensions_size = 0;
	init_block(&labyrinth->start);
	init_block(&labyrinth->finish);
	labyrinth->walls = NULL;
}

void push_back_number(NumbersArray *num_array, size_t number) {
	if (num_array->allocated_size == num_array->array_size) {
		num_array->array = realloc_wrapper(num_array->array, REALLOC_MULTIPLIER * num_array->allocated_size * sizeof(size_t));
		num_array->allocated_size = REALLOC_MULTIPLIER * num_array->allocated_size;
	}

	num_array->array[num_array->array_size] = number;
	num_array->array_size++;
	//printf("%zu   %zu\n", num_array->allocated_size, num_array->array_size);
}


void init_string(String *str) {
	str->content = malloc_wrapper(sizeof(char)*START_ARRAY_SIZE);
	check_alloc(str->content);
	str->size = 0;
	str->allocated_size = START_ARRAY_SIZE;
}


void init_line(Line *line) {
	line->content = NULL;
	line->size = 0;
	line->state = true;
}

void insert(char *str, char to_insert, size_t location) {
	str[location] = to_insert;

}
//There is no guarantee that string wil be null terminated after this operation
void str_insert(String *str, char to_insert, size_t location) {
	while (location >= str->allocated_size) {
		str->content = realloc_wrapper(str->content, sizeof(char) * REALLOC_MULTIPLIER * str->allocated_size);
		str->allocated_size = REALLOC_MULTIPLIER * str->allocated_size;
	}

	str->content[location] = to_insert;
	str->size++;
}

void clear_str(String *str) {
	for(size_t i = 0; i < str->size; i++)
		str->content[i] = '\0';
	str->size = 0;
}

size_t str_to_size_t(String *str) {
	char *str_end;

	return strtoull(str->content, &str_end, 10);
}


