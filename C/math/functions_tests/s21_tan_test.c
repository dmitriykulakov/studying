#include "s21_math_test.h"

START_TEST(s21_tan_test_1) {
  double test_var_1 = NAN;
  ck_assert_ldouble_nan(s21_tan(test_var_1));
  ck_assert_ldouble_nan(tan(test_var_1));
}
END_TEST

START_TEST(s21_tan_test_2) {
  double test_var_1 = +INFINITY;
  ck_assert_ldouble_nan(s21_tan(test_var_1));
  ck_assert_ldouble_nan(tan(test_var_1));
}
END_TEST

START_TEST(s21_tan_test_3) {
  double test_var_1 = -INFINITY;
  ck_assert_ldouble_nan(s21_tan(test_var_1));
  ck_assert_ldouble_nan(tan(test_var_1));
}
END_TEST

START_TEST(s21_tan_test_4) {
  double test_var_1 = 0.0L;
  ck_assert_ldouble_eq_tol(s21_tan(test_var_1), tan(test_var_1), ERROR);
}
END_TEST

START_TEST(s21_tan_test_5) {
  double test_var_1 = S21_PI * (1 / 2);
  ck_assert_ldouble_eq_tol(s21_tan(test_var_1), tan(test_var_1), ERROR);
}
END_TEST

START_TEST(s21_tan_test_6) {
  double test_var_1 = S21_PI * (1);
  ck_assert_ldouble_eq_tol(s21_tan(test_var_1), tan(test_var_1), ERROR);
}
END_TEST

START_TEST(s21_tan_test_7) {
  double test_var_1 = S21_PI * (3 / 2);
  ck_assert_ldouble_eq_tol(s21_tan(test_var_1), tan(test_var_1), ERROR);
}
END_TEST

START_TEST(s21_tan_test_8) {
  double test_var_1 = S21_PI * (2);
  ck_assert_ldouble_eq_tol(s21_tan(test_var_1), tan(test_var_1), ERROR);
}
END_TEST

START_TEST(s21_tan_test_9) {
  double test_var_1 = 123123123.436L;
  ck_assert_ldouble_eq_tol(s21_tan(test_var_1), tan(test_var_1), ERROR);
}
END_TEST

START_TEST(s21_tan_test_10) {
  double test_var_1 = -23.68L;
  ck_assert_ldouble_eq_tol(s21_tan(test_var_1), tan(test_var_1), ERROR);
}
END_TEST

START_TEST(s21_tan_test_11) {
  double test_var_1 = 0.000001L;
  ck_assert_ldouble_eq_tol(s21_tan(test_var_1), tan(test_var_1), ERROR);
}
END_TEST

START_TEST(s21_tan_test_12) {
  for (double test_var_1 = -S21_PI + TEST_SHIFT; test_var_1 <= S21_PI;
       test_var_1 += (S21_PI / 360) * TEST_FACTOR_1) {
    ck_assert_ldouble_eq_tol(s21_tan(test_var_1), tan(test_var_1), ERROR);
  }
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("s21_tan");
  TCase *tcase = tcase_create("core");

  tcase_add_test(tcase, s21_tan_test_1);
  tcase_add_test(tcase, s21_tan_test_2);
  tcase_add_test(tcase, s21_tan_test_3);
  tcase_add_test(tcase, s21_tan_test_4);
  tcase_add_test(tcase, s21_tan_test_5);
  tcase_add_test(tcase, s21_tan_test_6);
  tcase_add_test(tcase, s21_tan_test_7);
  tcase_add_test(tcase, s21_tan_test_8);
  tcase_add_test(tcase, s21_tan_test_9);
  tcase_add_test(tcase, s21_tan_test_10);
  tcase_add_test(tcase, s21_tan_test_11);
  tcase_add_test(tcase, s21_tan_test_12);

  suite_add_tcase(suite, tcase);
  return suite;
}

void case_test_runner(Suite *suite, int *fail_count) {
  SRunner *suite_runner = srunner_create(suite);
  srunner_run_all(suite_runner, CK_NORMAL);
  *fail_count = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
}

int main(void) {
  int fail_count = 0;
  case_test_runner(suite(), &fail_count);

  return fail_count;
}
