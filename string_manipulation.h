#ifndef _STRING_MANIPULATION_
#define _STRING_MANIPULATION_

#include <stddef.h>
#include <stdbool.h>

typedef struct String {
	char *content;
	size_t size;
	bool state;
} String;

void init_string(String *line);

#endif //_STRING_MANIPULATION_