#include "../s21_math.h"

long double s21_exp(double x) {
  long double s21_x = x;
  long double result1 = S21_E;
  long double result2 = 1;
  int FLAG = 0;
  if (s21_x != 0) {
    if (S21_IS_NAN(s21_x)) result1 = S21_NAN;
    if (S21_IS_INF_P(s21_x)) result1 = S21_INF_P;
    if (S21_IS_INF_N(s21_x)) result1 = S21_INF_N;
    if (s21_x > 800) {
      result1 = S21_INF_P;
      FLAG = 1;
    }
    if (s21_x < -25) {
      result1 = 0;
      FLAG = 1;
    }
    if (!S21_IS_NAN(s21_x) && !S21_IS_INF_P(s21_x) && !S21_IS_INF_N(s21_x) &&
        FLAG == 0) {
      long double tmp = s21_x;
      if (tmp < 0) tmp = tmp * (-1);
      tmp = s21_floor(tmp);
      long double tmp2;
      if (s21_x < 0)
        tmp2 = (s21_x * -1) - tmp;
      else
        tmp2 = s21_x - tmp;
      for (int i = 1; i < tmp; i++) {
        result1 = result1 * S21_E;
      }
      if (tmp < 1) result1 = 1;
      if (tmp2 > 0) {
        long double tmp3 = 1;
        for (int i = 1; s21_fabs(tmp3) > 1E-24L; i++) {
          tmp3 = tmp3 * tmp2 / (long double)i;
          result2 = result2 + tmp3;
        }
      }
      result1 = result1 * result2;
      if (s21_x < 0) result1 = 1 / result1;
    }
  } else
    result1 = 1;
  return result1;
}