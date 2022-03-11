#ifndef _TYPES_H
#define _TYPES_H

#include <stddef.h>
#include <stdbool.h>

//todo think if it is good enough

typedef size_t dimension_t;
typedef size_t coordinate_t;

typedef struct NumbersArray {
	size_t *array;
	size_t array_size;
	size_t allocated_size;
} NumbersArray;

typedef struct Block {
	coordinate_t *coordinates;
} Block;

typedef struct Labyrinth {
	dimension_t *dimensions;
	size_t dimensions_size;
	Block start, finish;
	Block *walls;
} Labyrinth;

typedef struct String {
	char *content;
	size_t size;
	size_t allocated_size;
} String;

typedef struct Line {
	char *content;
	size_t size;
	bool state;
} Line;

void init_labyrinth (Labyrinth *labyrinth);
void init_block (Block *block);
void init_numbers_array (NumbersArray *num_array);
void push_back_number(NumbersArray *num_array, size_t number);

void init_line(Line *line);

void init_string(String *line);

void insert(char *string, char to_insert, size_t location);

void str_insert(String *str, char to_insert, size_t location);

void clear_str(String *str);

size_t str_to_size_t(String *str);

#endif //_TYPES_H