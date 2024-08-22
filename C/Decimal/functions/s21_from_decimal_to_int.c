#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int s21_from_decimal_to_int = RETURN_VALUE_1;

  if (dst != NULL) {
    s21_decimal value;
    s21_decimal_extra value_extra;
    s21_decimal_convert_to_64bit(src, &value_extra);
    while (value_extra.scale != 0) {
      s21_decimal_point_shift_right(&value_extra);
    }
    s21_decimal_convert_to_32bit(&value, value_extra);

    if ((value.bits[1] == 0) && (value.bits[2] == 0)) {
      int decimal_sign = (value.bits[3] & MINUS_32) >> 31;
      // INT_MAX = 2147483647
      // INT_MIN = (-INT_MAX - 1)
      if (((decimal_sign == 0) &&
           ((unsigned int)value.bits[0] <= (unsigned int)INT_MAX)) ||
          ((decimal_sign == 1) &&
           ((unsigned int)value.bits[0] <= (unsigned int)INT_MAX + 1))) {
        if (decimal_sign == 0) {
          *dst = value.bits[0];
        } else {
          *dst = -1 * value.bits[0];
        }
        s21_from_decimal_to_int = RETURN_VALUE_0;
      } else {
        s21_from_decimal_to_int = RETURN_VALUE_1;
      }
    } else {
      s21_from_decimal_to_int = RETURN_VALUE_1;
    }
  }

  return s21_from_decimal_to_int;
}