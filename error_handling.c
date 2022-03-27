#include <stdio.h>
#include <stdlib.h>

#include "error_handling.h"

#define ALLOC_FAILURE_EXIT_CODE 1

void handle_wrong_input(size_t line_num) {
	fprintf(stderr, "ERROR %zu\n", line_num);
}

void handle_alloc_failure() {
	fprintf(stderr, "ERROR 0\n");
	exit(ALLOC_FAILURE_EXIT_CODE);
}