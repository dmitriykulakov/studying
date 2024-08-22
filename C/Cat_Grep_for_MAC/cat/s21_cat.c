#include "s21_cat.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  char flags[7] = {0};
  int n_flags_FLAG = 0, i;
  if (argc >= 2) {
    i = flags_building(flags, argv, argc, &n_flags_FLAG);
    if (n_flags_FLAG == 0) {
      work_with_the_file(flags, argv, argc, i);
    }
  }
  return 0;
}