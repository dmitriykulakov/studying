#include "s21_math_test.h"

START_TEST(s21_abs_test_1) { ck_assert_int_eq(s21_abs(14), abs(14)); }
END_TEST

START_TEST(s21_abs_test_2) { ck_assert_int_eq(s21_abs(777), abs(777)); }
END_TEST

START_TEST(s21_abs_test_3) { ck_assert_int_eq(s21_abs(-777), abs(-777)); }
END_TEST

START_TEST(s21_abs_test_4) { ck_assert_int_eq(s21_abs(777), abs(777)); }
END_TEST

START_TEST(s21_abs_test_5) { ck_assert_int_eq(s21_abs(-123), abs(-123)); }
END_TEST

START_TEST(s21_abs_test_6) { ck_assert_int_eq(s21_abs(+0), abs(+0)); }
END_TEST

START_TEST(s21_abs_test_7) { ck_assert_int_eq(s21_abs(-0), abs(-0)); }
END_TEST

START_TEST(s21_abs_test_8) { ck_assert_int_eq(s21_abs(INT_MAX), abs(INT_MAX)); }
END_TEST

START_TEST(s21_abs_test_9) { ck_assert_int_eq(s21_abs(INT_MIN), abs(INT_MIN)); }
END_TEST

START_TEST(s21_abs_test_10) {
  int test_1 = -5;
  ck_assert_ldouble_eq_tol(s21_abs(test_1), abs(test_1), 1e-6);
}
END_TEST

START_TEST(s21_abs_test_11) {
  int test_2 = -0;
  ck_assert_ldouble_eq_tol(s21_abs(test_2), abs(test_2), 1e-6);
}
END_TEST

START_TEST(s21_abs_test_12) {
  int test_3 = 12;
  ck_assert_ldouble_eq_tol(s21_abs(test_3), abs(test_3), 1e-6);
}
END_TEST

START_TEST(s21_abs_test_13) {
  for (int i = -10; i <= 10; i += 1) {
    ck_assert_ldouble_eq_tol(s21_abs(i), abs(i), 1e-6);
  }
}
END_TEST

START_TEST(s21_abs_test_14) {
  double test_4 = S21_NAN;
  ck_assert_ldouble_eq_tol(s21_abs((int)test_4), abs((int)test_4), 1e-6);
}
END_TEST

START_TEST(s21_abs_test_15) {
  double test_5 = S21_INF_P;
  ck_assert_ldouble_eq_tol(s21_abs((int)test_5), abs((int)test_5), 1e-6);
}
END_TEST

START_TEST(s21_abs_test_16) {
  double test_6 = S21_INF_N;
  ck_assert_ldouble_eq_tol(s21_abs((int)test_6), abs((int)test_6), 1e-6);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[32m-=S21_ABS_TEST=-\033[0m");
  TCase *tcase = tcase_create("core");

  tcase_add_test(tcase, s21_abs_test_1);
  tcase_add_test(tcase, s21_abs_test_2);
  tcase_add_test(tcase, s21_abs_test_3);
  tcase_add_test(tcase, s21_abs_test_4);
  tcase_add_test(tcase, s21_abs_test_5);
  tcase_add_test(tcase, s21_abs_test_6);
  tcase_add_test(tcase, s21_abs_test_7);
  tcase_add_test(tcase, s21_abs_test_8);
  tcase_add_test(tcase, s21_abs_test_9);
  tcase_add_test(tcase, s21_abs_test_10);
  tcase_add_test(tcase, s21_abs_test_11);
  tcase_add_test(tcase, s21_abs_test_12);
  tcase_add_test(tcase, s21_abs_test_13);
  tcase_add_test(tcase, s21_abs_test_14);
  tcase_add_test(tcase, s21_abs_test_15);
  tcase_add_test(tcase, s21_abs_test_16);

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
