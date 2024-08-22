#include "../s21_decimal.h"

int s21_decimal_is_zero(s21_decimal value) {
  int s21_decimal_is_zero = 1;
  for (int i = 0; (i < 3) && (s21_decimal_is_zero == 1); i++) {
    if (value.bits[i] != 0) {
      s21_decimal_is_zero = 0;
    }
  }
  return s21_decimal_is_zero;
}

void s21_decimal_fill_zero(s21_decimal *value) {
  if (value != NULL) {
    for (int i = 0; i < 4; i++) {
      value->bits[i] = ZERO_32;
    }
  }
  return;
}

void s21_decimal_convert_to_64bit(s21_decimal value,
                                  s21_decimal_extra *value_extra) {
  if (value_extra != NULL) {
    value_extra->sign = (value.bits[3] & MINUS_32) >> 31;
    value_extra->scale = (value.bits[3] & SC_32) >> 16;
    for (int i = 0; i < 3; i++) {
      value_extra->work_int[i] = value.bits[i] & MAXBITE_32;
    }
    for (int i = 3; i < 7; i++) {
      value_extra->work_int[i] = ZERO_64;
    }
  }
  return;
}

void s21_decimal_convert_to_32bit(s21_decimal *value,
                                  s21_decimal_extra value_extra) {
  if (value != NULL) {
    value->bits[3] = ZERO_32;
    value->bits[3] = (value_extra.sign << 31) & MINUS_32;
    value->bits[3] |= (value_extra.scale << 16) & SC_64;
    for (int i = 0; i < 3; i++) {
      value->bits[i] = value_extra.work_int[i] & MAXBITE_64;
    }
  }
  return;
}

int s21_decimal_getoverflow(s21_decimal_extra *value_extra) {
  int s21_getoverflow = RETURN_VALUE_1;
  if (value_extra != NULL) {
    int overflow = 0;
    for (int i = 0; i < 7; i++) {
      value_extra->work_int[i] = value_extra->work_int[i] + overflow;
      overflow = value_extra->work_int[i] >> 32;
      value_extra->work_int[i] = value_extra->work_int[i] & MAXBITE_64;
    }
    if (overflow == 0) {
      s21_getoverflow = RETURN_VALUE_0;
    }
  }
  return s21_getoverflow;
}

int s21_decimal_point_shift_right(s21_decimal_extra *value_extra) {
  int s21_point_shift_right = 0;
  if (value_extra != NULL) {
    long int remainder = 0;
    for (int i = 6; i >= 0; i--) {
      value_extra->work_int[i] += (remainder << 32);
      remainder = value_extra->work_int[i] % 10;
      value_extra->work_int[i] /= 10;
    }
    value_extra->scale--;
    s21_point_shift_right = remainder;
  }
  return s21_point_shift_right;
}

void s21_scale_normalization(s21_decimal_extra *value_1,
                             s21_decimal_extra *value_2) {
  if (value_1->scale > value_2->scale) {
    for (; value_1->scale != value_2->scale; (value_2->scale)++) {
      for (int i = 0; i < 7; i++) {
        value_2->work_int[i] = value_2->work_int[i] * 10;
      }
      s21_decimal_getoverflow(value_2);
    }
  }
  if (value_1->scale < value_2->scale) {
    for (; value_1->scale != value_2->scale; (value_1->scale)++) {
      for (int i = 0; i < 7; i++) {
        value_1->work_int[i] = value_1->work_int[i] * 10;
      }
      s21_decimal_getoverflow(value_1);
    }
  }
}

int s21_digit_normalization(s21_decimal_extra *value) {
  int result = 0, remainder_FLAG = 0, remainder_count = 0;
  uint64_t remainder = 0;
  for (int i = 6; i > 2 && result == 0; i--) {
    for (; (value->work_int[i] != 0 || value->scale > 28) && result == 0;
         (value->scale)--) {
      if (value->scale > 0) {
        remainder = 0;
        for (int j = i; j >= 0; j--) {
          value->work_int[j] = value->work_int[j] + (remainder << 32);
          remainder = value->work_int[j] % 10;
          value->work_int[j] = value->work_int[j] / (int)10;
        }
        if (remainder > 0 && remainder_count == 1) remainder_FLAG = 1;
        if (remainder > 0) remainder_count = 1;
      } else {
        result = 1;
        (value->scale)++;
      }
    }
  }
  if (result == 0) {
    if ((remainder > 5) || (remainder == 5 && remainder_FLAG == 1)) {
      (value->work_int[0])++;
      s21_decimal_getoverflow(value);
      s21_digit_normalization(value);
    } else if (remainder == 5 && remainder_FLAG == 0) {
      if (value->work_int[0] % 2 == 1) {
        value->work_int[0]++;
      }
    }
  }

  return result;
}