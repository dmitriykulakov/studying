#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int function_result = 0;
  int s21_zero1 = s21_decimal_is_zero(value_1);
  int s21_zero2 = s21_decimal_is_zero(value_2);
  if (s21_zero1 || s21_zero2) {
    for (int i = 0; i < 4; i++) {
      result->bits[i] = result->bits[i] & ZERO_32;
    }
  } else {
    s21_decimal_extra work_value_1 = {0};
    s21_decimal_extra work_value_2 = {0};
    s21_decimal_extra work_result = {0};
    if (((value_1.bits[3] & MINUS_32) && !(value_2.bits[3] & MINUS_32)) ||
        (!(value_1.bits[3] & MINUS_32) && (value_2.bits[3] & MINUS_32))) {
      work_result.sign = 1;
    }
    s21_decimal_convert_to_64bit(value_1, &work_value_1);
    s21_decimal_convert_to_64bit(value_2, &work_value_2);
    work_result.work_int[0] =
        work_value_1.work_int[0] * work_value_2.work_int[0];
    work_result.work_int[1] =
        work_value_1.work_int[1] * work_value_2.work_int[0] +
        work_value_1.work_int[0] * work_value_2.work_int[1];
    work_result.work_int[2] =
        work_value_1.work_int[0] * work_value_2.work_int[2] +
        work_value_1.work_int[1] * work_value_2.work_int[1] +
        work_value_1.work_int[2] * work_value_2.work_int[0];
    work_result.work_int[3] =
        work_value_1.work_int[1] * work_value_2.work_int[2] +
        work_value_1.work_int[2] * work_value_2.work_int[1];
    work_result.work_int[4] =
        work_value_1.work_int[2] * work_value_2.work_int[2];
    work_result.scale = work_value_1.scale + work_value_2.scale;
    s21_decimal_getoverflow(&work_result);
    function_result = s21_digit_normalization(&work_result);
    s21_decimal_convert_to_32bit(result, work_result);
    if (function_result == 1 && work_result.sign == 1) {
      function_result = 2;
    }
  }
  return function_result;
}