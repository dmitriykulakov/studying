#include "../s21_math.h"

long double s21_ceil(double x) {
  long double s21_x = x;
  long double result;
  if (S21_IS_NAN(s21_x)) result = S21_NAN;
  if (S21_IS_INF_P(s21_x)) result = S21_INF_P;
  if (S21_IS_INF_N(s21_x)) result = S21_INF_N;
  if (!S21_IS_NAN(s21_x) && !S21_IS_INF_P(s21_x) && !S21_IS_INF_N(s21_x)) {
    char buffer[10000];
    sprintf(buffer, "%.Lf", s21_x);
    sscanf(buffer, "%Lf", &result);
    if (result < s21_x) result++;
  }
  return result;
}