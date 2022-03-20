//getline() requires this to be defined.
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <errno.h>
#include <ctype.h>

#include "parse.h"
#include "my_string.h"
#include "arrays.h"
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

//for some godless reasons in this task coordinates to start block are given
//incorrectly ie counting from right down, which is different from the rest of
//the task.
void fix_order(NumbersArray *array) {
	for (size_t i = 0; i < array->size; i++) {
		size_t tmp = array->array[i];
		array->array[i] = array->array[array->size - i - 1];
		array->array[array->size - i - 1] = tmp;
	}
}

bool parse_first_3_lines_helper(NumbersArray *numbers, Line *line,
                                size_t line_number) {
	bool is_previous_blank = true;
	size_t i = 0;
	String number_as_string;
	init_string(&number_as_string);

	for (; i < line->size; i++) {
		char character = line->content[i];

		if (!(isspace(character) || isdigit(character))) {
			handle_wrong_input(line_number);

			free_string(&number_as_string);

			return false;
		}

		if (is_previous_blank) {
			if (isspace(character)) {
				continue;
			} else if (isdigit(character)) {
				is_previous_blank = false;

				insert_str(&number_as_string, character, 0);
			}
		} else {
			if (isspace(character)) {
				insert_str(&number_as_string, '\0', number_as_string.size);

				size_t number = str_to_size_t(&number_as_string);
				if (errno == ERANGE || number == 0) {
					handle_wrong_input(line_number);

					free_string(&number_as_string);

					return false;
				}
				push_back_number(numbers, number);

				clear_str(&number_as_string);

				is_previous_blank = true;
			} else if (isdigit(character)) {
				insert_str(&number_as_string, character, number_as_string.size);
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

	if (line_number == 1) {
		bool overflow = false;
		labyrinth->block_count = array_product(&numbers,
		                                       &overflow, 0, numbers.size);
		if (overflow) {
			free_numbers_array(&numbers);
			handle_wrong_input(line_number);

			return false;
		}

		labyrinth->dimensions = numbers;

		//labyrinth->dimensions = realloc_wrapper(labyrinth->dimensions,
		//																				sizeof(size_t) * labyrinth->dimensions_size);
	} else if (numbers.size != labyrinth->dimensions.size) {
		free_numbers_array(&numbers);
		handle_wrong_input(line_number);

		return false;
	} else if (line_number == 2) {
		fix_order(&numbers);
		/*
		size_t arra_rep_to_num = array_rep_to_number_rep(&numbers, labyrinth);
		printf("%zu\n", arra_rep_to_num);
		NumbersArray test;
		init_numbers_array(&test);
		test.array = malloc_wrapper(labyrinth->dimensions.size * 2 * sizeof(size_t));
		test.allocated_size = 2 * labyrinth->dimensions.size;
		test.size = 0;
		//number_rep_to_array_rep(arra_rep_to_num, labyrinth, &test);
		get_neighbours(arra_rep_to_num, labyrinth, &test);
		//printf("%zu\n", test.size);
		printf_array(&test);
		free_numbers_array(&test);
		 */

		labyrinth->start = array_rep_to_number_rep(&numbers, labyrinth);
		free_numbers_array(&numbers);

	} else if (line_number == 3) {
		fix_order(&numbers);

		labyrinth->finish = array_rep_to_number_rep(&numbers, labyrinth);
		free_numbers_array(&numbers);

	}

	//for(size_t i = 0; i < numbers.size; i ++) printf("%zu\n", numbers.array[i]);

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
			if (result_R_variant->array[2] == 0 || result_R_variant->size != 5) {
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
		//Skip the last character, which is blank
		for (; i < line->size - 1; i++) {
			character = line->content[i];
			if (isxdigit(character)) {
				insert_str(result_hexal_variant, character, result_hexal_variant->size);
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
						labyrinth->walls_R_version.array, result_R_variant.size);
		labyrinth->walls_R_version.size = result_R_variant.size;
		labyrinth->walls_R_version.allocated_size = result_R_variant.size;
	} else {
		insert_str(&result_hexal_variant, '\0', result_hexal_variant.size);
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
			break;
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

