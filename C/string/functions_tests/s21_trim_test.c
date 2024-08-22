#include "s21_test.h"

START_TEST(trim_1) {
  char s1[] = " gang ";
  char s2[] = " ";
  char *s3 = {0};
  char *s4 = {0};
  s3 = "gang";
  s4 = s21_trim(s1, s2);
  ck_assert_str_eq(s3, s4);
  if (s4) free(s4);
}
END_TEST

START_TEST(trim_2) {
  char s1[] = "      gang";
  char *s2 = " ";
  char *s3 = {0};
  char *s4 = {0};
  s3 = "gang";
  s4 = s21_trim(s1, s2);
  ck_assert_pstr_eq(s3, s4);
  if (s4) free(s4);
}
END_TEST

START_TEST(trim_3) {
  char s1[] = "gang  ";
  char *s2 = " ";
  char *s3 = {0};
  char *s4 = {0};
  s3 = "gang";
  s4 = s21_trim(s1, s2);
  ck_assert_pstr_eq(s3, s4);
  if (s4) free(s4);
}
END_TEST

START_TEST(trim_4) {
  char s1[] = "///i ooOO))";
  char *s2 = "/";
  char *s3 = {0};
  char *s4 = {0};
  s3 = "i ooOO))";
  s4 = s21_trim(s1, s2);
  ck_assert_pstr_eq(s3, s4);
  if (s4) free(s4);
}
END_TEST

START_TEST(trim_5) {
  char s1[] = "pull";
  char *s2 = "pull";
  char *s3 = {0};
  char *s4 = {0};
  s3 = "";
  s4 = s21_trim(s1, s2);
  ck_assert_pstr_eq(s3, s4);
  if (s4) free(s4);
}
END_TEST

START_TEST(trim_6) {
  char *s2 = "";
  char *s3 = {0};
  char *s4 = {0};
  s4 = s21_trim(S21_NULL, s2);
  ck_assert_pstr_eq(s3, S21_NULL);
  if (s4) free(s4);
}
END_TEST

START_TEST(trim_7) {
  char s1[] = " gang ";
  char s2[] = "p";
  char *s3 = {0};
  char *s4 = {0};
  s3 = " gang ";
  s4 = s21_trim(s1, s2);
  ck_assert_str_eq(s3, s4);
  if (s4) free(s4);
}
END_TEST

START_TEST(trim_8) {
  char s2[] = "pull";
  char *s4 = {0};
  s4 = s21_trim(S21_NULL, s2);
  ck_assert(S21_NULL == s4);
  if (s4) free(s4);
}
END_TEST

Suite *s21_trim_test(void) {
  Suite *s = suite_create("s21_trim_test");
  TCase *tc = tcase_create("trim_tc");

  tcase_add_test(tc, trim_1);
  tcase_add_test(tc, trim_2);
  tcase_add_test(tc, trim_3);
  tcase_add_test(tc, trim_4);
  tcase_add_test(tc, trim_5);
  tcase_add_test(tc, trim_6);
  tcase_add_test(tc, trim_7);
  tcase_add_test(tc, trim_8);
  suite_add_tcase(s, tc);
  return s;
}