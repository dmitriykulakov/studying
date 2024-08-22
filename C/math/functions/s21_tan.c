#include "../s21_math.h"

long double s21_tan(double x) {
  long double s21_x = x;
  long double s21_tan = 0;

  if (S21_IS_NAN(s21_x)) {
    s21_tan = S21_NAN;
  } else if (S21_IS_INF_P(s21_x)) {
    s21_tan = S21_NAN;
  } else if (S21_IS_INF_N(s21_x)) {
    s21_tan = S21_NAN;
  } else {
    s21_x = s21_fmod(s21_x, 2 * S21_PI);
    s21_tan = s21_sin(s21_x) / s21_cos(s21_x);
  }
  return s21_tan;
}