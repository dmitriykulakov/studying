#include "s21_test.h"

START_TEST(to_upper_1) {
  char s1[30] = "Hello, world!";
  char *s2 = s21_to_upper(s1);
  char s3[30] = "HELLO, WORLD!";
  ck_assert_pstr_eq(s3, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(to_upper_2) {
  char s1[30] = "111111111";
  char *s2 = s21_to_upper(s1);
  char s3[30] = "111111111";
  ck_assert_pstr_eq(s3, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(to_upper_3) {
  char s1[30] = "";
  char *s2 = s21_to_upper(s1);
  char s3[30] = "";
  ck_assert_pstr_eq(s3, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(to_upper_4) {
  char *s1 = S21_NULL;
  char *s2 = s21_to_upper(s1);
  char *s3 = S21_NULL;
  ck_assert_pstr_eq(s3, s2);
  if (s2) free(s2);
}
END_TEST

START_TEST(to_upper_5) {
  char s1[30] =
      "!;'/]}{"
      "}";
  char *s2 = s21_to_upper(s1);
  char s3[30] =
      "!;'/]}{"
      "}";
  ck_assert_pstr_eq(s3, s2);
  if (s2) free(s2);
}
END_TEST

Suite *s21_to_upper_test(void) {
  Suite *s = suite_create("s21_to_upper_test");
  TCase *tc = tcase_create("to_upper_tc");

  tcase_add_test(tc, to_upper_1);
  tcase_add_test(tc, to_upper_2);
  tcase_add_test(tc, to_upper_3);
  tcase_add_test(tc, to_upper_4);
  tcase_add_test(tc, to_upper_5);

  suite_add_tcase(s, tc);
  return s;
}