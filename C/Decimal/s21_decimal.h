#ifndef S21_DECIMAL_H_
#define S21_DECIMAL_H_

#define _POSIX_C_SOURCE 200809L

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int bits[4];
} s21_decimal;

typedef struct {
  int sign;
  uint64_t scale;
  uint64_t work_int[7];
} s21_decimal_extra;

#define MINUS_32 0x80000000  // 10000000 00000000 00000000 00000000
#define MINUS_64 0x0000000080000000
#define SC_32 0x00ff0000  // 00000000 11111111 00000000 00000000
#define SC_64 0x0000000000ff0000
#define MAXBITE_32 0xffffffff
#define MAXBITE_64 0x00000000ffffffff
#define ZERO_32 0x00000000
#define ZERO_64 0x0000000000000000

#define RETURN_VALUE_0 0
#define RETURN_VALUE_1 1
#define RETURN_VALUE_2 2
#define RETURN_VALUE_3 3

#define MAX_FLOAT_TO_DECIMAL powf(2.0, 96)  // 79228162514264337593543950335
#define MIN_FLOAT_TO_DECIMAL 1E-28
#define FLOAT_ERROR 1E-12

#define S21_NAN (0.0) / (0.0)
#define S21_IS_NAN(x) ((x) != (x))
#define S21_INF_P (1.0) / (+0.0)
#define S21_IS_INF_P(x) ((x) == S21_INF_P)
#define S21_INF_N (1.0) / (-0.0)
#define S21_IS_INF_N(x) ((x) == S21_INF_N)

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

int s21_decimal_is_zero(s21_decimal value);
void s21_decimal_fill_zero(s21_decimal *value);
void s21_decimal_convert_to_64bit(s21_decimal value,
                                  s21_decimal_extra *value_extra);
void s21_decimal_convert_to_32bit(s21_decimal *value,
                                  s21_decimal_extra value_extra);
int s21_decimal_getoverflow(s21_decimal_extra *value_extra);
int s21_decimal_point_shift_right(s21_decimal_extra *value_extra);
void s21_scale_normalization(s21_decimal_extra *value_1,
                             s21_decimal_extra *value_2);
int s21_digit_normalization(s21_decimal_extra *value);

void s21_sub_function(s21_decimal_extra value_1, s21_decimal_extra value_2,
                      s21_decimal_extra *result);
void s21_zero_for_div(s21_decimal *value);
void s21_function_for_div(s21_decimal_extra *work_value_1,
                          s21_decimal_extra work_value_2);
void s21_normalization_for_div(s21_decimal_extra *work_value_1,
                               s21_decimal_extra *work_value_2);

#endif