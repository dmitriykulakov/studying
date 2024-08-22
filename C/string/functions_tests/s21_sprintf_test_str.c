#include "s21_test.h"

START_TEST(sprintf_str_1) {
  char s1[128] = "", s2[128] = "";
  char symbol = 'q';
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%c", symbol);
  res2 = sprintf(s2, "%c", symbol);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_str_2) {
  char s1[128] = "", s2[128] = "";
  char str[20] = "qewrt.q";
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%s", str);
  res2 = sprintf(s2, "%s", str);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_str_3) {
  char s1[128] = "", s2[128] = "";
  char str[20] = "Go in window";
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%*s", 15, str);
  res2 = sprintf(s2, "%*s", 15, str);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

Suite *s21_sprintf_test_str(void) {
  Suite *suite = suite_create("s21_sprintf_str_test");
  TCase *tc = tcase_create("s21_sprintf_str_tc");

  tcase_add_test(tc, sprintf_str_1);
  tcase_add_test(tc, sprintf_str_2);
  tcase_add_test(tc, sprintf_str_3);

  suite_add_tcase(suite, tc);
  return suite;
}