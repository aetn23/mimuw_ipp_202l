#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>

#include "parse.h"
#include "memory_managment.h"
#include "string_manipulation.h"
#include "error_handling.h"


Line read_line() {
	Line line;
	init_line(&line);

	ssize_t length = getline(&line.content, &line.size, stdin);

	if (length == -1)
		line.state = false;
	else
		line.size = length;

	check_alloc(line.content);

	return line;
}

bool parse_first_3_lines(Labyrinth *labyrinth, Line *line, size_t line_number) {
	//printf("Ja tu \n");
	bool is_previous_blank = true;
	size_t i = 0;
	String number_as_string;
	init_string(&number_as_string);

	NumbersArray numbers;
	init_numbers_array(&numbers);

	for (; i < line->size; i++) {
		//printf("petla\n");
		char character = line->content[i];

		if (is_previous_blank) {
			//printf("bb\n");
			if (isspace(character)) {
				continue;
			} else if (isdigit(character)) {
				is_previous_blank = false;

				str_insert(&number_as_string, character, 0);
			} else {
				handle_wrong_input(line_number);

				free_numbers_array(&numbers);
				free_string(&number_as_string);

				return false;
			}
		} else {
			//printf("petla\n");
			if (isspace(character)) {
				str_insert(&number_as_string, '\0', number_as_string.size);
				//convert to number and add to numberArray
				printf("%s\n", number_as_string.content);
				numbers.array_size++;

				clear_str(&number_as_string);

				is_previous_blank = true;
			} else if (isdigit(character)) {
				str_insert(&number_as_string, character, number_as_string.size);
			} else {
				handle_wrong_input(line_number);

				free_numbers_array(&numbers);
				free_string(&number_as_string);

				return false;
			}
		}
	}

	free_numbers_array(&numbers);
	free_string(&number_as_string);

	return true;
}

Labyrinth parse() {
	Labyrinth labyrinth;
	init_labyrinth(&labyrinth);
	Line line;
	init_line(&line);
	size_t lines_count = 1;

	while (true) {
		line = read_line();
		//printf("state: %zu\n", line.state);
		//printf("cout : %zu\n", lines_count);

		if (!line.state && lines_count == MAX_NUM_LINES + 1) {
			break;
		} else if ((lines_count > MAX_NUM_LINES) || (!line.state && lines_count < MAX_NUM_LINES)) {
			handle_wrong_input(lines_count);
			break;
		}

		//getline() returns string with newline character, but it is not needed.
		insert(line.content, '\t', line.size - 1);

		lines_count++;

		parse_first_3_lines(&labyrinth, &line, lines_count);

		free(line.content);
	}
	//printf("%zu\n", (size_t)-1);
	free(line.content);

}