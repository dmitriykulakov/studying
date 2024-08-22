#include "s21_test.h"

START_TEST(sscanf_n_1) {
  char format[] = "%n";
  char str[] = "slovo pacana";
  int n1 = 0, n2 = 0;

  int res1 = sscanf(str, format, &n1);
  int res2 = s21_sscanf(str, format, &n2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(sscanf_n_2) {
  char format[] = "%Lf %Lf %n";
  char str[] = "-0.2 76.1 lompa";
  long double f1 = 0, f2 = 0, f3 = 0, f4 = 0;
  int n1 = 0, n2 = 0;

  int res1 = sscanf(str, format, &f1, &f3, &n1);
  int res2 = s21_sscanf(str, format, &f2, &f4, &n2);
  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq(f1, f2);
  ck_assert_float_eq(f3, f4);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(sscanf_n_3) {
  char format[] = "yurara%n dragon tearz";
  char str[] = "yurara";
  int n1 = 0, n2 = 0;

  int res1 = sscanf(str, format, &n1);
  int res2 = s21_sscanf(str, format, &n2);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

Suite *s21_sscanf_test_n(void) {
  Suite *suite = suite_create("s21_sscanf_test_n");
  TCase *tc = tcase_create("s21_sscanf_n_tc");

  tcase_add_test(tc, sscanf_n_1);
  tcase_add_test(tc, sscanf_n_2);
  tcase_add_test(tc, sscanf_n_3);

  suite_add_tcase(suite, tc);
  return suite;
}