#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <errno.h>
#include <ctype.h>

#include "parse.h"
#include "memory_managment.h"
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
			if (isspace(character)) {
				str_insert(&number_as_string, '\0', number_as_string.size);

				size_t number = str_to_size_t(&number_as_string);
				//In this task numbers are >0
				if (errno == ERANGE || number == 0) {
					handle_wrong_input(line_number);

					free_string(&number_as_string);

					return false;
				}
				push_back_number(numbers, number);

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
	numbers.array = malloc_wrapper(sizeof(size_t) * START_ARRAY_SIZE);
	numbers.allocated_size = START_ARRAY_SIZE;

	if (!parse_first_3_lines_helper(&numbers, line, line_number)) {
		free_numbers_array(&numbers);
		return false;
	}

	if (labyrinth->dimensions == NULL) {
		labyrinth->dimensions = numbers.array;
		labyrinth->dimensions_size = numbers.array_size;

		//labyrinth->dimensions = realloc_wrapper(labyrinth->dimensions, sizeof(size_t) * labyrinth->dimensions_size);

		labyrinth->dimensionality = 1;
		for(size_t i = 0; i < numbers.array_size; i++)
			labyrinth->dimensionality *= numbers.array[i];
	} else if (numbers.array_size != labyrinth->dimensions_size) {
		free_numbers_array(&numbers);
		handle_wrong_input(line_number);

		return false;
	} else if (labyrinth->start == 0) {
		//labyrinth->start.coordinates = numbers.array;
		//labyrinth->start.coordinates = realloc_wrapper(labyrinth->start.coordinates,
		 //                                              sizeof(size_t) * labyrinth->dimensions_size);
		 free(numbers.array);
	} else if (labyrinth->finish == 0) {
		//labyrinth->finish.coordinates = numbers.array;
		//labyrinth->finish.coordinates = realloc_wrapper(labyrinth->finish.coordinates,
		 //                                               sizeof(size_t) * labyrinth->dimensions_size);
		 free(numbers.array);
	}

	//for(size_t i = 0; i < numbers.array_size; i ++) printf("%zu\n", numbers.array[i]);

	//free_numbers_array(&numbers);
	return true;
}

bool parse_fourth_line_helper(String *result_hexal_variant,
                              NumbersArray *result_R_variant, Line *line,
                              size_t line_number) {
	size_t i = 0;
	char character;

	for (; i < line->size; i++) {
		character = line->content[i];
		if (isspace(character))
			continue;
		break;
	}

	if (line->size == i) {
		handle_wrong_input(line_number);
		return false;
	}

	if (character == 'R') {
		line->content[i] = '\t';
		result_R_variant->array = malloc_wrapper(sizeof(size_t) * START_ARRAY_SIZE);

		if (parse_first_3_lines_helper(result_R_variant, line, line_number)) {
			if (result_R_variant->array[2] == 0 || result_R_variant->array_size != 5) {
				handle_wrong_input(line_number);

				return false;
			} else {
				return true;
			}
		}
	} else if (character == '0') {
		if (!(line->size - 1 > i && tolower(line->content[++i]) == 'x')) {
			handle_wrong_input(line_number);
			return false;
		}

		++i;
		character = line->content[i];
		//Skip the last character, which is blank
		for (; i < line->size - 1; i++) {
			if(isxdigit(character)) {
				str_insert(result_hexal_variant, character, result_hexal_variant->size);
				continue;
			}

			handle_wrong_input(line_number);
			return false;
		}

	} else {
		handle_wrong_input(line_number);
		return false;
	}

	return true;
}

bool parse_fourth_line(Labyrinth *labyrinth, Line *line, size_t line_number) {
	String result_hexal_variant;
	init_string(&result_hexal_variant);
	NumbersArray result_R_variant;
	init_numbers_array(&result_R_variant);

	if (!parse_fourth_line_helper(&result_hexal_variant, &result_R_variant, line,
	                             line_number)) {
		free_string(&result_hexal_variant);
		free_numbers_array(&result_R_variant);

		return false;
	}

	if (result_hexal_variant.content == NULL) {
		labyrinth->is_hexal_version = false;
		labyrinth->walls_R_version.array = result_R_variant.array;
		labyrinth->walls_R_version.array = realloc_wrapper(
						labyrinth->walls_R_version.array, result_R_variant.array_size);
		labyrinth->walls_R_version.array_size = result_R_variant.array_size;
		labyrinth->walls_R_version.allocated_size = result_R_variant.array_size;
	} else {
		labyrinth->is_hexal_version = true;
		labyrinth->walls_hexal_version = hexal_to_binary(&result_hexal_variant);

		free_numbers_array(&result_R_variant);
	}

	free_string(&result_hexal_variant);

	return true;
}

bool parse(Labyrinth *labyrinth) {
	init_labyrinth(labyrinth);
	Line line;
	init_line(&line);
	size_t lines_count = 1;
	bool success = true;
	
	while (true) {
		line = read_line();

		if (!line.state && lines_count == MAX_NUM_LINES + 1) {
			break;
		} else if ((lines_count > MAX_NUM_LINES) || (!line.state && lines_count <= MAX_NUM_LINES)) {
			handle_wrong_input(lines_count);
			success = false;
		}

		//parse_first_3_lines function works on assumption that line ends with char
		//that returns true on isspace() call. This assumption allows that function
		//to be more readable.
		insert(line.content, '\t', line.size - 1);

		if (lines_count <= 3) {
			if (!parse_first_3_lines(labyrinth, &line, lines_count)) {
				success = false;
				break;
			}
		} else {
			if (!parse_fourth_line(labyrinth, &line, lines_count)) {
				success = false;
				break;
			}
		}

		lines_count++;

		free(line.content);
	}

	free(line.content);

	return success;
}