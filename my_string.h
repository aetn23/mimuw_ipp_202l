#ifndef _MY_STRING_
#define _MY_STRING_

#include <stddef.h>
#include <stdbool.h>

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

void init_line(Line *line);

void init_string(String *line);

void insert(char *string, const char to_insert, const size_t location);

void insert_str(String *str, const char to_insert, const size_t location);

void insert_line (Line *line, char to_insert, size_t location);

void clear_str(String *str);

String hexal_to_binary(const String *str);

size_t str_to_size_t(const String *str);

void concat_str(String *str, char *to_concat);

#endif //_MY_STRING_