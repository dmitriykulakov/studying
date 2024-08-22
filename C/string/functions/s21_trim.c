#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *res = NULL;
  if (src && trim_chars) {
    int start = 0;
    int end = s21_strlen(src);
    while (src[start] && s21_strchr(trim_chars, src[start])) start++;
    while (end != start && s21_strchr(trim_chars, src[end - 1])) end--;
    res = (char *)malloc((end - start + 1));
    if (res) {
      for (int i = start; i < end; i++) {
        res[i - start] = src[i];
      }
      res[end - start] = '\0';
    }
  }
  return res;
}
