#include "../s21_math.h"

long double s21_fabs(double x) {
  long double s21_x = x;
  long double result = s21_x;
  if (S21_IS_NAN(s21_x)) result = S21_NAN;
  if (S21_IS_INF_P(s21_x)) result = S21_INF_P;
  if (S21_IS_INF_N(s21_x)) result = S21_INF_P;
  if (!S21_IS_NAN(s21_x) && !S21_IS_INF_P(s21_x) && !S21_IS_INF_N(s21_x)) {
    if (s21_x < 0) result = s21_x * (-1L);
  }
  return result;
}