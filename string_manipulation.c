#include "string_manipulation.h"
#include "memory_managment.h"

void init_string(String *str) {
	str->content = malloc_wrapper(sizeof(char)*START_ARRAY_SIZE);
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
	while (location > str->allocated_size) {
		str->content = realloc_wrapper(str->content, sizeof(char) * REALLOC_MULTIPLIER * str->allocated_size);
		str->allocated_size = REALLOC_MULTIPLIER * str->allocated_size;
	}

	str->content[location] = to_insert;
	str->size++;
}

void clear_str(String *str) {
	for(size_t i = 0; i < str->size; i++)
		str->content[i] = '\0';
	str->size = 0;
}

size_t str_to_size_t(String *str) {
	char *str_end;

	return strtoull(str->content, &str_end, 10);
}


