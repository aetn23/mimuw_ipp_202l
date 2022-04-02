#include <string.h>

#include "memory_managment.h"
#include "my_string.h"

#define HEXAl_AS_BIN_SIZE 4
#define BASE_TWO 2
#define BASE_TEN 10
#define BASE_SIXTEEN 16

void init_line(Line *line, size_t size) {
  if (size != 0) {
    line->content = malloc_wrapper(size * sizeof(char));
    line->size = 0;
    line->allocated_size = size;
    line->state = true;
  } else {
    line->content = NULL;
    line->size = 0;
    line->allocated_size = 0;
    line->state = true;
  }
}

void insert_line(Line *line, const char to_insert, const size_t location) {
  while (line->allocated_size <= location) {
    line->allocated_size *= REALLOC_MULTIPLIER;
    line->content = realloc_wrapper(line->content, line->allocated_size);
  }

  line->content[location] = to_insert;
  line->size++;
}

void init_string(String *str, const size_t size) {
  if (size != 0) {
    str->content = malloc_wrapper(sizeof(char) * START_ARRAY_SIZE);
    str->size = 0;
    str->allocated_size = START_ARRAY_SIZE;
  } else {
    str->content = NULL;
    str->size = 0;
    str->allocated_size = START_ARRAY_SIZE;
  }
}

// There is no guarantee that string wil be null terminated after this.
void insert_str(String *str, const char to_insert, const size_t location) {
  while (location >= str->allocated_size) {
    str->allocated_size *= REALLOC_MULTIPLIER;
    str->content =
        realloc_wrapper(str->content, sizeof(char) * str->allocated_size);
  }

  str->content[location] = to_insert;
  str->size++;
}

void clear_str(String *str) {
  for (size_t i = 0; i < str->size; i++)
    str->content[i] = NULL_CHAR;
  str->size = 0;
}

// Getting walls from hexal is essentially reading consecutive bits starting
// from the end of string. Also leading zeroes have to be taken into account in
// order to correctly calculate size of walls. This function assumes it receives
// result array filled with zeroes.
size_t get_walls_hexal_version(String *str, NumbersArray *result) {
  char *character = malloc(2 * sizeof(char));
  character[1] = NULL_CHAR;

  size_t distance_since_last_one = 0;
  size_t position = 0;

  for (size_t i = str->size - 1;; i--) {
    *character = str->content[i];
    long number = strtol(character, NULL, BASE_SIXTEEN);

    for (size_t j = 0; j < HEXAl_AS_BIN_SIZE; j++) {
      if (number % BASE_TWO == 0)
        distance_since_last_one++;
      else
        distance_since_last_one = 0;

      if (number % BASE_TWO == 1)
        toggle_bit(result, position);
      else
        result->size++;

      number /= BASE_TWO;
      position++;
    }
    if (i == 0)
      break;
  }

  free(character);
  result->size -= distance_since_last_one;

  return distance_since_last_one;
}

size_t str_to_size_t(const String *str) {
  return strtoull(str->content, NULL, BASE_TEN);
}