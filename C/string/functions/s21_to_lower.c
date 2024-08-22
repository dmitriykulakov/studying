#include "s21_string.h"

void *s21_to_lower(const char *str) {
  char *result = S21_NULL;
  if (str) {
    s21_size_t len = s21_strlen(str);
    result = (char *)malloc(len + 1);
    if (result != S21_NULL) {
      s21_strncpy(result, str, len);
      result[len] = '\0';
      char *temp = result;
      while (temp != result + len) {
        if (*temp >= 65 && *temp <= 90) {
          *temp += 32;
        }
        temp++;
      }
    } else {
      fprintf(stderr, "Memory fail");
    }
  }
  return result;
}