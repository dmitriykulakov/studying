#include "s21_math_test.h"

START_TEST(s21_pow_test_1) {
  ck_assert_ldouble_eq_tol(s21_pow(5, 2), pow(5, 2), 1E-6L);
}
END_TEST

START_TEST(s21_pow_test_2) {
  ck_assert_ldouble_eq_tol(s21_pow(10.000001, 4), pow(10.000001, 4), 1E-6L);
}
END_TEST

START_TEST(s21_pow_test_3) {
  ck_assert_ldouble_eq_tol(s21_pow(164563, 2.2), pow(164563, 2.2), 1E-4L);
}
END_TEST

START_TEST(s21_pow_test_4) {
  ck_assert_ldouble_eq_tol(s21_pow(0.4324, 3.2), pow(0.4324, 3.2), 1E-6L);
}
END_TEST

START_TEST(s21_pow_test_5) {
  ck_assert_ldouble_eq_tol(s21_pow(0.999999, 0.123), pow(0.999999, 0.123),
                           1E-6L);
}
END_TEST

START_TEST(s21_pow_test_6) {
  ck_assert_ldouble_eq_tol(s21_pow(0.001, 99), pow(0.001, 99), 1E-6L);
}
END_TEST

START_TEST(s21_pow_test_7) {
  ck_assert_ldouble_eq(s21_pow(94556563463643523, 94556),
                       pow(94556563463643523, 94556));
}
END_TEST

START_TEST(s21_pow_test_8) { ck_assert_ldouble_eq(s21_pow(0, 0), pow(0, 0)); }
END_TEST

START_TEST(s21_pow_test_9) { ck_assert_ldouble_eq(s21_pow(5, 0), pow(5, 0)); }
END_TEST

START_TEST(s21_pow_test_10) {
  ck_assert_ldouble_eq(s21_pow(-5, 0), pow(-5, 0));
}
END_TEST

START_TEST(s21_pow_test_11) {
  ck_assert_ldouble_eq(s21_pow(S21_NAN, 0), pow(NAN, 0));
}
END_TEST

START_TEST(s21_pow_test_12) {
  ck_assert_ldouble_eq(s21_pow(S21_INF_P, 0), pow(INFINITY, 0));
}
END_TEST

START_TEST(s21_pow_test_13) {
  ck_assert_ldouble_eq(s21_pow(S21_INF_N, 0), pow(-INFINITY, 0));
}
END_TEST

START_TEST(s21_pow_test_14) {
  ck_assert_ldouble_eq(s21_pow(S21_INF_P, 0), pow(INFINITY, 0));
}
END_TEST

START_TEST(s21_pow_test_15) { ck_assert_ldouble_eq(s21_pow(0, 5), pow(0, 5)); }
END_TEST

START_TEST(s21_pow_test_16) {
  ck_assert_ldouble_nan(s21_pow(S21_NAN, 5));
  ck_assert_ldouble_nan(pow(NAN, 5));
}
END_TEST

START_TEST(s21_pow_test_17) {
  ck_assert_ldouble_nan(s21_pow(S21_NAN, S21_NAN));
  ck_assert_ldouble_nan(pow(NAN, NAN));
}
END_TEST

START_TEST(s21_pow_test_18) {
  ck_assert_ldouble_nan(s21_pow(0, S21_NAN));
  ck_assert_ldouble_nan(pow(0, NAN));
}
END_TEST

START_TEST(s21_pow_test_19) {
  ck_assert_ldouble_nan(s21_pow(5, S21_NAN));
  ck_assert_ldouble_nan(pow(5, NAN));
}
END_TEST

START_TEST(s21_pow_test_20) {
  ck_assert_ldouble_nan(s21_pow(-5, S21_NAN));
  ck_assert_ldouble_nan(pow(-5, NAN));
}
END_TEST

START_TEST(s21_pow_test_21) {
  ck_assert_ldouble_nan(s21_pow(S21_INF_P, S21_NAN));
  ck_assert_ldouble_nan(pow(INFINITY, NAN));
}
END_TEST

START_TEST(s21_pow_test_22) {
  ck_assert_ldouble_nan(s21_pow(S21_INF_N, S21_NAN));
  ck_assert_ldouble_nan(pow(-INFINITY, NAN));
}
END_TEST

