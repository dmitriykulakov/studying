#include "../s21_math.h"

long double s21_fmod(double x, double y) {
  long double s21_x = x;
  long double s21_y = y;
  long double s21_fmod = 0;

  if (S21_IS_NAN(s21_x) || S21_IS_NAN(s21_y)) {
    s21_fmod = S21_NAN;
  } else if (S21_IS_INF_P(s21_x) || S21_IS_INF_N(s21_x)) {
    s21_fmod = S21_NAN;
  } else if (S21_IS_INF_P(s21_y) || S21_IS_INF_N(s21_y)) {
    s21_fmod = x;
  } else if (s21_y == 0.0L) {
    s21_fmod = S21_NAN;
  } else {
    if (s21_x == 0.0L) {
      s21_fmod = s21_x;
    }
    if (s21_x > 0) {
      s21_fmod = s21_x - s21_floor(s21_x / s21_fabs(s21_y)) * s21_fabs(s21_y);
    }
    if (s21_x < 0) {
      s21_fmod = s21_x - s21_ceil(s21_x / s21_fabs(s21_y)) * s21_fabs(s21_y);
    }
  }
  return s21_fmod;
}
