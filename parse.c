#define _POSIX_C_SOURCE 200809L

#include <stdio.h>

#include "parse.h"
#include "memory_managment.h"

typedef struct Line {
	char *content;
	size_t size;
} Line;

Line read_line() {
	Line line;

	line.size = getline(&line.content, &line.size, stdin);
	check_alloc(line.content);

	return line;
}

Labyrinth parse() {
	printf("%s\n", read_line().content);
}