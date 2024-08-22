#include "s21_string.h"

s21_size_t s21_strlen(const char *str) {
  long unsigned int i = 0;
  for (; *str != '\0'; i++, str++)
    ;
  return i;
}