START_TEST(s21_pow_test_23) {
  ck_assert_ldouble_nan(s21_pow(S21_NAN, 5));
  ck_assert_ldouble_nan(pow(NAN, 5));
}
END_TEST

START_TEST(s21_pow_test_24) {
  ck_assert_ldouble_nan(s21_pow(S21_NAN, -5));
  ck_assert_ldouble_nan(pow(NAN, -5));
}
END_TEST

START_TEST(s21_pow_test_25) {
  ck_assert_ldouble_nan(s21_pow(S21_NAN, S21_INF_N));
  ck_assert_ldouble_nan(pow(NAN, -INFINITY));
}
END_TEST

START_TEST(s21_pow_test_26) {
  ck_assert_ldouble_eq(s21_pow(0, S21_INF_P), pow(0, INFINITY));
}
END_TEST

START_TEST(s21_pow_test_27) {
  ck_assert_ldouble_eq(s21_pow(5, S21_INF_N), pow(5, -INFINITY));
}
END_TEST

START_TEST(s21_pow_test_28) {
  ck_assert_ldouble_eq(s21_pow(-5, S21_INF_N), pow(-5, -INFINITY));
}
END_TEST

START_TEST(s21_pow_test_29) {
  ck_assert_ldouble_eq(s21_pow(S21_INF_P, S21_INF_N), pow(INFINITY, -INFINITY));
}
END_TEST

START_TEST(s21_pow_test_30) {
  ck_assert_ldouble_eq(s21_pow(S21_INF_N, S21_INF_N),
                       pow(-INFINITY, -INFINITY));
}
END_TEST

START_TEST(s21_pow_test_31) {
  ck_assert_ldouble_eq(s21_pow(S21_INF_P, -5), pow(INFINITY, -5));
}
END_TEST

START_TEST(s21_pow_test_32) {
  ck_assert_ldouble_eq(s21_pow(S21_INF_N, 5), pow(-INFINITY, 5));
}
END_TEST

START_TEST(s21_pow_test_33) {
  ck_assert_ldouble_eq(s21_pow(S21_INF_N, -5), pow(-INFINITY, -5));
}
END_TEST

START_TEST(s21_pow_test_34) {
  ck_assert_ldouble_eq(s21_pow(S21_INF_P, 5), pow(INFINITY, 5));
}
END_TEST

START_TEST(s21_pow_test_35) {
  ck_assert_ldouble_eq(s21_pow(0, -5), pow(0, -5));
}
END_TEST

START_TEST(s21_pow_test_36) {
  ck_assert_ldouble_eq(s21_pow(-5, S21_INF_P), pow(-5, INFINITY));
}
END_TEST

START_TEST(s21_pow_test_37) {
  ck_assert_ldouble_eq(s21_pow(S21_INF_P, S21_INF_P), pow(INFINITY, INFINITY));
}
END_TEST

START_TEST(s21_pow_test_38) {
  ck_assert_ldouble_eq(s21_pow(S21_INF_N, S21_INF_P), pow(-INFINITY, INFINITY));
}
END_TEST

START_TEST(s21_pow_test_39) {
  ck_assert_ldouble_eq(s21_pow(0, S21_INF_N), pow(0, -INFINITY));
}
END_TEST

START_TEST(s21_pow_test_40) {
  ck_assert_ldouble_eq_tol(s21_pow(-10.8, 3), pow(-10.8, 3), 1e-6);
}
END_TEST

START_TEST(s21_pow_test_41) {
  ck_assert_ldouble_eq_tol(s21_pow(12.6, -2.6), pow(12.6, -2.6), 1e-6);
}
END_TEST

START_TEST(s21_pow_test_42) {
  ck_assert_ldouble_eq_tol(s21_pow(-0.9755434567, -299),
                           pow(-0.9755434567, -299), 1e-6);
}
END_TEST

START_TEST(s21_pow_test_43) {
  ck_assert_ldouble_eq_tol(s21_pow(9755434567.33, -299.007),
                           pow(9755434567.33, -299.007), 1e-6);
}
END_TEST

START_TEST(s21_pow_test_44) {
  ck_assert_ldouble_eq_tol(s21_pow(-0.000000002, 3456789),
                           pow(-0.000000002, 3456789), 1e-6);
}
END_TEST

