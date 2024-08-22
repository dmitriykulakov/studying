#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  int FLAG = 0;
  char *result = S21_NULL;
  for (; *str != '\0' && FLAG == 0; str++) {
    if (*str == c) {
      result = (void *)str;
      FLAG = 1;
    }
  }
  if (*str == '\0' && FLAG == 0 && c == '\0') result = (void *)str;
  return result;
}
