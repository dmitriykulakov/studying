#include "../s21_decimal.h"

void s21_decimal_set_bits(double src_temp, s21_decimal *dst, int decimal_sign,
                          int decimal_scale);

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int s21_from_float_to_decimal = RETURN_VALUE_1;

  if (dst != NULL) {
    if (S21_IS_NAN(src) == 1) {
      s21_from_float_to_decimal = RETURN_VALUE_1;
    } else if ((S21_IS_INF_P(src) == 1) || (S21_IS_INF_N(src) == 1)) {
      s21_from_float_to_decimal = RETURN_VALUE_1;
    } else if (fabs(src) > MAX_FLOAT_TO_DECIMAL) {
      s21_from_float_to_decimal = RETURN_VALUE_1;
    } else if (fabs(src) < MIN_FLOAT_TO_DECIMAL) {
      s21_decimal_fill_zero(dst);
      s21_from_float_to_decimal = RETURN_VALUE_1;
    } else {
      double src_temp = (double)src;
      int decimal_sign = (src < 0.0) ? 1 : 0;
      int decimal_scale = 0;
      src_temp = fabs(src_temp);

      if (src_temp < 1e+7) {
        while ((src_temp < 1e+6) && (decimal_scale < 28)) {
          src_temp *= 10.0;
          decimal_scale++;
        }
        src_temp = roundf(src_temp);
      } else if (src_temp >= 1e+7) {
        int count_tmp = 0;
        while (src_temp >= 1e+7) {
          src_temp /= 10.0;
          count_tmp++;
        }
        src_temp = roundf(src_temp);
        if (src_temp * pow(10, count_tmp) > MAX_FLOAT_TO_DECIMAL) {
          src_temp -= 1.0;
        }
        src_temp *= pow(10, count_tmp);
      }
      s21_decimal_fill_zero(dst);
      s21_decimal_set_bits(src_temp, dst, decimal_sign, decimal_scale);
      s21_from_float_to_decimal = RETURN_VALUE_0;
    }
  }

  return s21_from_float_to_decimal;
}

void s21_decimal_set_bits(double src_temp, s21_decimal *dst, int decimal_sign,
                          int decimal_scale) {
  if (dst != NULL) {
    if (decimal_sign == 1) {
      dst->bits[3] |= MINUS_32;
    }
    dst->bits[3] |= (decimal_scale << 16) & SC_32;
    double src_temp_div = src_temp;
    double src_temp_rem = 0.0;
    int decimal_bit_num_max = 0;
    while (src_temp_div > 0) {
      src_temp_div = floor(src_temp_div / 2.0);
      decimal_bit_num_max++;
    }
    src_temp_div = src_temp;
    for (int i = 0; i < decimal_bit_num_max; i++) {
      int decimal_byte_num = i / 32;
      int decimal_bit_num = i % 32;
      src_temp_rem = fmod(src_temp_div, 2.0);
      src_temp_div = floor(src_temp_div / 2.0);
      if (fabs(src_temp_rem - 1.0) < 1e-6) {
        dst->bits[decimal_byte_num] |= 1 << decimal_bit_num;
      }
    }
  }
  return;
}