#include "s21_string.h"

char *s21_strerror(int error_int) {
  void *result1 = S21_NULL;
  static char result[100] = {0};

#if __APPLE__
  char *str[] = {answer_mac};
  int error = 106;
#elif __linux__
  char *str[] = {answer_linux};
  int error = 133;
#endif

  if (error_int >= 0 && error_int <= error)
    result1 = str[error_int];
  else {
    s21_sprintf(result, "%s%d", str[error + 1], error_int);
    result1 = result;
  }
  return result1;
}