#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int s21_from_int_to_decimal = RETURN_VALUE_1;

  if (dst != NULL) {
    s21_decimal_fill_zero(dst);
    dst->bits[0] = abs(src);
    if (src < 0) {
      dst->bits[3] |= MINUS_32;
    }
    s21_from_int_to_decimal = RETURN_VALUE_0;
  }

  return s21_from_int_to_decimal;
}