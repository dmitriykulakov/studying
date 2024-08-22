#include "../s21_math.h"

long double s21_cos(double x) {
  long double s21_x = x;
  long double s21_cos = 0;

  if (S21_IS_NAN(s21_x)) {
    s21_cos = S21_NAN;
  } else if (S21_IS_INF_P(s21_x)) {
    s21_cos = S21_NAN;
  } else if (S21_IS_INF_N(s21_x)) {
    s21_cos = S21_NAN;
  } else {
    s21_x = s21_fmod(s21_x, 2 * S21_PI);
    long double error = 10 * EPS;
    long double member = 1;
    for (int i = 1; s21_fabs((double)error) > EPS; i++) {
      s21_cos = s21_cos + member;
      member = member * ((-1) * s21_x * s21_x) / ((2 * i) * (2 * i - 1));
      error = member;
    }
  }
  return s21_cos;
}
