#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "containers.h"
#include "memory_managment.h"

void init_numbers_array(NumbersArray *num_array) {
	num_array->array = NULL;
	num_array->array_size = 0;
	num_array->allocated_size = 0;
}

void init_block(Block *block) {
	block->coordinates = NULL;
}

void init_labyrinth(Labyrinth *labyrinth) {
	labyrinth->dimensions = NULL;
	labyrinth->dimensions_size = 0;
	labyrinth->start = 0;
	labyrinth->finish = 0;
	labyrinth->is_hexal_version = false;
	labyrinth->walls_hexal_version.content = NULL;
}

void push_back_number(NumbersArray *num_array, size_t number) {
	if (num_array->allocated_size == num_array->array_size) {
		num_array->array = realloc_wrapper(num_array->array,
		                                   REALLOC_MULTIPLIER * num_array->allocated_size * sizeof(size_t));
		num_array->allocated_size = REALLOC_MULTIPLIER * num_array->allocated_size;
	}

	num_array->array[num_array->array_size] = number;
	num_array->array_size++;
	//printf("%zu   %zu\n", num_array->allocated_size, num_array->array_size);
}

void init_string(String *str) {
	str->content = malloc_wrapper(sizeof(char) * START_ARRAY_SIZE);
	check_alloc(str->content);
	str->size = 0;
	str->allocated_size = START_ARRAY_SIZE;
}

void init_line(Line *line) {
	line->content = NULL;
	line->size = 0;
	line->state = true;
}

void insert(char *str, char to_insert, size_t location) {
	str[location] = to_insert;

}

//There is no guarantee that string wil be null terminated after this operation
void str_insert(String *str, char to_insert, size_t location) {
	while (location >= str->allocated_size) {
		str->content = realloc_wrapper(str->content, sizeof(char) * REALLOC_MULTIPLIER * str->allocated_size);
		check_alloc(str->content);
		str->allocated_size = REALLOC_MULTIPLIER * str->allocated_size;
	}

	str->content[location] = to_insert;
	str->size++;
}

void str_concat(String *str, char *to_concat) {
	size_t to_concat_len = strlen(to_concat);
	while (to_concat_len + str->size >= str->allocated_size) {
		str->content = realloc_wrapper(str->content, sizeof(char) * REALLOC_MULTIPLIER * str->allocated_size);
		check_alloc(str->content);
		str->allocated_size = REALLOC_MULTIPLIER * str->allocated_size;
	}
	for(size_t i = 0; i < to_concat_len; i++)
		str->content[i + str->size] = to_concat[i];

	str->size += to_concat_len;
}

void clear_str(String *str) {
	for (size_t i = 0; i < str->size; i++)
		str->content[i] = '\0';
	str->size = 0;
}

size_t str_to_size_t(String *str) {
	char *str_end;

	return strtoull(str->content, &str_end, 10);
}

void init_bool_array(BoolArray *bool_array, size_t size) {
	bool_array->array = malloc(size * sizeof(bool));
	check_alloc(bool_array->array);
}

String hexal_to_binary(String *hexal) {
	String result;
	init_string(&result);
	size_t i = 0;

	for(; i < hexal->size; i++) {
		char character = hexal->content[i];
		switch (tolower(character)) {
			case '0':
				str_insert(&result, '0', result.size);
				break;
			case '1':
				str_insert(&result, '1', result.size);
				break;
			case '2':
				str_concat(&result, "10");
				break;
			case '3':
				str_concat(&result, "11");
				break;
			case '4':
				str_concat(&result, "100");
				break;
			case '5':
				str_concat(&result, "101");
				break;
			case '6':
				str_concat(&result, "110");
				break;
			case '7':
				str_concat(&result, "111");
				break;
			case '8':
				str_concat(&result, "1000");
				break;
			case '9':
				str_concat(&result, "1001");
				break;
			case 'a':
				str_concat(&result, "1010");
				break;
			case 'b':
				str_concat(&result, "1011");
				break;
			case 'c':
				str_concat(&result, "1100");
				break;
			case 'd':
				str_concat(&result, "1101");
				break;
			case 'e':
				str_concat(&result, "1110");
				break;
			case 'f':
				str_concat(&result, "1111");
				break;
			default:
				break;
		}
	}

	return result;
}