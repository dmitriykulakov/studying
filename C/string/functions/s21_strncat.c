#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  int m = 0;
  for (int i = 0; dest[i] != '\0'; i++) {
    m++;
  }
  for (long unsigned int i = 0; i < n; i++, m++) {
    dest[m] = src[i];
  }
  return dest;
}