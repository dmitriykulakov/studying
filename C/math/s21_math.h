#ifndef S21_MATH_H_
#define S21_MATH_H_

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>

#define S21_NAN (0.0) / (0.0)
#define S21_IS_NAN(x) ((x) != (x))
#define S21_INF_P (1.0) / (+0.0)
#define S21_IS_INF_P(x) ((x) == S21_INF_P)
#define S21_INF_N (1.0) / (-0.0)
#define S21_IS_INF_N(x) ((x) == S21_INF_N)

#define S21_PI 3.141592653589793238462643383279502884L
#define S21_PI_2 1.570796326794896619231321691639751442L
#define S21_PI_4 0.785398163397448309615660845819875721L
#define S21_E 2.718281828459045235360287471352662498L

#define EPS 1E-24L

int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_sin(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);
long double s21_fmod(double x, double y);

#endif
