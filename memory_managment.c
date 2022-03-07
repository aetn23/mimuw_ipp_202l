#include <stdlib.h>

#include "memory_managment.h"

void check_alloc(void *pointer) {
	if (pointer == NULL)
		exit(1);
}
