#include "s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int result = 0, FLAG = 0;
  for (long unsigned int i = 0; FLAG == 0 && i < n; i++, str1++, str2++) {
    if (*(char *)str1 != *(char *)str2) {
      result = *(char *)str1 - *(char *)str2;
      FLAG = 1;
    }
  }
  return result;
}