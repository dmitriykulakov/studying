#include "s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  void *tmp = dest;
  for (long unsigned int i = 0; i < n; i++, tmp++, src++) {
    *(char *)tmp = *(char *)src;
  }
  return dest;
}