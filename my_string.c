#include <string.h>

#include "my_string.h"
#include "memory_managment.h"
#include "common_defines.h"

#define HEXAl_AS_BIN_SIZE 4

#define BASE_TWO 2

void init_string(String *str, size_t size) {
	if (size != 0) {
		str->content = malloc_wrapper(sizeof(char) * START_ARRAY_SIZE);
		check_alloc(str->content);
		str->size = 0;
		str->allocated_size = START_ARRAY_SIZE;
	} else {
		str->content = NULL;
		str->size = 0;
		str->allocated_size = START_ARRAY_SIZE;
	}
}

void init_line(Line *line, size_t size) {
	if (size != 0) {
		line->content = malloc_wrapper(size * sizeof(char));
		line->size = 0;
		line->allocated_size = size;
		line->state = true;
	} else {
		line->content = NULL;
		line->size = 0;
		line->allocated_size = 0;
		line->state = true;
	}
}

//todo think if this function should exist
void insert(char *str, char to_insert, const size_t location) {
	str[location] = to_insert;
}

void insert_line(Line *line, char to_insert, size_t location) {
	while (line->allocated_size <= location) {
		line->content = realloc_wrapper(line->content, line->allocated_size * REALLOC_MULTIPLIER);
		check_alloc(line->content);
		line->allocated_size *= REALLOC_MULTIPLIER;
	}
	line->content[location] = to_insert;
	line->size++;
}

//There is no guarantee that string wil be null terminated after this operation
void insert_str(String *str, const char to_insert, const size_t location) {
	while (location >= str->allocated_size) {
		str->content = realloc_wrapper(str->content, sizeof(char) * REALLOC_MULTIPLIER * str->allocated_size);
		check_alloc(str->content);
		str->allocated_size = REALLOC_MULTIPLIER * str->allocated_size;
	}

	str->content[location] = to_insert;
	str->size++;
}

void clear_str(String *str) {
	for (size_t i = 0; i < str->size; i++)
		str->content[i] = '\0';
	str->size = 0;
}

size_t str_to_size_t(const String *str) {
	char *str_end;

	return strtoull(str->content, &str_end, BASE_TEN);
}

size_t hexal_to_reverse_binary(String *str, NumbersArray *result) {
	char *character = malloc(2 * sizeof(char));
	*(character + 1) = NULL_CHAR;

	size_t distance_since_last_one = 0;
	size_t position = 0;

	for (size_t i = str->size - 1;; i--) {
		*character = str->content[i];
		long number = strtol(character, NULL, BASE_SIXTEEN);
		for (size_t j = 0; j < HEXAl_AS_BIN_SIZE; j++) {
			if (number % BASE_TWO == 0)
				distance_since_last_one++;
			else 
				distance_since_last_one = 0;
			if (number % BASE_TWO == 1)
				toggle_bit(result, position);
			number /= BASE_TWO;
			position++;
		}
		if (i == 0)
			break;
	}
	//printf("\n");
	free(character);
	return distance_since_last_one;

}