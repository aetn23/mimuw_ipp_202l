//getline() requires this to be defined.
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <errno.h>
#include <ctype.h>
#include <stdint.h>

#include "parse.h"
#include "my_string.h"
#include "arrays.h"
#include "memory_managment.h"
#include "error_handling.h"
#include "common_defines.h"

#define TWO_TO_THRITYTWO 4294967296UL

#define MIN_NUMBER_FIRST_3_LINES 1
#define MIN_NUMBER_FOURTH_LINE 0
#define MAX_NUM_LINES 4

#define ISSPACE_DUMMY '\t'

Line read_line() {
	Line line;
	init_line(&line, 0);
	ssize_t length;

	length = getline(&line.content, &line.allocated_size, stdin);

	if (length == -1) {
		line.state = false;
	} else {
		line.size = length;
		line.state = true;
	}
	//printf("%zu\n", line.size);
	check_alloc(line.content);

	return line;
}

size_t get_first_nonspace_location(const Line *line, size_t i) {
	for (; i < line->size; i++)
		if (!isspace(line->content[i]))
			return i--;
	return i;
}

// Variabales are named after formula in task's description.
void get_walls_r_version(const Labyrinth *labyrinth, const NumbersArray *R_line, NumbersArray *walls) {
	size_t a = R_line->array[0], b = R_line->array[1], m = R_line->array[2],
					r = R_line->array[3], s_0 = R_line->array[4], s_i = s_0;

	NumbersArray w_numbers;
	init_numbers_array(&w_numbers, r);
	size_t i = 0;

	// Count s1, s2, ..., sr acoording to formula in task description.
	for (; i < r; i++) {
		s_i = (a * s_i + b) % m;
		push_back_number(&w_numbers, s_i % back_num_array(&labyrinth->partial_array));
	}

	// Fill walls array with walls.
	for (i = 0; i < w_numbers.size; i++) {
		while (w_numbers.array[i] < back_num_array(&labyrinth->partial_array)) {
			toggle_bit(walls, w_numbers.array[i]);
			//walls->array[w_numbers.array[i]] = WALL;
			if (w_numbers.array[i] > SIZE_MAX - TWO_TO_THRITYTWO)
				break;
			else
				w_numbers.array[i] += TWO_TO_THRITYTWO;
		}
	}
	free_numbers_array(&w_numbers);
}

bool parse_number(NumbersArray *numbers, const Line *line,
                  const size_t min_number_allowed, const size_t max_number_allowed,
                  String *number_as_string, size_t *i) {
	char character;

	for (; *i < line->size; (*i)++) {
		character = line->content[*i];

		if (isspace(character)) {
			insert_str(number_as_string, NULL_CHAR, number_as_string->size);

			size_t number = str_to_size_t(number_as_string);
			push_back_number(numbers, number);

			if (errno == ERANGE || number < min_number_allowed || number > max_number_allowed)
				return false;

			clear_str(number_as_string);

			return true;
		} else if (isxdigit(character)) {
			insert_str(number_as_string, character, number_as_string->size);
		} else {
			return false;
		}
	}
	return true;
}

bool parse_first_3_lines_helper(NumbersArray *numbers, const Line *line,
                                const size_t line_number,
                                const size_t min_number_allowed, const size_t max_number_allowed) {
	size_t i = 0;
	String number_as_string;
	init_string(&number_as_string, START_ARRAY_SIZE);

	for (; i < line->size; i++) {

		i = get_first_nonspace_location(line, i);
		if (i >= line->size)
			break;

		char character = line->content[i];

		if ((!isdigit(character) || !parse_number(numbers, line,
		                                          min_number_allowed, max_number_allowed,
		                                          &number_as_string, &i))) {
			handle_wrong_input(line_number);

			free_string(&number_as_string);

			return false;
		}
	}

	free_string(&number_as_string);

	return true;
}

bool parse_first_3_lines(Labyrinth *labyrinth, const Line *line, const size_t line_number) {
	NumbersArray numbers;
	init_numbers_array(&numbers, START_ARRAY_SIZE);
	bool success = true;

	if (!parse_first_3_lines_helper(&numbers, line, line_number, MIN_NUMBER_FIRST_3_LINES, SIZE_MAX)) {
		free_numbers_array(&numbers);
		return false;
	}

	if (line_number == 1) {
		labyrinth->dimensions = numbers;
		bool overflow = false;

		calculate_partial_products(&labyrinth->dimensions, &labyrinth->partial_array, &overflow);

		if (overflow) {
			handle_wrong_input(0);

			success = false;
		} else if (labyrinth->dimensions.size == 0) {
			handle_wrong_input(line_number);
			success = false;
		}

	} else if (numbers.size != labyrinth->dimensions.size) {
		handle_wrong_input(line_number);
		success = false;
	} else if (line_number == 2) {
		if (!is_array_greater(&labyrinth->dimensions, &numbers)) {
			handle_wrong_input(line_number);
			success = false;
		} else {
			labyrinth->start = array_rep_to_number_rep(&numbers, labyrinth);
		}
	} else if (line_number == 3) {
		if (!is_array_greater(&labyrinth->dimensions, &numbers)) {
			handle_wrong_input(line_number);
			success = false;
		} else {
			labyrinth->finish = array_rep_to_number_rep(&numbers, labyrinth);
		}
	}

	if (line_number != 1)
		free_numbers_array(&numbers);

	return success;
}

