#include "s21_test.h"

START_TEST(sscanf_o_1) {
  char format[] = "%o";
  char str[] = "777";
  unsigned int x1 = 0, x2 = 0;

  int res1 = s21_sscanf(str, format, &x1);
  int res2 = sscanf(str, format, &x2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
}
END_TEST

START_TEST(sscanf_o_2) {
  char format[] = "%o %o";
  char str[] = "123 52";
  unsigned int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, format, &x1, &x3);
  int res2 = sscanf(str, format, &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_o_3) {
  char format[] = "%o %o";
  char str[] = "12a3 5b2";
  unsigned int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, format, &x1, &x3);
  int res2 = sscanf(str, format, &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_o_4) {
  char format[] = "%o %o";
  char str[] = "12i3 5j2";
  unsigned int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, format, &x1, &x3);
  int res2 = sscanf(str, format, &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_o_5) {
  char format[] = "%o %o";
  char str[] = "+12i3 +5j2";
  unsigned int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, format, &x1, &x3);
  int res2 = sscanf(str, format, &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_o_6) {
  char format[] = "%o %o";
  char str[] = "+012i3 +05j2";
  unsigned int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, format, &x1, &x3);
  int res2 = sscanf(str, format, &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_o_7) {
  char format[] = "%1o %1o";
  char str[] = "+012i3 +05j2";
  unsigned int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, format, &x1, &x3);
  int res2 = sscanf(str, format, &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_o_8) {
  char format[] = "%1o %1o";
  char str[] = "+012i3 bc";
  unsigned int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, format, &x1, &x3);
  int res2 = sscanf(str, format, &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

START_TEST(sscanf_o_9) {
  char format[] = "%1o %2o";
  char str[] = "2i3 bCc";
  unsigned int x1 = 0, x2 = 0, x3 = 0, x4 = 0;

  int res1 = s21_sscanf(str, format, &x1, &x3);
  int res2 = sscanf(str, format, &x2, &x4);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
}
END_TEST

Suite *s21_sscanf_test_o(void) {
  Suite *suite = suite_create("s21_sscanf_test_o");
  TCase *tc = tcase_create("s21_sscanf_o_tc");

  tcase_add_test(tc, sscanf_o_1);
  tcase_add_test(tc, sscanf_o_2);
  tcase_add_test(tc, sscanf_o_3);
  tcase_add_test(tc, sscanf_o_4);
  tcase_add_test(tc, sscanf_o_5);
  tcase_add_test(tc, sscanf_o_6);
  tcase_add_test(tc, sscanf_o_7);
  tcase_add_test(tc, sscanf_o_8);
  tcase_add_test(tc, sscanf_o_9);

  suite_add_tcase(suite, tc);
  return suite;
}