#include "s21_test.h"

START_TEST(sprintf_float_1) {
  char s1[128] = "", s2[128] = "";
  double num = 12e3;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%e", num);
  res2 = sprintf(s2, "%e", num);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_float_2) {
  char s1[128] = "", s2[128] = "";
  double num = 12e3;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%E", num);
  res2 = sprintf(s2, "%E", num);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_float_3) {
  char s1[128] = "", s2[128] = "";
  double num = 12.34;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%f", num);
  res2 = sprintf(s2, "%f", num);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_float_4) {
  char s1[128] = "", s2[128] = "";
  long double num = 10.45678;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%Lf", num);
  res2 = sprintf(s2, "%Lf", num);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_float_5) {
  char s1[128] = "", s2[128] = "";
  double num1 = NAN;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%f", num1);
  res2 = sprintf(s2, "%f", num1);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_float_6) {
  char s1[128] = "", s2[128] = "";
  double num1 = INFINITY;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%f", num1);
  res2 = sprintf(s2, "%f", num1);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_float_7) {
  char s1[128] = "", s2[128] = "";
  double num1 = 1234321, num2 = 6999;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%#f %#E", num1, num2);
  res2 = sprintf(s2, "%#f %#E", num1, num2);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_float_8) {
  char s1[128] = "", s2[128] = "";
  double num1 = NAN;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%f", num1);
  res2 = sprintf(s2, "%f", num1);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_float_9) {
  char s1[128] = "", s2[128] = "";
  double num1 = INFINITY;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%f", num1);
  res2 = sprintf(s2, "%f", num1);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

Suite *s21_sprintf_test_float(void) {
  Suite *suite = suite_create("s21_sprintf_float_test");
  TCase *tc = tcase_create("s21_sprintf_float_tc");

  tcase_add_test(tc, sprintf_float_1);
  tcase_add_test(tc, sprintf_float_2);
  tcase_add_test(tc, sprintf_float_3);
  tcase_add_test(tc, sprintf_float_4);
  tcase_add_test(tc, sprintf_float_5);
  tcase_add_test(tc, sprintf_float_6);
  tcase_add_test(tc, sprintf_float_7);
  tcase_add_test(tc, sprintf_float_8);
  tcase_add_test(tc, sprintf_float_9);

  suite_add_tcase(suite, tc);
  return suite;
}