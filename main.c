#include "containers.h"
#include "parse.h"
#include "memory_managment.h"

int main() {
	Labyrinth labyrinth;
	parse(&labyrinth);
	free_labyrinth(&labyrinth);


	NumFIFO fifo;
	bool end = false;
	init_fifo(&fifo);
	enqueue(&fifo, 1);
	enqueue(&fifo, 1);
	enqueue(&fifo, 1);
	enqueue(&fifo, 1);
	enqueue(&fifo, 1);
	enqueue(&fifo, 1);
	dequeue(&fifo, &end);
	dequeue(&fifo, &end);
	dequeue(&fifo, &end);
	dequeue(&fifo, &end);
	dequeue(&fifo, &end);
	dequeue(&fifo, &end);
	dequeue(&fifo, &end);
	dequeue(&fifo, &end);
	dequeue(&fifo, &end);
	dequeue(&fifo, &end);
	dequeue(&fifo, &end);
	dequeue(&fifo, &end);
	dequeue(&fifo, &end);
	dequeue(&fifo, &end);
	free_queue(&fifo);
	return 0;
}