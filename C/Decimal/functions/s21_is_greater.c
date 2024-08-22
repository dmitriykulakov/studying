#include "../s21_decimal.h"

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int result = 0, FLAG = 0;
  if (s21_is_not_equal(value_1, value_2)) {
    s21_decimal_extra work_value_1 = {0};
    s21_decimal_extra work_value_2 = {0};
    s21_decimal_convert_to_64bit(value_1, &work_value_1);
    s21_decimal_convert_to_64bit(value_2, &work_value_2);
    int s21_zero1 = s21_decimal_is_zero(value_1);
    int s21_zero2 = s21_decimal_is_zero(value_2);
    if (work_value_1.scale != work_value_2.scale) {
      s21_scale_normalization(&work_value_1, &work_value_2);
    }
    if ((s21_zero1 == 1 && !(value_2.bits[3] & MINUS_32)) ||
        ((value_1.bits[3] & MINUS_32) && !(value_2.bits[3] & MINUS_32)) ||
        ((value_1.bits[3] & MINUS_32) && s21_zero2))
      result = 0;
    else if ((!(value_1.bits[3] & MINUS_32) && s21_zero2) ||
             (s21_zero1 && (value_2.bits[3] & MINUS_32)) ||
             (!(value_1.bits[3] & MINUS_32) && (value_2.bits[3] & MINUS_32)))
      result = 1;
    else if ((value_1.bits[3] & MINUS_32) && (value_2.bits[3] & MINUS_32)) {
      for (int i = 6; i >= 0 && result == 0 && FLAG == 0; i--) {
        if (work_value_1.work_int[i] < work_value_2.work_int[i]) result = 1;
        if (work_value_1.work_int[i] != work_value_2.work_int[i]) FLAG = 1;
      }
    } else if (!(value_1.bits[3] & MINUS_32) && !(value_2.bits[3] & MINUS_32)) {
      for (int i = 6; i >= 0 && result == 0 && FLAG == 0; i--) {
        if (work_value_1.work_int[i] > work_value_2.work_int[i]) result = 1;
        if (work_value_1.work_int[i] != work_value_2.work_int[i]) FLAG = 1;
      }
    }
  }
  return result;
}