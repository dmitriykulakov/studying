#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int s21_round = RETURN_VALUE_1;

  if (result != NULL) {
    s21_decimal_extra value_extra;
    if (s21_decimal_is_zero(value) == 1) {
      s21_decimal_fill_zero(result);
    } else {
      s21_decimal_convert_to_64bit(value, &value_extra);
      int remainder = 0;
      while (value_extra.scale != 0) {
        remainder = s21_decimal_point_shift_right(&value_extra);
      }
      if (remainder >= 5) {
        value_extra.work_int[0] += 1;
      }
      s21_decimal_getoverflow(&value_extra);
      s21_decimal_convert_to_32bit(result, value_extra);
    }
    s21_round = RETURN_VALUE_0;
  }

  return s21_round;
}