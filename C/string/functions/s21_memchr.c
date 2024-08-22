#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  int FLAG = 0;
  void *result = S21_NULL;
  for (long unsigned int i = 0; FLAG == 0 && i < n; i++, str++) {
    if (*(char *)str == c) {
      result = (void *)str;
      FLAG = 1;
    }
  }
  return result;
}