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
	ssize_t length;
	length = getline(&line.content, &line.allocated_size, stdin);

	if (length == -1) {
		line.state = false;
	}
	else {
		line.size = length;
		line.state = true;
	}
	//printf("%zu\n", line.size);
	check_alloc(line.content);

	return line;
}

bool parse_first_3_lines_helper(Labyrinth *labyrinth, NumbersArray *numbers, Line *line,
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
				push_back_number(numbers, number);

				if (errno == ERANGE || number == 0 
				) {
					handle_wrong_input(line_number);

					free_string(&number_as_string);

					return false;
				}


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
	init_numbers_array(&numbers, START_ARRAY_SIZE);

	if (!parse_first_3_lines_helper(labyrinth, &numbers, line, line_number)) {
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

		init_numbers_array(&labyrinth->partial_array, labyrinth->dimensions.size + 1);
		labyrinth->partial_array.size = labyrinth->dimensions.size + 1;
		calculate_partial_sums(&labyrinth->dimensions, &labyrinth->partial_array);
	} else if (numbers.size != labyrinth->dimensions.size) {
		free_numbers_array(&numbers);
		handle_wrong_input(line_number);

		return false;
	} else if (line_number == 2) {
		//fix_order(&numbers, labyrinth);

		labyrinth->start = array_rep_to_number_rep(&numbers, labyrinth);
		free_numbers_array(&numbers);

	} else if (line_number == 3) {
		//fix_order(&numbers, labyrinth);

		labyrinth->finish = array_rep_to_number_rep(&numbers, labyrinth);
		free_numbers_array(&numbers);

	}

	//for(size_t i = 0; i < numbers.size; i ++) printf("%zu\n", numbers.array[i]);

	//free_numbers_array(&numbers);
	return true;
}

bool parse_fourth_line_helper(Labyrinth *labyrinth, String *result_hexal_variant,
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

		if (parse_first_3_lines_helper(labyrinth, result_R_variant, line, line_number)) {
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
		for (; i < line->size; i++) {
			character = line->content[i];
			if (isxdigit(character)) {
				insert_str(result_hexal_variant, character, result_hexal_variant->size);
				continue;
			} else if (isspace(character)) {
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

bool parse_fourth_line(Labyrinth *labyrinth, Line *line, size_t line_number) {

	String result_hexal_variant;
	init_string(&result_hexal_variant);
	NumbersArray result_R_variant;
	init_numbers_array(&result_R_variant, 0);

	if (!parse_fourth_line_helper(labyrinth, &result_hexal_variant, &result_R_variant, line,
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

		if (labyrinth->walls_hexal_version.size - 1 > labyrinth->block_count) { 
			handle_wrong_input(line_number);
			free_numbers_array(&result_R_variant);
			free_string(&result_hexal_variant);

			return false;
		}

		free_numbers_array(&result_R_variant);
	}

	free_string(&result_hexal_variant);

	return true;
}

bool parse(Labyrinth *labyrinth) {
	init_labyrinth(labyrinth, 0);
	Line line;
	size_t lines_count = 1;
	bool success = true;

	while (true) {
		//debug, needed for clion debuggin which does not go well with endline
		if (lines_count == 5)
			return true;
		line = read_line();
		//printf("%s\n", line.content);
		//printf("%zu\n", line.size);

		if (!line.state && lines_count == MAX_NUM_LINES + 1) {
			break;
		} else if ((lines_count > MAX_NUM_LINES) || (!line.state && lines_count <= MAX_NUM_LINES)) {
			handle_wrong_input(lines_count);
			success = false;
			break;
		}
		
		//The fourth line may not end with \n, but the parsing of that line
		//will be shorter and nicer if they could assume that \n always will be 
		//present. Hence this insertion.
		if (lines_count == 4 && !isspace(line.content[line.size - 1])) {
			insert_line(&line, '\n', line.size); 
			insert_line(&line, '\0', line.size);
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

