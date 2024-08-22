#include "s21_math_test.h"

START_TEST(s21_exp_test_1) {
  ck_assert_ldouble_eq_tol(s21_exp(2.5), exp(2.5), 1E-5L);
}
END_TEST

START_TEST(s21_exp_test_2) {
  ck_assert_ldouble_eq_tol(s21_exp(1.25), exp(1.25), 1E-5L);
}
END_TEST

START_TEST(s21_exp_test_3) {
  ck_assert_ldouble_eq_tol(s21_exp(320.42135435), exp(320.42135435), 1E124L);
}
END_TEST

START_TEST(s21_exp_test_4) {
  ck_assert_ldouble_eq_tol(s21_exp(-40.42135435), exp(-40.42135435), 1E-6L);
}
END_TEST

START_TEST(s21_exp_test_5) {
  ck_assert_ldouble_eq(s21_exp(800.42135435), exp(800.42135435));
}
END_TEST

START_TEST(s21_exp_test_6) {
  ck_assert_ldouble_eq_tol(s21_exp(0.000001), exp(0.000001), 1E-6L);
}
END_TEST

START_TEST(s21_exp_test_7) {
  ck_assert_ldouble_eq_tol(s21_exp(0.0000003), exp(0.0000003), 1E-6L);
}
END_TEST

START_TEST(s21_exp_test_8) {
  ck_assert_ldouble_eq_tol(s21_exp(25.000000000001), exp(25.000000000001),
                           1E-5L);
}
END_TEST

START_TEST(s21_exp_test_9) {
  ck_assert_ldouble_eq_tol(s21_exp(1), exp(1), 1E-6L);
}
END_TEST

START_TEST(s21_exp_test_10) {
  ck_assert_ldouble_eq_tol(s21_exp(-1), exp(-1), 1E-6L);
}
END_TEST

START_TEST(s21_exp_test_11) {
  ck_assert_ldouble_eq_tol(s21_exp(-0.1), exp(-0.1), 1E-6L);
}
END_TEST

START_TEST(s21_exp_test_12) {
  ck_assert_ldouble_nan(s21_exp(S21_NAN));
  ck_assert_ldouble_nan(exp(NAN));
}
END_TEST

START_TEST(s21_exp_test_13) {
  ck_assert_ldouble_eq(s21_exp(S21_INF_P), exp(INFINITY));
}
END_TEST

START_TEST(s21_exp_test_14) {
  ck_assert_ldouble_eq_tol(s21_exp(S21_INF_N), exp(-INFINITY), 1E-6L);
}
END_TEST

START_TEST(s21_exp_test_15) {
  ck_assert_ldouble_eq_tol(s21_exp(-0), exp(-0), 1E-6L);
}
END_TEST

START_TEST(s21_exp_test_16) {
  ck_assert_ldouble_eq_tol(s21_exp(+0), exp(+0), 1E-6L);
}
END_TEST

START_TEST(s21_exp_test_17) {
  ck_assert_ldouble_eq_tol(s21_exp(-0.000001), exp(-0.000001), 1E-6L);
}
END_TEST

START_TEST(s21_exp_test_18) {
  ck_assert_ldouble_eq_tol(s21_exp(-0.0000001), exp(-0.0000001), 1E-6L);
}
END_TEST

START_TEST(s21_exp_test_19) {
  ck_assert_ldouble_eq_tol(s21_exp(-0.9999999), exp(-0.9999999), 1E-6L);
}
END_TEST

START_TEST(s21_exp_test_20) {
  ck_assert_ldouble_eq_tol(s21_exp(-0.999999), exp(-0.999999), 1E-6L);
}
END_TEST

START_TEST(s21_exp_test_21) {
  ck_assert_ldouble_eq_tol(s21_exp(0.000001), exp(0.000001), 1e-6);
}
END_TEST

START_TEST(s21_exp_test_22) {
  ck_assert_ldouble_eq_tol(s21_exp(-9998.000331), exp(-9998.000331), 1e-6);
}
END_TEST

START_TEST(s21_exp_test_23) {
  ck_assert_ldouble_eq_tol(s21_exp(-0.00000881), exp(-0.00000881), 1e-6);
}
END_TEST

START_TEST(s21_exp_test_24) {
  ck_assert_ldouble_eq_tol(s21_exp(S21_E), exp(S21_E), 1e-6);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[32m-=S21_EXP_TEST=-\033[0m");
  TCase *tcase = tcase_create("core");

  tcase_add_test(tcase, s21_exp_test_1);
  tcase_add_test(tcase, s21_exp_test_2);
  tcase_add_test(tcase, s21_exp_test_3);
  tcase_add_test(tcase, s21_exp_test_4);
  tcase_add_test(tcase, s21_exp_test_5);
  tcase_add_test(tcase, s21_exp_test_6);
  tcase_add_test(tcase, s21_exp_test_7);
  tcase_add_test(tcase, s21_exp_test_8);
  tcase_add_test(tcase, s21_exp_test_9);
  tcase_add_test(tcase, s21_exp_test_10);
  tcase_add_test(tcase, s21_exp_test_11);
  tcase_add_test(tcase, s21_exp_test_12);
  tcase_add_test(tcase, s21_exp_test_13);
  tcase_add_test(tcase, s21_exp_test_14);
  tcase_add_test(tcase, s21_exp_test_15);
  tcase_add_test(tcase, s21_exp_test_16);
  tcase_add_test(tcase, s21_exp_test_17);
  tcase_add_test(tcase, s21_exp_test_18);
  tcase_add_test(tcase, s21_exp_test_19);
  tcase_add_test(tcase, s21_exp_test_20);
  tcase_add_test(tcase, s21_exp_test_21);
  tcase_add_test(tcase, s21_exp_test_22);
  tcase_add_test(tcase, s21_exp_test_23);
  tcase_add_test(tcase, s21_exp_test_24);

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
