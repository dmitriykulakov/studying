#include "s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  void *tmp = str;
  for (long unsigned int i = 0; i < n; i++, tmp++) {
    *(char *)tmp = c;
  }
  return str;
}