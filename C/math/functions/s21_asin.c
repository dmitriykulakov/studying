#include "../s21_math.h"

long double s21_asin(double x) {
  long double s21_x = x;
  long double s21_asin = 0;

  if (S21_IS_NAN(s21_x)) {
    s21_asin = S21_NAN;
  } else if (S21_IS_INF_P(s21_x)) {
    s21_asin = S21_NAN;
  } else if (S21_IS_INF_N(s21_x)) {
    s21_asin = S21_NAN;
  } else if ((s21_x < -1.0L) || (1.0L < s21_x)) {
    s21_asin = S21_NAN;
  } else if (s21_x == 1.0L) {
    s21_asin = +S21_PI / 2;
  } else if (s21_x == 0.0L) {
    s21_asin = 0L;
  } else if (s21_x == -1.0L) {
    s21_asin = -S21_PI / 2;
  } else {
    s21_asin = s21_atan(s21_x / s21_sqrt(1 - s21_x * s21_x));
  }
  return s21_asin;
}
