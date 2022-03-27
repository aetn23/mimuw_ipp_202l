#include <string.h>
#include <ctype.h>

#include "my_string.h"
#include "memory_managment.h"


#define HEXAl_AS_BIN_SIZE 4

//todo this is inconsitent
void init_string(String *str) {
	str->content = malloc_wrapper(sizeof(char) * START_ARRAY_SIZE);
	check_alloc(str->content);
	str->size = 0;
	str->allocated_size = START_ARRAY_SIZE;
}

void init_line(Line *line) {
	line->content = NULL;
	line->size = 0;
	line->allocated_size = 0;
	line->state = true;
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

void concat_str(String *str, char *to_concat) {
	size_t to_concat_len = strlen(to_concat);
	while (to_concat_len + str->size >= str->allocated_size) {
		str->content = realloc_wrapper(str->content, sizeof(char) * REALLOC_MULTIPLIER * str->allocated_size);
		check_alloc(str->content);
		str->allocated_size = REALLOC_MULTIPLIER * str->allocated_size;
	}
	for (size_t i = 0; i < to_concat_len; i++)
		str->content[i + str->size] = to_concat[i];

	str->size += to_concat_len;
}

void clear_str(String *str) {
	for (size_t i = 0; i < str->size; i++)
		str->content[i] = '\0';
	str->size = 0;
}

size_t str_to_size_t(const String *str) {
	char *str_end;

	return strtoull(str->content, &str_end, 10);
}


//write and algot  that takes hexal str and turns into binary array, but:
//it has to be done in reverse, ie:
//0x7 = 0111,
//so res = 1110
//0x76 = 0111 0110
// so res = 0110 1110
//to do it cleverly.
void hexal_to_reverse_binary(String *str, BoolArray *result) {
	for (size_t i = str->size - 1;; i--) {
		char character = str->content[i];
		long number = strtol(&character, NULL, 16);

		for (size_t j = 0; j < HEXAl_AS_BIN_SIZE; j++) {
			push_back_bool(result, (bool)(number % 2));
			number /= 2;
		}
		if (i == 0)
			break;
	}
}