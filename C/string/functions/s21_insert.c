#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *result = S21_NULL;
  if (src && str && s21_strlen(str) >= start_index) {
    s21_size_t len = s21_strlen(str) + s21_strlen(src);
    result = (char *)malloc(len + 1);
    if (result != S21_NULL) {
      result[len] = '\0';
      s21_size_t i = 0;
      for (; i < start_index; i++) {
        result[i] = src[i];
      }
      s21_size_t src_end = i;
      for (s21_size_t j = 0; j < s21_strlen(str); j++, i++) {
        result[i] = str[j];
      }
      for (; src[src_end] != '\0'; src_end++, i++) {
        result[i] = src[src_end];
      }
    }
  }
  return result;
}