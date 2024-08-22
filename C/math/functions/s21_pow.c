#include "../s21_math.h"

long double s21_pow(double base, double exp_) {
  long double s21_base = base, s21_exp_ = exp_, result = 1, result1 = 1;
  int FLAG = 0;
  if (S21_IS_NAN(s21_exp_) || S21_IS_NAN(s21_base)) result = S21_NAN;
  if ((S21_IS_NAN(s21_base) && s21_exp_ == 0) || s21_exp_ == 0) result = 1;
  if ((s21_base != 0 && !S21_IS_NAN(s21_base) && S21_IS_INF_P(s21_exp_)) ||
      (s21_base == 0 && S21_IS_INF_N(s21_exp_)))
    result = S21_INF_P;
  if (S21_IS_INF_N(s21_base) && !S21_IS_INF_P(s21_exp_) &&
      !S21_IS_INF_N(s21_exp_) && !S21_IS_NAN(s21_exp_) && s21_exp_ > 0)
    result = S21_INF_N;
  if ((s21_exp_ < 0 && s21_base == 0) ||
      (S21_IS_INF_P(s21_base) && s21_exp_ > 0))
    result = S21_INF_P;
  if (S21_IS_INF_N(s21_exp_) && s21_base != 0 && !S21_IS_NAN(s21_base))
    result = 0;
  if ((s21_base == 0 && (s21_exp_ > 0 || S21_IS_INF_P(s21_exp_))) ||
      (s21_exp_ < 0 && S21_IS_INF_P(s21_base)))
    result = 0;
  if (S21_IS_INF_N(s21_base) && s21_exp_ < 0) result = -0;
  if (!S21_IS_NAN(s21_exp_) && !S21_IS_INF_P(s21_exp_) &&
      !S21_IS_INF_N(s21_exp_) && !S21_IS_INF_P(s21_base) &&
      !S21_IS_INF_N(s21_base) && !S21_IS_NAN(s21_base) && s21_exp_ != 0 &&
      s21_base != 0) {
    if (s21_exp_ < 0) {
      s21_exp_ = s21_exp_ * (-1L);
      FLAG = 1;
    }
    long double tmp = s21_exp_;
    if (tmp < 0) tmp = tmp * (-1);
    tmp = s21_floor(tmp);
    long double tmp2;
    tmp2 = s21_exp_ - tmp;
    if (s21_base < 0 && tmp2 > 0)
      result = S21_NAN;
    else {
      for (int i = 0; i < tmp; i++) {
        result = result * s21_base;
      }
      if (s21_base > 0) result1 = s21_exp(tmp2 * s21_log(s21_base));
      result = result * result1;
      if (FLAG == 1) result = 1L / result;
    }
  }
  return result;
}
