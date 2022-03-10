#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <errno.h>

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

bool parse_first_3_lines_helper(NumbersArray *numbers, Line *line,
																size_t line_number) {
	bool is_previous_blank = true;
	size_t i = 0;
	String number_as_string;
	init_string(&number_as_string);

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

				free_string(&number_as_string);

				return false;
			}
		} else {
			//printf("petla\n");
			if (isspace(character)) {
				str_insert(&number_as_string, '\0', number_as_string.size);

				size_t number = str_to_size_t(&number_as_string);
				//In this task number are >0
				if (errno == ERANGE || number == 0) {
					handle_wrong_input(line_number);

					free_string(&number_as_string);

					return false;
				}

				numbers->array[numbers->array_size] = number;
				numbers->array_size++;

				clear_str(&number_as_string);

				is_previous_blank = true;
			} else if (isdigit(character)) {
				str_insert(&number_as_string, character, number_as_string.size);
			} else {
				handle_wrong_input(line_number);

				free_string(&number_as_string);

				return false;
			}
		}
	}

	free_string(&number_as_string);

	return true;
}

bool parse_first_3_lines(Labyrinth *labyrinth, Line *line, size_t line_number) {
	NumbersArray numbers;
	init_numbers_array(&numbers);

	if(!parse_first_3_lines_helper(&numbers, line, line_number)) {
		free_numbers_array(&numbers);
		return false;
	}

	if (labyrinth->dimensions == NULL) {
		labyrinth->dimensions = numbers.array;
		labyrinth->dimensions_size = numbers.array_size;

		labyrinth->dimensions = realloc_wrapper(labyrinth->dimensions, sizeof(size_t) * labyrinth->dimensions_size);
	} else if (numbers.array_size != labyrinth->dimensions_size) {
		free_numbers_array(&numbers);
		handle_wrong_input(line_number);

		return false;
	} else if (labyrinth->start.coordinates == NULL) {
		labyrinth->start.coordinates = numbers.array;
		labyrinth->start.coordinates = realloc_wrapper(labyrinth->start.coordinates, sizeof(size_t) * labyrinth->dimensions_size);
	} else if (labyrinth->finish.coordinates == NULL) {
		labyrinth->finish.coordinates = numbers.array;
		labyrinth->finish.coordinates = realloc_wrapper(labyrinth->finish.coordinates, sizeof(size_t) * labyrinth->dimensions_size);
	}

	//for(size_t i = 0; i < numbers.array_size; i ++) printf("%zu\n", numbers.array[i]);

	//free_numbers_array(&numbers);
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
		} else if ((lines_count > MAX_NUM_LINES) || (!line.state && lines_count <= MAX_NUM_LINES)) {
			handle_wrong_input(lines_count);
			break;
		}

		//parse_first_3_lines function works on assumption that line ends with char
		//that returns true on isspace() call. This assumption allows that function
		//to be more readable.
		insert(line.content, '\t', line.size - 1);

		lines_count++;
		if (lines_count <= 3)
			if (!parse_first_3_lines(&labyrinth, &line, lines_count))
				break;
		//todo the other case

		free(line.content);
	}
	//printf("%zu\n", (size_t)-1);
	free_labyrinth(&labyrinth);
	free(line.content);

	return labyrinth;
}