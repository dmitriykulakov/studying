#include "s21_test.h"

START_TEST(sscanf_i_1) {
  char str[] = "0777";
  unsigned int p1 = 0, p2 = 0;

  int res1 = sscanf(str, "%i", &p1);
  int res2 = s21_sscanf(str, "%i", &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_i_2) {
  char str[] = "-0777";
  unsigned int p1 = 0, p2 = 0;

  int res1 = sscanf(str, "%i", &p1);
  int res2 = s21_sscanf(str, "%i", &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_i_3) {
  char str[] = "+0777";
  unsigned int p1 = 0, p2 = 0;

  int res1 = sscanf(str, "%i", &p1);
  int res2 = s21_sscanf(str, "%i", &p2);
  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(p1, p2);
}
END_TEST

Suite *s21_sscanf_test_i(void) {
  Suite *suite = suite_create("s21_sscanf_test_i");
  TCase *tc = tcase_create("s21_sscanf_i_tc");

  tcase_add_test(tc, sscanf_i_1);
  tcase_add_test(tc, sscanf_i_2);
  tcase_add_test(tc, sscanf_i_3);

  suite_add_tcase(suite, tc);
  return suite;
}