START_TEST(s21_pow_test_45) {
  ck_assert_ldouble_eq_tol(s21_pow(97, 3.7), pow(97, 3.7), 1e-6);
}
END_TEST

START_TEST(s21_pow_test_46) {
  ck_assert_ldouble_eq_tol(s21_pow(34567, 0.2), pow(34567, 0.2), 1e-6);
}
END_TEST

START_TEST(s21_pow_test_47) { ck_assert_double_nan(s21_pow(-2, 0.8)); }
END_TEST

START_TEST(s21_pow_test_48) { ck_assert_double_nan(s21_pow(-9, -4.8)); }
END_TEST

START_TEST(s21_pow_test_49) { ck_assert_ldouble_infinite(s21_pow(-0, -5.94)); }
END_TEST

START_TEST(s21_pow_test_50) {
  ck_assert_ldouble_eq_tol(s21_pow(-3, 5), pow(-3, 5), 1E-6L);
}
END_TEST

START_TEST(s21_pow_test_51) {
  ck_assert_ldouble_eq_tol(s21_pow(-3, -5), pow(-3, -5), 1E-6L);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[32m-=S21_POW_TEST=-\033[0m");
  TCase *tcase = tcase_create("core");

  tcase_add_test(tcase, s21_pow_test_1);
  tcase_add_test(tcase, s21_pow_test_2);
  tcase_add_test(tcase, s21_pow_test_3);
  tcase_add_test(tcase, s21_pow_test_4);
  tcase_add_test(tcase, s21_pow_test_5);
  tcase_add_test(tcase, s21_pow_test_6);
  tcase_add_test(tcase, s21_pow_test_7);
  tcase_add_test(tcase, s21_pow_test_8);
  tcase_add_test(tcase, s21_pow_test_9);
  tcase_add_test(tcase, s21_pow_test_10);
  tcase_add_test(tcase, s21_pow_test_11);
  tcase_add_test(tcase, s21_pow_test_12);
  tcase_add_test(tcase, s21_pow_test_13);
  tcase_add_test(tcase, s21_pow_test_14);
  tcase_add_test(tcase, s21_pow_test_15);
  tcase_add_test(tcase, s21_pow_test_16);
  tcase_add_test(tcase, s21_pow_test_17);
  tcase_add_test(tcase, s21_pow_test_18);
  tcase_add_test(tcase, s21_pow_test_19);
  tcase_add_test(tcase, s21_pow_test_20);
  tcase_add_test(tcase, s21_pow_test_21);
  tcase_add_test(tcase, s21_pow_test_22);
  tcase_add_test(tcase, s21_pow_test_23);
  tcase_add_test(tcase, s21_pow_test_24);
  tcase_add_test(tcase, s21_pow_test_25);
  tcase_add_test(tcase, s21_pow_test_26);
  tcase_add_test(tcase, s21_pow_test_27);
  tcase_add_test(tcase, s21_pow_test_28);
  tcase_add_test(tcase, s21_pow_test_29);
  tcase_add_test(tcase, s21_pow_test_30);
  tcase_add_test(tcase, s21_pow_test_31);
  tcase_add_test(tcase, s21_pow_test_32);
  tcase_add_test(tcase, s21_pow_test_33);
  tcase_add_test(tcase, s21_pow_test_34);
  tcase_add_test(tcase, s21_pow_test_35);
  tcase_add_test(tcase, s21_pow_test_36);
  tcase_add_test(tcase, s21_pow_test_37);
  tcase_add_test(tcase, s21_pow_test_38);
  tcase_add_test(tcase, s21_pow_test_39);
  tcase_add_test(tcase, s21_pow_test_40);
  tcase_add_test(tcase, s21_pow_test_41);
  tcase_add_test(tcase, s21_pow_test_42);
  tcase_add_test(tcase, s21_pow_test_43);
  tcase_add_test(tcase, s21_pow_test_44);
  tcase_add_test(tcase, s21_pow_test_45);
  tcase_add_test(tcase, s21_pow_test_46);
  tcase_add_test(tcase, s21_pow_test_47);
  tcase_add_test(tcase, s21_pow_test_48);
  tcase_add_test(tcase, s21_pow_test_49);
  tcase_add_test(tcase, s21_pow_test_50);
  tcase_add_test(tcase, s21_pow_test_51);

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
