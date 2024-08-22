#include "s21_math_test.h"

START_TEST(s21_sqrt_test_1) {
  ck_assert_ldouble_eq_tol(s21_sqrt(0), sqrt(0), 1E-6L);
}
END_TEST

START_TEST(s21_sqrt_test_2) {
  ck_assert_ldouble_eq_tol(s21_sqrt(1352565435634564564.5435235325654645634622),
                           sqrt(1352565435634564564.5435235325654645634622),
                           1E-6L);
}
END_TEST

START_TEST(s21_sqrt_test_3) {
  ck_assert_ldouble_eq_tol(s21_sqrt(0.000001), sqrt(0.000001), 1E3L);
}
END_TEST

START_TEST(s21_sqrt_test_4) {
  ck_assert_ldouble_eq_tol(s21_sqrt(0.0000001), sqrt(0.0000001), 1E-6L);
}
END_TEST

START_TEST(s21_sqrt_test_5) {
  ck_assert_ldouble_eq_tol(s21_sqrt(0.999999), sqrt(0.999999), 1E-6L);
}
END_TEST

START_TEST(s21_sqrt_test_6) {
  ck_assert_ldouble_eq_tol(s21_sqrt(0.9999999), sqrt(0.9999999), 1E-6L);
}
END_TEST

START_TEST(s21_sqrt_test_7) {
  ck_assert_ldouble_nan(s21_sqrt(-1234));
  ck_assert_ldouble_nan(sqrt(-1234));
}
END_TEST

START_TEST(s21_sqrt_test_8) {
  ck_assert_ldouble_nan(s21_sqrt(-0.00000000001));
  ck_assert_ldouble_nan(sqrt(-0.00000000001));
}
END_TEST

START_TEST(s21_sqrt_test_9) {
  ck_assert_ldouble_eq_tol(s21_sqrt(1.000002), sqrt(1.000002), 1E-6L);
}
END_TEST

START_TEST(s21_sqrt_test_10) {
  ck_assert_ldouble_eq_tol(s21_sqrt(1.000001), sqrt(1.000001), 1E-6L);
}
END_TEST

START_TEST(s21_sqrt_test_11) {
  ck_assert_ldouble_eq_tol(s21_sqrt(135142344234234523),
                           sqrt(135142344234234523), 1E-6L);
}
END_TEST

START_TEST(s21_sqrt_test_12) {
  ck_assert_ldouble_nan(s21_sqrt(S21_NAN));
  ck_assert_ldouble_nan(sqrt(NAN));
}
END_TEST

START_TEST(s21_sqrt_test_13) {
  ck_assert_ldouble_eq(s21_sqrt(S21_INF_P), sqrt(INFINITY));
}
END_TEST

START_TEST(s21_sqrt_test_14) {
  ck_assert_ldouble_nan(s21_sqrt(S21_INF_N));
  ck_assert_ldouble_nan(sqrt(-INFINITY));
}
END_TEST

START_TEST(s21_sqrt_test_15) {
  ck_assert_ldouble_eq_tol(s21_sqrt(-0), sqrt(-0), 1E-6L);
}
END_TEST

START_TEST(s21_sqrt_test_16) {
  ck_assert_ldouble_eq_tol(s21_sqrt(+0), sqrt(+0), 1E-6L);
}
END_TEST

START_TEST(s21_sqrt_test_17) {
  ck_assert_ldouble_eq_tol(s21_sqrt(0.4909), sqrt(0.4909), 1e-6);
}
END_TEST

START_TEST(s21_sqrt_test_18) {
  ck_assert_ldouble_eq_tol(s21_sqrt(S21_E), sqrt(S21_E), 1e-6);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[32m-=S21_SQRT_TEST=-\033[0m");
  TCase *tcase = tcase_create("core");
  ;

  tcase_add_test(tcase, s21_sqrt_test_1);
  tcase_add_test(tcase, s21_sqrt_test_2);
  tcase_add_test(tcase, s21_sqrt_test_3);
  tcase_add_test(tcase, s21_sqrt_test_4);
  tcase_add_test(tcase, s21_sqrt_test_5);
  tcase_add_test(tcase, s21_sqrt_test_6);
  tcase_add_test(tcase, s21_sqrt_test_7);
  tcase_add_test(tcase, s21_sqrt_test_8);
  tcase_add_test(tcase, s21_sqrt_test_9);
  tcase_add_test(tcase, s21_sqrt_test_10);
  tcase_add_test(tcase, s21_sqrt_test_11);
  tcase_add_test(tcase, s21_sqrt_test_12);
  tcase_add_test(tcase, s21_sqrt_test_13);
  tcase_add_test(tcase, s21_sqrt_test_14);
  tcase_add_test(tcase, s21_sqrt_test_15);
  tcase_add_test(tcase, s21_sqrt_test_16);
  tcase_add_test(tcase, s21_sqrt_test_17);
  tcase_add_test(tcase, s21_sqrt_test_18);

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
