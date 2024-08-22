#include "s21_test.h"

START_TEST(strtold_1) {
  char s2[] = "123.1233";

  ck_assert_ldouble_eq(strtold(s2, NULL), s21_strtold(s2));
}
END_TEST

START_TEST(strtold_2) {
  char s2[] = "0.5555555555555555";

  ck_assert_ldouble_eq(strtold(s2, NULL), s21_strtold(s2));
}
END_TEST

START_TEST(strtold_3) {
  char s2[] = "1999";
  ck_assert_ldouble_eq(strtold(s2, NULL), s21_strtold(s2));
}
END_TEST

Suite *s21_strtold_test(void) {
  Suite *s = suite_create("s21_strtold_test");
  TCase *tc = tcase_create("strtold_tc");

  tcase_add_test(tc, strtold_1);
  tcase_add_test(tc, strtold_2);
  tcase_add_test(tc, strtold_3);

  suite_add_tcase(s, tc);
  return s;
}