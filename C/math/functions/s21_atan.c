#include "../s21_math.h"

long double s21_atan(double x) {
  long double s21_x = x;
  long double s21_atan_ = 0;

  if (S21_IS_NAN(s21_x)) {
    s21_atan_ = S21_NAN;
  } else if (S21_IS_INF_P(s21_x)) {
    s21_atan_ = +S21_PI / 2;
  } else if (S21_IS_INF_N(s21_x)) {
    s21_atan_ = -S21_PI / 2;
  } else if (s21_x == 1.0L) {
    s21_atan_ = 0.785398163L;
  } else if (s21_x == -1.0L) {
    s21_atan_ = -0.785398163L;
  } else {
    if (s21_x > 1) {
      s21_atan_ = +S21_PI / 2 - s21_atan(1 / s21_x);
    }
    if (s21_x < -1) {
      s21_atan_ = -S21_PI / 2 - s21_atan(1 / s21_x);
    }
    if ((-1 < s21_x) && (s21_x < 1)) {
      long double error = 10 * EPS;
      long double member = s21_x;
      for (int i = 2; s21_fabs((double)error) > EPS; i++) {
        s21_atan_ = s21_atan_ + member;
        member =
            member * ((-1) * s21_x * s21_x) * (2 * i - 1 - 2) / (2 * i - 1);
        error = member;
      }
    }
  }
  return s21_atan_;
}
