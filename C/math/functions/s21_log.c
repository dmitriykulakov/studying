#include "../s21_math.h"

long double s21_log(double x) {
  long double s21_x = x;
  long double result = 0;
  long long int result1 = 0;
  long double tmp;
  if (S21_IS_NAN(s21_x)) result = S21_NAN;
  if (S21_IS_INF_P(s21_x)) result = S21_INF_P;
  if (S21_IS_INF_N(s21_x)) result = S21_NAN;
  if (s21_x == 0) result = S21_INF_N;
  if (s21_x < 0) result = S21_NAN;
  if (!S21_IS_NAN(s21_x) && !S21_IS_INF_P(s21_x) && !S21_IS_INF_N(s21_x) &&
      s21_x > 0) {
    while (s21_x >= S21_E) {
      s21_x = s21_x / S21_E;
      result1++;
    }
    for (int i = 0; i < 64; i++) {
      tmp = result;
      result = tmp + 2 * (s21_x - s21_exp(tmp)) / (s21_x + s21_exp(tmp));
    }
  }
  return result + result1;
}
