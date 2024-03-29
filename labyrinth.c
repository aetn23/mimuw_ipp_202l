#include <string.h>

#include "labyrinth.h"
#include "memory_management.h"
#include "queue.h"

void init_labyrinth(Labyrinth *labyrinth, const size_t alloc_size) {
  init_numbers_array(&labyrinth->dimensions, 0);
  init_numbers_array(&labyrinth->partial_product, alloc_size);
  init_bit_array(&labyrinth->walls, 0);
  labyrinth->start = 0;
  labyrinth->finish = 0;
}

// This formula is taken directly from the task's description.
size_t array_rep_to_number_rep(const NumbersArray *array,
                               const Labyrinth *labyrinth) {
  size_t result = 0;

  for (size_t i = 0; i < array->size; i++)
    result += (array->array[i] - 1) * labyrinth->partial_product.array[i];

  return result;
}

inline bool is_wall(size_t block, Labyrinth *labyrinth) {
  return read_bit(&labyrinth->walls, block);
}

void get_new_neighbours_helper(const size_t block, Labyrinth *labyrinth,
                               NumFIFO *result, const size_t neighbour,
                               const size_t i) {
  size_t block_i_dimension = block / labyrinth->partial_product.array[i + 1];
  size_t neighbour_i_dimension =
      neighbour / labyrinth->partial_product.array[i + 1];

  bool is_neighbour_correct =
      neighbour < back_num_array(&labyrinth->partial_product) &&
      !is_wall(neighbour, labyrinth) &&
      block_i_dimension == neighbour_i_dimension;
  if (is_neighbour_correct) {
    enqueue(result, neighbour);
    toggle_bit(&labyrinth->walls, neighbour);
  }
}

// New neighbours can be counted directly from block number representation if
// one notices the relationship expressed in this function and its helper.
void get_new_neighbours(const size_t block, Labyrinth *labyrinth,
                        NumFIFO *result) {
  size_t i = 0;
  size_t neighbour;

  for (; i < labyrinth->partial_product.size - 1; i++) {
    bool is_bigger_neighbour_within_bounds =
        back_num_array(&labyrinth->partial_product) -
            labyrinth->partial_product.array[i] >=
        block;
    bool is_smaller_neighbour_within_bounds =
        block >= labyrinth->partial_product.array[i];

    if (is_bigger_neighbour_within_bounds) {
      neighbour = block + labyrinth->partial_product.array[i];
      get_new_neighbours_helper(block, labyrinth, result, neighbour, i);
    }

    if (is_smaller_neighbour_within_bounds) {
      neighbour = block - labyrinth->partial_product.array[i];
      get_new_neighbours_helper(block, labyrinth, result, neighbour, i);
    }
  }
}

// In order to find an end of labyrinth a simple bfs is used. Using of two
// queues allows easily return distance from start to the end, because said
// distance is equal to an amount of how much queue switches have been made, as
// in the function.
size_t get_result(Labyrinth *labyrinth) {
  size_t distance = 1;
  bool found = false;

  NumFIFO queue_0;
  init_fifo(&queue_0, START_ARRAY_SIZE);

  NumFIFO queue_1;
  init_fifo(&queue_1, START_ARRAY_SIZE);

  NumFIFO *active_queue = &queue_0;
  NumFIFO *non_active_queue = &queue_1;

  bool queue_0_active = true;
  bool queue_end = false;

  size_t block = labyrinth->start;

  toggle_bit(&labyrinth->walls, block);
  get_new_neighbours(block, labyrinth, active_queue);

  while (!(is_empty_queue(&queue_0) && is_empty_queue(&queue_1))) {

    block = dequeue(active_queue, &queue_end);
    if (queue_end) {
      active_queue = queue_0_active ? &queue_1 : &queue_0;
      non_active_queue = queue_0_active ? &queue_0 : &queue_1;
      queue_0_active = !queue_0_active;
      distance++;
      continue;
    }

    if (block == labyrinth->finish) {
      found = true;
      break;
    }

    get_new_neighbours(block, labyrinth, non_active_queue);
  }

  free_queue(&queue_0);
  free_queue(&queue_1);

  if (found)
    return distance;
  else
    return 0;
}