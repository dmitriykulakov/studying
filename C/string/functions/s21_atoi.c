#include "s21_string.h"

int s21_atoi(const char *str) {
  int res = 0;
  int sign = 1;
  int i = 0;
  if (str[i] == '-') {
    sign *= -1;
    i++;
  } else if (str[i] == '+')
    i++;
  for (; str[i] != '\0'; i++) {
    res = res * 10 + str[i] - '0';
  }
  res *= sign;

  return res;
}