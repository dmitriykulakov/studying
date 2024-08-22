#include "s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  int FLAG = 0;
  long unsigned int i = 0;
  if (str2[0] != '\0') {
    for (i = 0; str1[i] != '\0' && FLAG == 0; i++) {
      for (int j = 0; str2[j] != '\0' && FLAG == 0; j++) {
        if (str1[i] == str2[j]) {
          FLAG = 1;
          i--;
        }
      }
    }
  } else
    for (i = 0; str1[i] != '\0'; i++)
      ;
  return i;
}