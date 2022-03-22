#ifndef _QUEUE_
#define _QUEUE_

#include <stddef.h>
#include <stdbool.h>

#include "arrays.h"
//FIFO can be implemented using linked list, which is memory effective, but
//has insertion time complexity of O(n) which is huge drawback, since in this
//task insertion to queue will be used much. Also linked list do not have
//caching benefits of array's.
//To mitigate memory effectiveness of array FIFO I will reallocate it every x
//elements.
typedef struct NumFIFO {
	NumbersArray array;
	size_t first_pos;
} NumFIFO;


void init_fifo(NumFIFO *fifo, size_t alloc_size);
void enqueue(NumFIFO *fifo, size_t value);
size_t dequeue(NumFIFO *fifo, bool *end);
bool is_empty_queue(NumFIFO *queue);

#endif //_QUEUE_