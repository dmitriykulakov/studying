#include "../s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  int s21_zero1 = s21_decimal_is_zero(value_1);
  int s21_zero2 = s21_decimal_is_zero(value_2);
  if (s21_zero1 == 1 && s21_zero2 == 1)
    result = 1;
  else if (!((s21_zero1 == 1 && s21_zero2 == 0) ||
             (s21_zero1 == 0 && s21_zero2 == 1) ||
             ((value_1.bits[3] & MINUS_32) && !(value_2.bits[3] & MINUS_32)) ||
             (!(value_1.bits[3] & MINUS_32) && (value_2.bits[3] & MINUS_32)))) {
    s21_decimal_extra work_value_1 = {0};
    s21_decimal_extra work_value_2 = {0};
    s21_decimal_convert_to_64bit(value_1, &work_value_1);
    s21_decimal_convert_to_64bit(value_2, &work_value_2);
    if (work_value_1.scale != work_value_2.scale) {
      s21_scale_normalization(&work_value_1, &work_value_2);
    }
    int FLAG = 1;
    for (int i = 6; i >= 0 && FLAG == 1; i--) {
      if (work_value_1.work_int[i] != work_value_2.work_int[i]) FLAG = 0;
    }
    result = FLAG;
  }
  return result;
}