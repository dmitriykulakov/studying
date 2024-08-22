#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int function_result = 0;
  int s21_zero1 = s21_decimal_is_zero(value_1);
  int s21_zero2 = s21_decimal_is_zero(value_2);
  s21_decimal value_negate_1 = {0};
  if (s21_is_equal(value_1, value_2)) {
    for (int i = 0; i < 4; i++) {
      result->bits[i] = result->bits[i] & ZERO_32;
    }
  } else if (s21_zero1) {
    s21_negate(value_2, &value_negate_1);
    *result = value_negate_1;
  } else if (s21_zero2)
    *result = value_1;
  else if ((value_1.bits[3] & MINUS_32) && (value_2.bits[3] & MINUS_32)) {
    s21_decimal value_negate_2 = {0};
    s21_negate(value_1, &value_negate_1);
    s21_negate(value_2, &value_negate_2);
    function_result = s21_sub(value_negate_2, value_negate_1, result);
  } else if (!(value_1.bits[3] & MINUS_32) && !(value_2.bits[3] & MINUS_32)) {
    s21_decimal_extra work_value_1 = {0};
    s21_decimal_extra work_value_2 = {0};
    s21_decimal_extra work_result = {0};
    s21_decimal_convert_to_64bit(value_1, &work_value_1);
    s21_decimal_convert_to_64bit(value_2, &work_value_2);
    if (work_value_1.scale != work_value_2.scale) {
      s21_scale_normalization(&work_value_1, &work_value_2);
    }
    work_result.scale = work_value_1.scale;
    if (s21_is_greater(value_2, value_1)) {
      work_result.sign = 1;
      s21_sub_function(work_value_2, work_value_1, &work_result);
    } else {
      s21_sub_function(work_value_1, work_value_2, &work_result);
    }
    s21_decimal_getoverflow(&work_result);
    function_result = s21_digit_normalization(&work_result);
    s21_decimal_convert_to_32bit(result, work_result);
    if (function_result == 1 && work_result.sign == 1) function_result = 2;
  } else if (value_1.bits[3] & MINUS_32 || value_2.bits[3] & MINUS_32) {
    s21_negate(value_2, &value_negate_1);
    function_result = s21_add(value_1, value_negate_1, result);
  }
  return function_result;
}

void s21_sub_function(s21_decimal_extra value_1, s21_decimal_extra value_2,
                      s21_decimal_extra *result) {
  for (int i = 0; i < 7; i++) {
    if (value_1.work_int[i] < value_2.work_int[i]) {
      (value_1.work_int[i + 1])--;
      value_1.work_int[i] = value_1.work_int[i] + (0x100000000);
    }
    result->work_int[i] = value_1.work_int[i] - value_2.work_int[i];
  }
}