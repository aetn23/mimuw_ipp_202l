#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>

#include "parse.h"
#include "memory_managment.h"
#include "string_manipulation.h"
#include "error_handling.h"



String read_line() {
	String line;
	init_string(&line);

	ssize_t length = getline(&line.content, &line.size, stdin);

	if (length == -1)
		line.state = false;
	else
		line.size = length;

	check_alloc(line.content);

	return line;
}

void parse_first_3_lines (Labyrinth *labyrinth, String *line) {

}

Labyrinth parse() {
	Labyrinth labyrinth;
	init_labyrinth(&labyrinth);
	String line;
	init_string(&line);
	size_t lines_count = 1;

	while (true) {
		line = read_line();
		//printf("state: %zu\n", line.state);
		//printf("cout : %zu\n", lines_count);

		if (!line.state && lines_count == MAX_NUM_LINES + 1) {
			break;
		} else if (lines_count > MAX_NUM_LINES) {
			handle_wrong_input(lines_count);
			break;
		}

		lines_count++;

		//todo parse first three lines the same (more or less). The parse function
		//will know what it is parsing, depending on state of particular fields in
		//labyrinth.
		//has been parsed

		free(line.content);
	}
	//printf("%zu\n", (size_t)-1);
	free(line.content);

}