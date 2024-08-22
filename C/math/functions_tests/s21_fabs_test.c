#include "s21_math_test.h"

START_TEST(s21_fabs_test_1) {
  ck_assert_ldouble_eq_tol(s21_fabs(-4645645654739857.32131444324),
                           fabs(-4645645654739857.32131444324), 1E1L);
}
END_TEST

START_TEST(s21_fabs_test_2) {
  ck_assert_ldouble_eq_tol(s21_fabs(1.5555555), fabs(1.5555555), 1E-6L);
}
END_TEST

START_TEST(s21_fabs_test_3) {
  ck_assert_ldouble_eq_tol(s21_fabs(2.4999999), fabs(2.4999999), 1E-6L);
}
END_TEST

START_TEST(s21_fabs_test_4) {
  ck_assert_ldouble_eq_tol(s21_fabs(-2.500000000001), fabs(-2.500000000001),
                           1E-6L);
}
END_TEST

START_TEST(s21_fabs_test_5) {
  ck_assert_ldouble_eq_tol(s21_fabs(-1.499997), fabs(-1.499997), 1E-6L);
}
END_TEST

START_TEST(s21_fabs_test_6) {
  ck_assert_ldouble_eq_tol(s21_fabs(-0.000001), fabs(-0.000001), 1E-6L);
}
END_TEST

START_TEST(s21_fabs_test_7) {
  ck_assert_ldouble_eq_tol(s21_fabs(-0.0000019), fabs(-0.0000019), 1E-6L);
}
END_TEST

START_TEST(s21_fabs_test_8) {
  ck_assert_ldouble_eq_tol(s21_fabs(25.000000000001), fabs(25.000000000001),
                           1E-6L);
}
END_TEST

START_TEST(s21_fabs_test_9) {
  ck_assert_ldouble_eq_tol(s21_fabs(-1325325.0), fabs(-1325325.0), 1E-6L);
}
END_TEST

START_TEST(s21_fabs_test_10) {
  ck_assert_ldouble_eq_tol(s21_fabs(-0.0), fabs(-0.0), 1E-6L);
}
END_TEST

START_TEST(s21_fabs_test_11) {
  ck_assert_ldouble_eq_tol(s21_fabs(+0.0), fabs(+0.0), 1E-6L);
}
END_TEST

START_TEST(s21_fabs_test_12) {
  ck_assert_ldouble_nan(s21_fabs(S21_NAN));
  ck_assert_ldouble_nan(fabs(NAN));
}
END_TEST

START_TEST(s21_fabs_test_13) {
  ck_assert_ldouble_eq(s21_fabs(S21_INF_P), fabs(INFINITY));
}
END_TEST

START_TEST(s21_fabs_test_14) {
  ck_assert_ldouble_eq(s21_fabs(S21_INF_N), fabs(-INFINITY));
}
END_TEST

START_TEST(s21_fabs_test_15) {
  for (double i = -1.01; i <= 1.01; i += 0.01) {
    ck_assert_ldouble_eq_tol(s21_fabs(i), fabs(i), 1e-6);
  }
}
END_TEST

START_TEST(s21_fabs_test_16) {
  ck_assert_ldouble_eq_tol(s21_fabs((double)S21_PI), fabs((double)S21_PI),
                           1e-6);
}
END_TEST

START_TEST(s21_fabs_test_17) {
  ck_assert_ldouble_eq_tol(s21_fabs((double)S21_E), fabs((double)S21_E), 1e-6);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[32m-=S21_FABS_TEST=-\033[0m");
  TCase *tcase = tcase_create("fabs_tc");

  tcase_add_test(tcase, s21_fabs_test_1);
  tcase_add_test(tcase, s21_fabs_test_2);
  tcase_add_test(tcase, s21_fabs_test_3);
  tcase_add_test(tcase, s21_fabs_test_4);
  tcase_add_test(tcase, s21_fabs_test_5);
  tcase_add_test(tcase, s21_fabs_test_6);
  tcase_add_test(tcase, s21_fabs_test_7);
  tcase_add_test(tcase, s21_fabs_test_8);
  tcase_add_test(tcase, s21_fabs_test_9);
  tcase_add_test(tcase, s21_fabs_test_10);
  tcase_add_test(tcase, s21_fabs_test_11);
  tcase_add_test(tcase, s21_fabs_test_12);
  tcase_add_test(tcase, s21_fabs_test_13);
  tcase_add_test(tcase, s21_fabs_test_14);
  tcase_add_test(tcase, s21_fabs_test_15);
  tcase_add_test(tcase, s21_fabs_test_16);
  tcase_add_test(tcase, s21_fabs_test_17);

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
