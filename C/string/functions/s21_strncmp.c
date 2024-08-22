#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0, FLAG = 0;
  for (long unsigned int i = 0; FLAG == 0 && i < n; i++, str1++, str2++) {
    if (*str1 != *str2) {
      result = *str1 - *str2;
      FLAG = 1;
    }
  }
  return result;
}