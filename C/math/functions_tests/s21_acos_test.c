#include "s21_math_test.h"

START_TEST(s21_acos_test_1) {
  double test_var_1 = NAN;
  ck_assert_ldouble_nan(s21_acos(test_var_1));
  ck_assert_ldouble_nan(acos(test_var_1));
}
END_TEST

START_TEST(s21_acos_test_2) {
  double test_var_1 = +INFINITY;
  ck_assert_ldouble_nan(s21_acos(test_var_1));
  ck_assert_ldouble_nan(acos(test_var_1));
}
END_TEST

START_TEST(s21_acos_test_3) {
  double test_var_1 = -INFINITY;
  ck_assert_ldouble_nan(s21_acos(test_var_1));
  ck_assert_ldouble_nan(acos(test_var_1));
}
END_TEST

START_TEST(s21_acos_test_4) {
  double test_var_1 = -2.24L;
  ck_assert_ldouble_nan(s21_acos(test_var_1));
  ck_assert_ldouble_nan(acos(test_var_1));
}
END_TEST
START_TEST(s21_acos_test_5) {
  double test_var_1 = +3.32L;
  ck_assert_ldouble_nan(s21_acos(test_var_1));
  ck_assert_ldouble_nan(acos(test_var_1));
}
END_TEST

START_TEST(s21_acos_test_6) {
  double test_var_1 = 1.0L;
  ck_assert_ldouble_eq_tol(s21_acos(test_var_1), acos(test_var_1), ERROR);
}
END_TEST

START_TEST(s21_acos_test_7) {
  double test_var_1 = 0.0L;
  ck_assert_ldouble_eq_tol(s21_acos(test_var_1), acos(test_var_1), ERROR);
}
END_TEST

START_TEST(s21_acos_test_8) {
  double test_var_1 = -1.0L;
  ck_assert_ldouble_eq_tol(s21_acos(test_var_1), acos(test_var_1), ERROR);
}
END_TEST

START_TEST(s21_acos_test_9) {
  double test_var_1 = 0.6786L;
  ck_assert_ldouble_eq_tol(s21_acos(test_var_1), acos(test_var_1), ERROR);
}
END_TEST

START_TEST(s21_acos_test_10) {
  double test_var_1 = -0.235L;
  ck_assert_ldouble_eq_tol(s21_acos(test_var_1), acos(test_var_1), ERROR);
}
END_TEST

START_TEST(s21_acos_test_11) {
  for (double test_var_1 = -1; test_var_1 <= 1; test_var_1 += TEST_FACTOR_2) {
    ck_assert_ldouble_eq_tol(s21_acos(test_var_1), acos(test_var_1), ERROR);
  }
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("s21_acos");
  TCase *tcase = tcase_create("core");

  tcase_add_test(tcase, s21_acos_test_1);
  tcase_add_test(tcase, s21_acos_test_2);
  tcase_add_test(tcase, s21_acos_test_3);
  tcase_add_test(tcase, s21_acos_test_4);
  tcase_add_test(tcase, s21_acos_test_5);
  tcase_add_test(tcase, s21_acos_test_6);
  tcase_add_test(tcase, s21_acos_test_7);
  tcase_add_test(tcase, s21_acos_test_8);
  tcase_add_test(tcase, s21_acos_test_9);
  tcase_add_test(tcase, s21_acos_test_10);
  tcase_add_test(tcase, s21_acos_test_11);

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
