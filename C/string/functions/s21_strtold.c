#include "s21_string.h"

long double s21_strtold(const char *str) {
  long double res = 0.;
  long double temp = 1.0;
  int counter = 0, sign = 1, i = 0;
  if (s21_strstr("nan", str)) {
    res = NAN;
  } else if (s21_strstr("inf", str)) {
    res = INFINITY;
  } else {
    if (str[i] == '-') {
      sign = -1.;
      i++;
    } else if (str[i] == '+') {
      i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
      res = res * 10 + str[i] - '0';
      i++;
    }
    if (str[i] == '.') {
      i++;
    }
    while (str[i] >= '0' && str[i] <= '9') {
      res = res * 10 + str[i] - '0';
      counter++;
      i++;
    }
    for (int j = 0; j < counter; j++) {
      temp *= 10;
    }
    res /= temp;
    if (str[i] == 'e' || str[i] == 'E') {
      str_spec_e(str, i, &res);
    }
    res *= sign;
  }

  return res;
}

void str_spec_e(const char *str, int i, long double *res) {
  int exponent = 0, exp_sign = 1;

  i++;
  if (str[i] == '-') {
    exp_sign = -1;
    i++;
  } else if (str[i] == '+') {
    i++;
  }
  while (str[i] >= '0' && str[i] <= '9') {
    exponent = exponent * 10 + str[i] - '0';
    i++;
  }
  exponent *= exp_sign;
  long double temp = pow(10, exponent);
  *res *= temp;
}