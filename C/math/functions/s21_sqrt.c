#include "../s21_math.h"

long double s21_sqrt(double x) {
  long double s21_x = x;
  long double result = s21_x / 2;
  if (S21_IS_NAN(s21_x)) result = S21_NAN;
  if (S21_IS_INF_P(s21_x)) result = S21_INF_P;
  if (S21_IS_INF_N(s21_x)) result = S21_NAN;
  if (s21_x == 0) result = 0;
  if (!S21_IS_NAN(s21_x) && !S21_IS_INF_P(s21_x) && !S21_IS_INF_N(s21_x) &&
      s21_x != 0) {
    if (s21_x > 0) {
      for (int i = 0; i < 40; i++) {
        result = 0.5 * (result + s21_x / result);
      }
    } else
      result = S21_NAN;
  }
  return result;
}
