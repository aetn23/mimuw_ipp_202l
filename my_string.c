#include <string.h>
#include <ctype.h>

#include "my_string.h"
#include "memory_managment.h"


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
	line->state = true;
}

//todo think if this function should exist
void insert(char *str, char to_insert, const size_t location) {
	str[location] = to_insert;
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


String hexal_to_binary(const String *hexal) {
	String result;
	init_string(&result);
	size_t i = 0;

	for (; i < hexal->size; i++) {
		char character = hexal->content[i];
		switch (tolower(character)) {
			case '0':
				insert_str(&result, '0', result.size);
				break;
			case '1':
				insert_str(&result, '1', result.size);
				break;
			case '2':
				concat_str(&result, "10");
				break;
			case '3':
				concat_str(&result, "11");
				break;
			case '4':
				concat_str(&result, "100");
				break;
			case '5':
				concat_str(&result, "101");
				break;
			case '6':
				concat_str(&result, "110");
				break;
			case '7':
				concat_str(&result, "111");
				break;
			case '8':
				concat_str(&result, "1000");
				break;
			case '9':
				concat_str(&result, "1001");
				break;
			case 'a':
				concat_str(&result, "1010");
				break;
			case 'b':
				concat_str(&result, "1011");
				break;
			case 'c':
				concat_str(&result, "1100");
				break;
			case 'd':
				concat_str(&result, "1101");
				break;
			case 'e':
				concat_str(&result, "1110");
				break;
			case 'f':
				concat_str(&result, "1111");
				break;
			default:
				break;
		}
	}

	return result;
}