#ifndef _STRING_MANIPULATION_
#define _STRING_MANIPULATION_

#include <stddef.h>
#include <stdbool.h>
#include <ctype.h>

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

void init_line(Line *line);

void init_string(String *line);

void insert(char *string, char to_insert, size_t location);

void str_insert(String *str, char to_insert, size_t location);

void clear_str(String *str);



#endif //_STRING_MANIPULATION_