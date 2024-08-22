#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int s21_from_decimal_to_float = RETURN_VALUE_1;

  if (dst != NULL) {
    *dst = 0.0;
    double dst_temp = 0.0;
    int decimal_scale = (src.bits[3] & SC_32) >> 16;
    int decimal_sign = (src.bits[3] & MINUS_32) >> 31;
    int bit_mask = 0x00000001;
    for (int i = 0; i < 3 * 32; i++) {
      int decimal_byte_num = i / 32;
      int decimal_bit_num = i % 32;
      int decimal_bit_value =
          (src.bits[decimal_byte_num] >> decimal_bit_num) & bit_mask;
      if (decimal_bit_value == 1) {
        dst_temp += pow(2, i);
      }
    }
    while (decimal_scale != 0) {
      dst_temp /= 10;
      decimal_scale--;
    }
    if (decimal_sign == 1) {
      dst_temp *= -1.0;
    }
    *dst = (float)dst_temp;
    s21_from_decimal_to_float = RETURN_VALUE_0;
  }

  return s21_from_decimal_to_float;
}