#include "s21_test.h"

START_TEST(sscanf_char_1) {
  char format[] = "%c";
  char str[] = "\n \n \n \t \t 123 \n \n \t";
  char c1, c2;

  int res1 = sscanf(str, format, &c1);

  int res2 = s21_sscanf(str, format, &c2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(sscanf_char_2) {
  char format[] = "%c%c";
  char str[] = "\n \n \n \t \t 123 \n \n \t";
  char c1, c2, c3, c4;
  int res1 = sscanf(str, format, &c1, &c3);
  int res2 = s21_sscanf(str, format, &c2, &c4);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(c3, c4);
}
END_TEST

START_TEST(sscanf_char_3) {
  char format[] = "%c %c";
  char str[] = "\n \n \n \t \t 123 \n \n \t";
  char c1, c2, c3, c4;

  int res1 = sscanf(str, format, &c1, &c3);
  int res2 = s21_sscanf(str, format, &c2, &c4);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(c3, c4);
}
END_TEST

START_TEST(sscanf_char_4) {
  char format[] = "%c \t%c";
  char str[] = "\n \n \n \t \t 123 \n \n \t";
  char c1, c2, c3, c4;

  int res1 = sscanf(str, format, &c1, &c3);
  int res2 = s21_sscanf(str, format, &c2, &c4);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(c3, c4);
}
END_TEST

START_TEST(sscanf_char_5) {
  char format[] = "%c\t%c";
  char str[] = "\n \n \n \t \t 123 \n \n \t";
  char c1, c2, c3, c4;

  int res1 = sscanf(str, format, &c1, &c3);
  int res2 = s21_sscanf(str, format, &c2, &c4);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(c3, c4);
}
END_TEST

Suite *s21_sscanf_test_char(void) {
  Suite *suite = suite_create("s21_sscanf_test_char");
  TCase *tc = tcase_create("s21_sscanf_char_tc");

  tcase_add_test(tc, sscanf_char_1);
  tcase_add_test(tc, sscanf_char_2);
  tcase_add_test(tc, sscanf_char_3);
  tcase_add_test(tc, sscanf_char_4);
  tcase_add_test(tc, sscanf_char_5);

  suite_add_tcase(suite, tc);
  return suite;
}