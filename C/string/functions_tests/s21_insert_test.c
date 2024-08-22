#include "s21_test.h"

START_TEST(insert_1) {
  char s1[] = "gang gang gang";
  char s2[] = " hello, block!";
  char *s3 = {0};
  char *s4 = {0};
  s3 = "gang gang gang hello, block!";
  s4 = s21_insert(s1, s2, 14);
  ck_assert_str_eq(s3, s4);
  if (s4) free(s4);
}
END_TEST

START_TEST(insert_2) {
  char s1[] = "";
  char s2[] = "";
  char *s3 = {0};
  char *s4 = {0};
  s3 = "";
  s4 = s21_insert(s1, s2, 0);
  ck_assert_str_eq(s3, s4);
  if (s4) free(s4);
}
END_TEST

START_TEST(insert_3) {
  char s1[] = "gang gang gang";
  char s2[] = " hello, block!";
  char *s3 = {0};
  char *s4 = {0};
  s3 = S21_NULL;
  s4 = s21_insert(s1, s2, 120);
  ck_assert(s3 == s4);
  if (s4) free(s4);
}
END_TEST

START_TEST(insert_4) {
  char s2[] = " hello, block!";
  char *s3 = {0};
  char *s4 = {0};
  s3 = S21_NULL;
  s4 = s21_insert(S21_NULL, s2, 120);
  ck_assert(s3 == s4);
  if (s4) free(s4);
}
END_TEST

START_TEST(insert_5) {
  char s1[] = "gang gang gang FREE YSL";
  char s2[] = " hello, block!";
  char *s3 = {0};
  char *s4 = {0};
  s3 = "gang gang gang hello, block! FREE YSL";
  s4 = s21_insert(s1, s2, 14);
  ck_assert_str_eq(s3, s4);
  if (s4) free(s4);
}
END_TEST

Suite *s21_insert_test(void) {
  Suite *s = suite_create("s21_insert_test");
  TCase *tc = tcase_create("insert_tc");

  tcase_add_test(tc, insert_1);
  tcase_add_test(tc, insert_2);
  tcase_add_test(tc, insert_3);
  tcase_add_test(tc, insert_4);
  tcase_add_test(tc, insert_5);

  suite_add_tcase(s, tc);
  return s;
}