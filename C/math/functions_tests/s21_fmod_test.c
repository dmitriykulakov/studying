#include "s21_math_test.h"

START_TEST(s21_fmod_test_1) {
  double test_var_1 = NAN;
  double test_var_2 = 2 * S21_PI;
  ck_assert_ldouble_nan(s21_fmod(test_var_1, test_var_2));
  ck_assert_ldouble_nan(fmod(test_var_1, test_var_2));
}
END_TEST

START_TEST(s21_fmod_test_2) {
  double test_var_1 = 2 * S21_PI;
  double test_var_2 = NAN;
  ck_assert_ldouble_nan(s21_fmod(test_var_1, test_var_2));
  ck_assert_ldouble_nan(fmod(test_var_1, test_var_2));
}
END_TEST

START_TEST(s21_fmod_test_3) {
  double test_var_1 = +INFINITY;
  double test_var_2 = 2 * S21_PI;
  ck_assert_ldouble_nan(s21_fmod(test_var_1, test_var_2));
  ck_assert_ldouble_nan(fmod(test_var_1, test_var_2));
}
END_TEST

START_TEST(s21_fmod_test_4) {
  double test_var_1 = -INFINITY;
  double test_var_2 = 2 * S21_PI;
  ck_assert_ldouble_nan(s21_fmod(test_var_1, test_var_2));
  ck_assert_ldouble_nan(fmod(test_var_1, test_var_2));
}
END_TEST

START_TEST(s21_fmod_test_5) {
  double test_var_1 = 2 * S21_PI;
  double test_var_2 = +INFINITY;
  ck_assert_ldouble_eq_tol(s21_fmod(test_var_1, test_var_2),
                           fmod(test_var_1, test_var_2), ERROR);
}
END_TEST

START_TEST(s21_fmod_test_6) {
  double test_var_1 = 2 * S21_PI;
  double test_var_2 = -INFINITY;
  ck_assert_ldouble_eq_tol(s21_fmod(test_var_1, test_var_2),
                           fmod(test_var_1, test_var_2), ERROR);
}
END_TEST

START_TEST(s21_fmod_test_7) {
  double test_var_1 = +INFINITY;
  double test_var_2 = +INFINITY;
  ck_assert_ldouble_nan(s21_fmod(test_var_1, test_var_2));
  ck_assert_ldouble_nan(fmod(test_var_1, test_var_2));

  test_var_1 = +INFINITY;
  test_var_2 = -INFINITY;
  ck_assert_ldouble_nan(s21_fmod(test_var_1, test_var_2));
  ck_assert_ldouble_nan(fmod(test_var_1, test_var_2));

  test_var_1 = -INFINITY;
  test_var_2 = +INFINITY;
  ck_assert_ldouble_nan(s21_fmod(test_var_1, test_var_2));
  ck_assert_ldouble_nan(fmod(test_var_1, test_var_2));

  test_var_1 = -INFINITY;
  test_var_2 = -INFINITY;
  ck_assert_ldouble_nan(s21_fmod(test_var_1, test_var_2));
  ck_assert_ldouble_nan(fmod(test_var_1, test_var_2));
}
END_TEST

START_TEST(s21_fmod_test_8) {
  double test_var_1 = NAN;
  double test_var_2 = +INFINITY;
  ck_assert_ldouble_nan(s21_fmod(test_var_1, test_var_2));
  ck_assert_ldouble_nan(fmod(test_var_1, test_var_2));
  test_var_1 = NAN;
  test_var_2 = -INFINITY;
  ck_assert_ldouble_nan(s21_fmod(test_var_1, test_var_2));
  ck_assert_ldouble_nan(fmod(test_var_1, test_var_2));
}
END_TEST

START_TEST(s21_fmod_test_9) {
  double test_var_1 = 2 * S21_PI;
  double test_var_2 = 0.0L;
  ck_assert_ldouble_nan(s21_fmod(test_var_1, test_var_2));
  ck_assert_ldouble_nan(fmod(test_var_1, test_var_2));
}
END_TEST

