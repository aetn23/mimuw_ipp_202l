#ifndef _QUEUE_
#define _QUEUE_

#include <stddef.h>
#include <stdbool.h>

#include "arrays.h"

typedef struct NumFIFO {
	NumbersArray array;
	size_t first_pos;
} NumFIFO;

void init_fifo(NumFIFO *fifo, size_t alloc_size);

void enqueue(NumFIFO *fifo, size_t value);

size_t dequeue(NumFIFO *fifo, bool *end);

bool is_empty_queue(NumFIFO *queue);

#endif //_QUEUE_