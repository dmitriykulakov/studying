#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int s21_negate = RETURN_VALUE_1;

  if (result != NULL) {
    if (s21_decimal_is_zero(value) == 1) {
      s21_decimal_fill_zero(result);
    } else {
      int scale = 0;
      for (int i = 0; i < 4; i++) {
        result->bits[i] = value.bits[i];
      }
      scale = (result->bits[3] & SC_32) >> 16;
      result->bits[3] ^= MINUS_32;
      result->bits[3] &= MINUS_32;
      result->bits[3] |= (scale << 16) & SC_32;
    }
    s21_negate = RETURN_VALUE_0;
  }

  return s21_negate;
}