#include "s21_test.h"

START_TEST(sprintf_other_1) {
  char s1[128] = "", s2[128] = "";
  char str[20] = "win project";
  int res1 = 0, res2 = 0;
  int num1 = 0, num2 = 0;

  res1 = s21_sprintf(s1, "%s %n", str, &num1);
  res2 = sprintf(s2, "%s %n", str, &num2);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(num1, num2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_other_2) {
  char s1[128] = "", s2[128] = "";
  int num = 2376;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "31%% %d", num);
  res2 = sprintf(s2, "31%% %d", num);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_other_3) {
  char s1[128] = "";
  int num = 14;

  s21_sprintf(s1, "%r", num);
}
END_TEST

START_TEST(sprintf_other_4) {
  char s1[128] = "", s2[128] = "";
  int num = 2376;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "%p", &num);
  res2 = sprintf(s2, "%p", &num);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sprintf_other_5) {
  char s1[128] = "", s2[128] = "";
  int num = 2376;
  int res1 = 0, res2 = 0;

  res1 = s21_sprintf(s1, "31%% %d", num);
  res2 = sprintf(s2, "31%% %d", num);

  ck_assert_pstr_eq(s1, s2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

Suite *s21_sprintf_test_other(void) {
  Suite *suite = suite_create("s21_sprintf_other_test");
  TCase *tc = tcase_create("s21_sprintf_other_tc");

  tcase_add_test(tc, sprintf_other_1);
  tcase_add_test(tc, sprintf_other_2);
  tcase_add_test(tc, sprintf_other_3);
  tcase_add_test(tc, sprintf_other_4);
  tcase_add_test(tc, sprintf_other_5);

  suite_add_tcase(suite, tc);
  return suite;
}