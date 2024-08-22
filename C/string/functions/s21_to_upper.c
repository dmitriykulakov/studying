#include "s21_string.h"

void *s21_to_upper(const char *str) {
  char *result = S21_NULL;
  if (str) {
    s21_size_t len = s21_strlen(str);
    result = (char *)malloc(len + 1);
    if (result) {
      s21_strncpy(result, str, len);
      char *temp = result;
      result[len] = '\0';
      while (temp != result + len) {
        if (*temp >= 97 && *temp <= 122) {
          *temp -= 32;
        }
        temp++;
      }
    }
  }
  return result;
}