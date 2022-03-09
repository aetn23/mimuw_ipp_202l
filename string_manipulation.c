#include "string_manipulation.h"

void init_string(String *line) {
	line->content = NULL;
	line->size = 0;
	line->state = true;
}