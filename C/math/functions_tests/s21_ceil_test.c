#include "s21_math_test.h"

START_TEST(s21_ceil_test_1) {
  ck_assert_ldouble_eq_tol(s21_ceil(1254354.9999999), ceil(1254354.9999999),
                           1e-6);
}
END_TEST

START_TEST(s21_ceil_test_2) {
  ck_assert_ldouble_eq_tol(s21_ceil(-1254354.9999999), ceil(-1254354.9999999),
                           1e-6);
}
END_TEST

START_TEST(s21_ceil_test_3) {
  ck_assert_ldouble_eq_tol(s21_ceil(1254354), ceil(1254354), 1e-6);
}
END_TEST

START_TEST(s21_ceil_test_4) {
  ck_assert_ldouble_eq_tol(s21_ceil(-1254354), ceil(-1254354), 1e-6);
}
END_TEST

START_TEST(s21_ceil_test_5) {
  ck_assert_ldouble_eq_tol(s21_ceil(1254354.0000001), ceil(1254354.0000001),
                           1e-6);
}
END_TEST

START_TEST(s21_ceil_test_6) {
  ck_assert_ldouble_eq_tol(s21_ceil(-1254354.0000001), ceil(-1254354.0000001),
                           1e-6);
}
END_TEST

START_TEST(s21_ceil_test_7) {
  ck_assert_ldouble_eq_tol(s21_ceil(12545435435435345354.99999999),
                           ceil(12545435435435345354.99999999), 1e-6);
}
END_TEST

START_TEST(s21_ceil_test_8) {
  ck_assert_ldouble_eq_tol(s21_ceil(12545435435435345354.0000001),
                           ceil(12545435435435345354.0000001), 1e-6);
}
END_TEST

START_TEST(s21_ceil_test_9) {
  ck_assert_ldouble_eq_tol(s21_ceil(-12545435435435345354.0000001),
                           ceil(-12545435435435345354.0000001), 1e-6);
}
END_TEST

START_TEST(s21_ceil_test_10) {
  ck_assert_ldouble_eq_tol(s21_ceil(2.5), ceil(2.5), 1e-6);
}
END_TEST

START_TEST(s21_ceil_test_11) {
  ck_assert_ldouble_eq_tol(s21_ceil(-2.5), ceil(-2.5), 1e-6);
}
END_TEST

START_TEST(s21_ceil_test_12) {
  ck_assert_ldouble_nan(s21_ceil(S21_NAN));
  ck_assert_ldouble_nan(ceil(NAN));
}
END_TEST

START_TEST(s21_ceil_test_13) {
  ck_assert_ldouble_eq(s21_ceil(S21_INF_P), ceil(INFINITY));
}
END_TEST

START_TEST(s21_ceil_test_14) {
  ck_assert_ldouble_eq(s21_ceil(S21_INF_N), ceil(-INFINITY));
}
END_TEST

START_TEST(s21_ceil_test_15) {
  ck_assert_ldouble_eq_tol(s21_ceil(-0), ceil(-0), 1e-6);
}
END_TEST

START_TEST(s21_ceil_test_16) {
  ck_assert_ldouble_eq_tol(s21_ceil(+0), ceil(+0), 1e-6);
}
END_TEST

START_TEST(s21_ceil_test_17) {
  ck_assert_ldouble_eq_tol(s21_ceil(0.345678789987), ceil(0.345678789987),
                           1e-6);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[32m-=S21_CEIL_TEST=-\033[0m");
  TCase *tcase = tcase_create("core");

  tcase_add_test(tcase, s21_ceil_test_1);
  tcase_add_test(tcase, s21_ceil_test_2);
  tcase_add_test(tcase, s21_ceil_test_3);
  tcase_add_test(tcase, s21_ceil_test_4);
  tcase_add_test(tcase, s21_ceil_test_5);
  tcase_add_test(tcase, s21_ceil_test_6);
  tcase_add_test(tcase, s21_ceil_test_7);
  tcase_add_test(tcase, s21_ceil_test_8);
  tcase_add_test(tcase, s21_ceil_test_9);
  tcase_add_test(tcase, s21_ceil_test_10);
  tcase_add_test(tcase, s21_ceil_test_11);
  tcase_add_test(tcase, s21_ceil_test_12);
  tcase_add_test(tcase, s21_ceil_test_13);
  tcase_add_test(tcase, s21_ceil_test_14);
  tcase_add_test(tcase, s21_ceil_test_15);
  tcase_add_test(tcase, s21_ceil_test_16);
  tcase_add_test(tcase, s21_ceil_test_17);

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
