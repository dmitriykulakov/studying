#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;
  int FLAG = 0;
  for (int i = 0; haystack[i] != '\0' && FLAG == 0; i++) {
    if (haystack[i] == needle[0]) {
      int k = i, n = 0;
      for (; haystack[k] == needle[n] && haystack[k] != '\0' &&
             needle[n] != '\0' && FLAG == 0;
           k++, n++)
        ;
      if (needle[n] == '\0') {
        result = (void *)haystack + i;
        FLAG = 1;
      }
    }
  }
  if (needle[0] == '\0') result = (void *)haystack;
  return result;
}