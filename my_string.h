#ifndef _MY_STRING_
#define _MY_STRING_

#include <stddef.h>
#include <stdbool.h>

#include "arrays.h"

typedef struct String {
	char *content;
	size_t size;
	size_t allocated_size;
} String;


typedef struct Line {
	char *content;
	size_t size;
	size_t allocated_size;
	bool state;
} Line;

void init_line(Line *line, size_t size);

void init_string(String *str, size_t size);

//void insert(char *string, char to_insert, size_t location);

void insert_str(String *str, char to_insert, size_t location);

void insert_line(Line *line, char to_insert, size_t location);

void clear_str(String *str);

void hexal_to_reverse_binary(String *str, BoolArray *result);

size_t str_to_size_t(const String *str);

//void concat_str(String *str, char *to_concat);

#endif //_MY_STRING_