bool parse_fourth_line_helper(String *result_hexal_variant,
                              NumbersArray *result_R_variant, const Line *line,
                              const size_t line_number) {
	size_t i = 0;
	char character;

	i = get_first_nonspace_location(line, i);

	if (line->size == i) {
		handle_wrong_input(line_number);
		return false;
	}

	character = line->content[i];

	if (character == 'R') {
		line->content[i] = ISSPACE_DUMMY;
		if (parse_first_3_lines_helper(result_R_variant, line, line_number, MIN_NUMBER_FOURTH_LINE, UINT32_MAX)) {
			bool is_R_line_condition_failed =
							result_R_variant->array[2] == 0 || result_R_variant->size != 5;

			if (is_R_line_condition_failed) {
				//printf("TUTAJ\n\n");
				handle_wrong_input(line_number);

				return false;
			} else {
				return true;
			}
		} else {
			return false;
		}
	} else if (character == '0') {
		if (!(line->size - 1 > i && tolower(line->content[++i]) == 'x')) {
			handle_wrong_input(line_number);
			return false;
		}

		++i;
		for (; i < line->size; i++) {
			character = line->content[i];
			if (isxdigit(character)) {
				insert_str(result_hexal_variant, character, result_hexal_variant->size);
				continue;
			} else if (isspace(character)) {
				if (get_first_nonspace_location(line, i) == line->size)
					break;
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

bool parse_fourth_line(Labyrinth *labyrinth, const Line *line, const size_t line_number) {

	String result_hexal_variant;
	init_string(&result_hexal_variant, START_ARRAY_SIZE);

	NumbersArray result_R_variant;
	init_numbers_array(&result_R_variant, START_ARRAY_SIZE);

	bool success = true;

	if (!parse_fourth_line_helper(&result_hexal_variant, &result_R_variant, line,
	                              line_number))
		success = false;

	init_bit_array(&labyrinth->walls, (back_num_array(&labyrinth->partial_array) / SIZE_T_SIZE_IN_BITS) + 1);

	if (result_hexal_variant.size == 0) {
		get_walls_r_version(labyrinth, &result_R_variant, &labyrinth->walls);
	} else {
		insert_str(&result_hexal_variant, NULL_CHAR, result_hexal_variant.size);
		// In C strings are counted up to null byte.
		--result_hexal_variant.size;

		//printf("%s\n", result_hexal_variant.content);
		//printf("%zu\n", labyrinth->walls.size);
		hexal_to_reverse_binary(&result_hexal_variant, &labyrinth->walls);
		//printf("%zu\n", labyrinth->walls.size);
		if (labyrinth->walls.size  > back_num_array(&labyrinth->partial_array)) {
			handle_wrong_input(line_number);
			success = false;
		}

		labyrinth->walls.size = back_num_array(&labyrinth->partial_array);
	}

	if (success && (is_wall(labyrinth->start, labyrinth))) {
		handle_wrong_input(4);
		success = false;
	} else if (success && (is_wall(labyrinth->finish, labyrinth))) {
		handle_wrong_input(4);
		success = false;
	}

	free_numbers_array(&result_R_variant);
	free_string(&result_hexal_variant);

	return success;
}

bool parse(Labyrinth *labyrinth) {
	Line line;
	size_t lines_count = 1;
	bool success = true;

	while (true) {
		line = read_line();

		if (!line.state && lines_count == MAX_NUM_LINES + 1 && line.size == 0) {
			break;
		} else if ((lines_count > MAX_NUM_LINES) || (!line.state && lines_count <= MAX_NUM_LINES)) {
			handle_wrong_input(lines_count);
			success = false;
			break;
		}

		//The fourth line may not end with \n, but the parsing of that line
		//will be shorter and nicer if they could assume that \n always will be 
		//present. Hence, this insertion.
		if (!isspace(line.content[line.size - 1])) {
			insert_line(&line, ISSPACE_DUMMY, line.size);
			insert_line(&line, NULL_CHAR, line.size);
			line.size--;
		}


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

