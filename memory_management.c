#include "memory_management.h"
#include "error_handling.h"

void check_alloc(void *pointer) {
  if (pointer == NULL)
    handle_alloc_failure();
}

void *malloc_wrapper(const size_t size) {
  void *result = malloc(size);
  check_alloc(result);

  return result;
}

void *calloc_wraper(const size_t num, const size_t size) {
  void *result = calloc(num, size);
  check_alloc(result);

  return result;
}

void *realloc_wrapper(void *ptr, const size_t size) {
  ptr = realloc(ptr, size);
  check_alloc(ptr);

  return ptr;
}

void free_numbers_array(NumbersArray *array) {
  if (array->array != NULL)
    free(array->array);
}

void free_string(String *str) {
  if (str->content != NULL)
    free(str->content);
}

void free_labyrinth(Labyrinth *labyrinth) {
  free_numbers_array(&labyrinth->walls);
  free_numbers_array(&labyrinth->dimensions);
  free_numbers_array(&labyrinth->partial_product);
}

void free_queue(NumFIFO *fifo) { free_numbers_array(&fifo->array); }