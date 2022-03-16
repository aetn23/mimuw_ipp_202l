#ifndef _TYPES_H
#define _TYPES_H

#include <stddef.h>
#include <stdbool.h>

//todo think if it is good enough

typedef size_t dimension_t;
typedef size_t coordinate_t;

//There is no need to reallocate this array, since its size is constant after
//the data has been parsed.
typedef struct BoolArray {
	bool *array;
	size_t size;
} BoolArray;

typedef struct NumbersArray {
	size_t *array;
	size_t size;
	size_t allocated_size;
} NumbersArray;

typedef struct Block {
	coordinate_t *coordinates;
} Block;

/*
typedef struct Labyrinth {
	dimension_t *dimensions;
	size_t dimensions_size;
	Block start, finish;
	Block *walls;
} Labyrinth;
*/

typedef struct String {
	char *content;
	size_t size;
	size_t allocated_size;
} String;

typedef struct Labyrinth {
	dimension_t *dimensions;
	size_t dimensions_size, block_count;
	size_t start, finish;
	union {
		NumbersArray walls_R_version;
		String walls_hexal_version;
	};
	bool is_hexal_version;

} Labyrinth;

typedef struct Line {
	char *content;
	size_t size;
	bool state;
} Line;

//FIFO can be implemented using linked list, which is memory effective, but
//has insertion time complexity of O(n) which is huge drawback, since in this
//task insertion to queue will be used much. Also linked list do not have
//caching benefits of array's.
//To mitigate memory effectiveness of array FIFO I will reallocate it every x
//elements.
typedef struct NumFIFO {
	size_t *array;
	size_t first_pos, allocated_size, size;
} NumFIFO;

void init_fifo(NumFIFO *fifo);
void enqueue(NumFIFO *fifo, size_t value);
size_t dequeue(NumFIFO *fifo, bool *end);

void init_labyrinth (Labyrinth *labyrinth);
void init_block (Block *block);
void init_numbers_array (NumbersArray *num_array);
void push_back_number(NumbersArray *num_array, size_t number);

void init_bool_array(BoolArray *bool_array, size_t size);

void init_line(Line *line);

void init_string(String *line);

void insert(char *string, char to_insert, size_t location);

void str_insert(String *str, char to_insert, size_t location);

void clear_str(String *str);

String hexal_to_binary(String *str);

size_t str_to_size_t(String *str);

size_t count_array_product(NumbersArray *array, bool *overflow);



#endif //_TYPES_H