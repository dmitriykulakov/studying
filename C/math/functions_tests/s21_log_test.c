#include "s21_math_test.h"

START_TEST(s21_log_test_1) {
  ck_assert_ldouble_eq_tol(s21_log(5), log(5), 1E-6L);
}
END_TEST

START_TEST(s21_log_test_2) {
  ck_assert_ldouble_eq_tol(s21_log(10.000001), log(10.000001), 1E-6L);
}
END_TEST

START_TEST(s21_log_test_3) {
  ck_assert_ldouble_eq_tol(s21_log(164563), log(164563), 1E-6L);
}
END_TEST

START_TEST(s21_log_test_4) {
  ck_assert_ldouble_eq_tol(s21_log(0.4324), log(0.4324), 1E-6L);
}
END_TEST

START_TEST(s21_log_test_5) {
  ck_assert_ldouble_eq_tol(s21_log(0.999999), log(0.999999), 1E-6L);
}
END_TEST

START_TEST(s21_log_test_6) {
  ck_assert_ldouble_eq_tol(s21_log(0.000001), log(0.000001), 1E-6L);
}
END_TEST

START_TEST(s21_log_test_7) {
  ck_assert_ldouble_eq_tol(s21_log(94556563463643523), log(94556563463643523),
                           1E-6L);
}
END_TEST

START_TEST(s21_log_test_8) {
  ck_assert_ldouble_nan(s21_log(-94556563463643523));
  ck_assert_ldouble_nan(log(-94556563463643523));
}
END_TEST

START_TEST(s21_log_test_9) {
  ck_assert_ldouble_eq_tol(s21_log(1), log(1), 1E-6L);
}
END_TEST

START_TEST(s21_log_test_10) {
  ck_assert_ldouble_nan(s21_log(-1));
  ck_assert_ldouble_nan(log(-1));
}
END_TEST

START_TEST(s21_log_test_11) {
  ck_assert_ldouble_nan(s21_log(-0.000000001));
  ck_assert_ldouble_nan(log(-0.000000001));
}
END_TEST

START_TEST(s21_log_test_12) {
  ck_assert_ldouble_nan(s21_log(S21_NAN));
  ck_assert_ldouble_nan(log(NAN));
}
END_TEST

START_TEST(s21_log_test_13) {
  ck_assert_ldouble_eq(s21_log(S21_INF_P), log(INFINITY));
}
END_TEST

START_TEST(s21_log_test_14) {
  ck_assert_ldouble_nan(s21_log(S21_INF_N));
  ck_assert_ldouble_nan(log(-INFINITY));
}
END_TEST

START_TEST(s21_log_test_15) { ck_assert_ldouble_eq(s21_log(-0), log(-0)); }
END_TEST

START_TEST(s21_log_test_16) { ck_assert_ldouble_eq(s21_log(+0), log(+0)); }
END_TEST

START_TEST(s21_log_test_17) {
  ck_assert_ldouble_eq_tol(s21_log(0.17956), log(0.17956), 1e-6);
}
END_TEST

START_TEST(s21_log_test_18) {
  ck_assert_ldouble_eq_tol(s21_log(9999.498004), log(9999.498004), 1e-6);
}
END_TEST

START_TEST(s21_log_test_19) {
  ck_assert_ldouble_eq_tol(s21_log((double)S21_E), log((double)S21_E), 1e-6);
}
END_TEST

START_TEST(s21_log_test_20) {
  ck_assert_ldouble_eq_tol(s21_log((double)S21_PI), log((double)S21_PI), 1e-6);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[32m-=S21_LOG_TEST=-\033[0m");
  TCase *tcase = tcase_create("log_tc");

  tcase_add_test(tcase, s21_log_test_1);
  tcase_add_test(tcase, s21_log_test_2);
  tcase_add_test(tcase, s21_log_test_3);
  tcase_add_test(tcase, s21_log_test_4);
  tcase_add_test(tcase, s21_log_test_5);
  tcase_add_test(tcase, s21_log_test_6);
  tcase_add_test(tcase, s21_log_test_7);
  tcase_add_test(tcase, s21_log_test_8);
  tcase_add_test(tcase, s21_log_test_9);
  tcase_add_test(tcase, s21_log_test_10);
  tcase_add_test(tcase, s21_log_test_11);
  tcase_add_test(tcase, s21_log_test_12);
  tcase_add_test(tcase, s21_log_test_13);
  tcase_add_test(tcase, s21_log_test_14);
  tcase_add_test(tcase, s21_log_test_15);
  tcase_add_test(tcase, s21_log_test_16);
  tcase_add_test(tcase, s21_log_test_17);
  tcase_add_test(tcase, s21_log_test_18);
  tcase_add_test(tcase, s21_log_test_19);
  tcase_add_test(tcase, s21_log_test_20);

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
