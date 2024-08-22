#include "../s21_math.h"

long double s21_sin(double x) {
  long double s21_x = x;
  long double s21_sin = 0;

  if (S21_IS_NAN(s21_x)) {
    s21_sin = S21_NAN;
  } else if (S21_IS_INF_P(s21_x)) {
    s21_sin = S21_NAN;
  } else if (S21_IS_INF_N(s21_x)) {
    s21_sin = S21_NAN;
  } else {
    s21_x = s21_fmod(s21_x, 2 * S21_PI);
    long double error = 10 * EPS;
    long double member = s21_x;
    for (int i = 2; s21_fabs((double)error) > EPS; i++) {
      s21_sin = s21_sin + member;
      member = member * ((-1) * s21_x * s21_x) / ((2 * i - 1) * (2 * i - 2));
      error = member;
    }
  }
  return s21_sin;
}