START_TEST(s21_fmod_test_10) {
  double test_var_1 = 0.0L;
  double test_var_2 = 2 * S21_PI;
  ck_assert_ldouble_eq_tol(s21_fmod(test_var_1, test_var_2),
                           fmod(test_var_1, test_var_2), ERROR);
}
END_TEST

START_TEST(s21_fmod_test_11) {
  double test_var_1 = 1.5645L;
  double test_var_2 = 2 * S21_PI;
  ck_assert_ldouble_eq_tol(s21_fmod(test_var_1, test_var_2),
                           fmod(test_var_1, test_var_2), ERROR);
}
END_TEST

START_TEST(s21_fmod_test_12) {
  double test_var_1 = -1.5645L;
  double test_var_2 = 2 * S21_PI;
  ck_assert_ldouble_eq_tol(s21_fmod(test_var_1, test_var_2),
                           fmod(test_var_1, test_var_2), ERROR);
}
END_TEST

START_TEST(s21_fmod_test_13) {
  double test_var_1 = 23.6786L;
  double test_var_2 = 2 * S21_PI;
  ck_assert_ldouble_eq_tol(s21_fmod(test_var_1, test_var_2),
                           fmod(test_var_1, test_var_2), ERROR);
}
END_TEST

START_TEST(s21_fmod_test_14) {
  double test_var_1 = -25.235L;
  double test_var_2 = 2 * S21_PI;
  ck_assert_ldouble_eq_tol(s21_fmod(test_var_1, test_var_2),
                           fmod(test_var_1, test_var_2), ERROR);
}
END_TEST

START_TEST(s21_fmod_test_15) {
  double test_var_1 = +3L;
  double test_var_2 = -2L;
  ck_assert_ldouble_eq_tol(s21_fmod(test_var_1, test_var_2),
                           fmod(test_var_1, test_var_2), ERROR);
  test_var_1 = +4L;
  test_var_2 = -5L;
  ck_assert_ldouble_eq_tol(s21_fmod(test_var_1, test_var_2),
                           fmod(test_var_1, test_var_2), ERROR);
  test_var_1 = -3L;
  test_var_2 = -2L;
  ck_assert_ldouble_eq_tol(s21_fmod(test_var_1, test_var_2),
                           fmod(test_var_1, test_var_2), ERROR);
  test_var_1 = -4L;
  test_var_2 = -5L;
  ck_assert_ldouble_eq_tol(s21_fmod(test_var_1, test_var_2),
                           fmod(test_var_1, test_var_2), ERROR);
}
END_TEST

START_TEST(s21_fmod_test_16) {
  double test_var_2 = 2 * S21_PI;
  for (double test_var_1 = -1; test_var_1 <= 1; test_var_1 += 0.1L) {
    ck_assert_ldouble_eq_tol(s21_fmod(test_var_1, test_var_2),
                             fmod(test_var_1, test_var_2), ERROR);
  }
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("s21_fmod");
  TCase *tcase = tcase_create("core");

  tcase_add_test(tcase, s21_fmod_test_1);
  tcase_add_test(tcase, s21_fmod_test_2);
  tcase_add_test(tcase, s21_fmod_test_3);
  tcase_add_test(tcase, s21_fmod_test_4);
  tcase_add_test(tcase, s21_fmod_test_5);
  tcase_add_test(tcase, s21_fmod_test_6);
  tcase_add_test(tcase, s21_fmod_test_7);
  tcase_add_test(tcase, s21_fmod_test_8);
  tcase_add_test(tcase, s21_fmod_test_9);
  tcase_add_test(tcase, s21_fmod_test_10);
  tcase_add_test(tcase, s21_fmod_test_11);
  tcase_add_test(tcase, s21_fmod_test_12);
  tcase_add_test(tcase, s21_fmod_test_13);
  tcase_add_test(tcase, s21_fmod_test_14);
  tcase_add_test(tcase, s21_fmod_test_15);
  tcase_add_test(tcase, s21_fmod_test_16);

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
