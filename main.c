#include <stdio.h>

#include "labyrinth.h"
#include "memory_managment.h"
#include "parse.h"

int main() {
  Labyrinth labyrinth;
  init_labyrinth(&labyrinth, START_ARRAY_SIZE);
  bool good_input = parse(&labyrinth);

  if (good_input) {
    if (labyrinth.start == labyrinth.finish) {
      printf("0\n");
    } else {
      size_t result = get_result(&labyrinth);

      if (result == 0)
        printf("NO WAY\n");
      else
        printf("%zu\n", result);
    }
  }
  free_labyrinth(&labyrinth);

  return 0;
}