#include "queue.h"

void init_fifo(NumFIFO *fifo) {
	init_numbers_array(&fifo->array);
	fifo->first_pos = 0;
}

void enqueue(NumFIFO *fifo, const size_t value) {
	push_back_number(&fifo->array, value);

}

//todo implement shrinking after first_pos > constant
size_t dequeue(NumFIFO *fifo, bool *end) {
	if (fifo->first_pos >= fifo->array.size) {
		*end = true;
		return 0;
	} else {
		//printf("DEQUE: %zu\n", fifo->array.array[fifo->first_pos]);
		*end = false;
		return fifo->array.array[fifo->first_pos++];
	}
}

bool is_empty_queue(NumFIFO *queue) {
	return queue->first_pos >= queue->array.size;
}