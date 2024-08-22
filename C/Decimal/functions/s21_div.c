#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int function_result = 0, FLAG = 0, counter = 0, digits = 0;
  int s21_zero1 = s21_decimal_is_zero(value_1);
  int s21_zero2 = s21_decimal_is_zero(value_2);
  if (s21_zero2)
    function_result = 3;
  else if (s21_zero1) {
    s21_zero_for_div(result);
  } else {
    s21_decimal_extra work_value_1 = {0}, work_value_2 = {0}, work_result = {0};
    if (((value_1.bits[3] & MINUS_32) && !(value_2.bits[3] & MINUS_32)) ||
        (!(value_1.bits[3] & MINUS_32) && (value_2.bits[3] & MINUS_32)))
      work_result.sign = 1;
    s21_decimal_convert_to_64bit(value_1, &work_value_1);
    s21_decimal_convert_to_64bit(value_2, &work_value_2);
    s21_normalization_for_div(&work_value_1, &work_value_2);
    while (digits < 34) {
      FLAG = 0;
      for (int i = 4; i >= 0 && FLAG == 0; i--) {
        if (work_value_1.work_int[i] > work_value_2.work_int[i])
          FLAG = 2;
        else if (work_value_1.work_int[i] < work_value_2.work_int[i])
          FLAG = 1;
      }
      if (FLAG == 1) {
        for (int i = 0; i < 5; i++) {
          work_result.work_int[i] = work_result.work_int[i] * 10;
          work_value_1.work_int[i] = work_value_1.work_int[i] * 10;
        }
        if (counter > 0)
          work_result.work_int[0] = work_result.work_int[0] + counter;
        s21_decimal_getoverflow(&work_result);
        s21_decimal_getoverflow(&work_value_1);
        digits++;
        counter = 0;
      } else {
        s21_function_for_div(&work_value_1, work_value_2);
        counter++;
      }
    }
    if (33 + work_value_1.scale >= work_value_2.scale) {
      work_result.scale = 33 + work_value_1.scale - work_value_2.scale;
      function_result = s21_digit_normalization(&work_result);
      s21_decimal_convert_to_32bit(result, work_result);
    } else
      function_result = 1;
    if (function_result == 1 && work_result.sign == 1) function_result = 2;
  }
  return function_result;
}

void s21_zero_for_div(s21_decimal *value) {
  for (int i = 0; i < 4; i++) {
    value->bits[i] = value->bits[i] & ZERO_32;
  }
}

void s21_function_for_div(s21_decimal_extra *work_value_1,
                          s21_decimal_extra work_value_2) {
  for (int i = 0; i < 5; i++) {
    if (work_value_1->work_int[i] < work_value_2.work_int[i]) {
      (work_value_1->work_int[i + 1])--;
      work_value_1->work_int[i] = work_value_1->work_int[i] + (0x100000000);
    }
    work_value_1->work_int[i] =
        work_value_1->work_int[i] - work_value_2.work_int[i];
  }
}

void s21_normalization_for_div(s21_decimal_extra *work_value_1,
                               s21_decimal_extra *work_value_2) {
  for (; work_value_1->work_int[1] < 0x10000000; (work_value_1->scale)++) {
    for (int i = 0; i < 2; i++) {
      work_value_1->work_int[i] = work_value_1->work_int[i] * 10;
    }
    s21_decimal_getoverflow(work_value_1);
  }
  for (; work_value_2->work_int[2] < 0x10000000; (work_value_2->scale)++) {
    for (int i = 0; i < 3; i++) {
      work_value_2->work_int[i] = work_value_2->work_int[i] * 10;
    }
    s21_decimal_getoverflow(work_value_2);
  }
}
