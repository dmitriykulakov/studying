#include "s21_test.h"

START_TEST(atoi_1) {
  char s1[] = "123";
  char s2[] = "123";
  ck_assert_int_eq(atoi(s1), s21_atoi(s2));
}
END_TEST

START_TEST(atoi_3) {
  char s1[] = "-123";
  char s2[] = "-123";
  ck_assert_int_eq(atoi(s1), s21_atoi(s2));
}
END_TEST

START_TEST(atoi_5) {
  char s1[] = "+123";
  char s2[] = "+123";
  ck_assert_int_eq(atoi(s1), s21_atoi(s2));
}
END_TEST

Suite *s21_atoi_test(void) {
  Suite *s = suite_create("s21_atoi_test");
  TCase *tc = tcase_create("atoi_tc");

  tcase_add_test(tc, atoi_1);
  tcase_add_test(tc, atoi_3);
  tcase_add_test(tc, atoi_5);

  suite_add_tcase(s, tc);
  return s;
}