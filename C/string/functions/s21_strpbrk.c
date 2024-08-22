#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = S21_NULL;
  int FLAG = 0;
  for (int j = 0; str1[j] != '\0' && FLAG == 0; j++) {
    for (int i = 0; str2[i] != '\0' && FLAG == 0; i++) {
      if (str1[j] == str2[i]) {
        result = ((void *)str1 + j);
        FLAG = 1;
      }
    }
  }
  return result;
}