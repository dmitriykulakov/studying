#include "s21_test.h"

START_TEST(sscanf_float_1) {
  char format[] = "%f %f %f";
  char str[] = "123 +77 -52";
  float d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0, d6 = 0;

  int res1 = sscanf(str, format, &d1, &d3, &d5);
  int res2 = s21_sscanf(str, format, &d2, &d4, &d6);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(d3, d4);
  ck_assert_float_eq(d5, d6);
}
END_TEST

START_TEST(sscanf_float_2) {
  char format[] = "%f %f %f";
  char str[] = "123.00 +7.2357 -52.1254";
  float d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0, d6 = 0;

  int res1 = sscanf(str, format, &d1, &d3, &d5);
  int res2 = s21_sscanf(str, format, &d2, &d4, &d6);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(d3, d4);
  ck_assert_float_eq(d5, d6);
}
END_TEST

START_TEST(sscanf_float_3) {
  char format[] = "%fx %fik %f.tu";
  char str[] = "123.00x +7.2357in -52.1254.tu";
  float d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0, d6 = 0;

  int res1 = sscanf(str, format, &d1, &d3, &d5);
  int res2 = s21_sscanf(str, format, &d2, &d4, &d6);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(d3, d4);
  ck_assert_float_eq(d5, d6);
}
END_TEST

START_TEST(sscanf_float_4) {
  char format[] = "%f %f";
  char str[] = "INF nan";
  float d1 = 0, d2 = 0, d3 = 0, d4 = 0;

  int res1 = sscanf(str, format, &d1, &d3);
  int res2 = s21_sscanf(str, format, &d2, &d4);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_infinite(d2);
  ck_assert_float_nan(d4);
}
END_TEST

START_TEST(sscanf_float_5) {
  char format[] = "%f";
  char str[] = "  lol  ";
  float d1 = 0, d2 = 0;

  int res1 = sscanf(str, format, &d1);
  int res2 = s21_sscanf(str, format, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_float_6) {
  char format[] = "%f %f %f";
  char str[] = "123.41e3 77.2e-4 .52e+1 +123";
  float d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0, d6 = 0;

  int res1 = sscanf(str, format, &d1, &d3, &d5);
  int res2 = s21_sscanf(str, format, &d2, &d4, &d6);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(d3, d4);
  ck_assert_float_eq(d5, d6);
}
END_TEST

START_TEST(sscanf_float_7) {
  char format[] = "%1f %2f %3f";
  char str[] = "123.41e3 77.2e-4 .52e+1 +123";
  float d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0, d6 = 0;

  int res1 = sscanf(str, format, &d1, &d3, &d5);
  int res2 = s21_sscanf(str, format, &d2, &d4, &d6);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(d3, d4);
  ck_assert_float_eq(d5, d6);
}
END_TEST

START_TEST(sscanf_float_8) {
  char format[] = "%fr %7f p";
  char str[] = "76.5r 52.3ep4";
  float d1 = 0, d2 = 0, d3 = 0, d4 = 0;

  int res1 = sscanf(str, format, &d1, &d3);
  int res2 = s21_sscanf(str, format, &d2, &d4);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(d3, d4);
}
END_TEST

START_TEST(sscanf_float_9) {
  char format[] = "%3f %3f %4f %3ef";
  char str[] = "56 3. +234.e +15E3 -0.56e2";
  float d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0, d6 = 0, d7 = 0, d8 = 0;

  int res1 = sscanf(str, format, &d1, &d3, &d5, &d7);
  int res2 = s21_sscanf(str, format, &d2, &d4, &d6, &d8);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(d1, d2);
  ck_assert_float_eq(d3, d4);
  ck_assert_float_eq(d5, d6);
  ck_assert_float_eq(d7, d8);
}
END_TEST

Suite *s21_sscanf_test_float(void) {
  Suite *suite = suite_create("s21_sscanf_test_float");
  TCase *tc = tcase_create("s21_sscanf_float_tc");

  tcase_add_test(tc, sscanf_float_1);
  tcase_add_test(tc, sscanf_float_2);
  tcase_add_test(tc, sscanf_float_3);
  tcase_add_test(tc, sscanf_float_4);
  tcase_add_test(tc, sscanf_float_5);
  tcase_add_test(tc, sscanf_float_6);
  tcase_add_test(tc, sscanf_float_7);
  tcase_add_test(tc, sscanf_float_8);
  tcase_add_test(tc, sscanf_float_9);

  suite_add_tcase(suite, tc);
  return suite;
}