#include "s21_math_test.h"

START_TEST(s21_floor_test_1) {
  ck_assert_ldouble_eq(s21_floor(1254354.9999999), floor(1254354.9999999));
}
END_TEST

START_TEST(s21_floor_test_2) {
  ck_assert_ldouble_eq(s21_floor(-1254354.9999999), floor(-1254354.9999999));
}
END_TEST

START_TEST(s21_floor_test_3) {
  ck_assert_ldouble_eq(s21_floor(1254354), floor(1254354));
}
END_TEST

START_TEST(s21_floor_test_4) {
  ck_assert_ldouble_eq(s21_floor(-1254354), floor(-1254354));
}
END_TEST

START_TEST(s21_floor_test_5) {
  ck_assert_ldouble_eq(s21_floor(1254354.0000001), floor(1254354.0000001));
}
END_TEST

START_TEST(s21_floor_test_6) {
  ck_assert_ldouble_eq(s21_floor(-1254354.0000001), floor(-1254354.0000001));
}
END_TEST

START_TEST(s21_floor_test_7) {
  ck_assert_ldouble_eq(s21_floor(12545435435435345354.99999999),
                       floor(12545435435435345354.99999999));
}
END_TEST

START_TEST(s21_floor_test_8) {
  ck_assert_ldouble_eq(s21_floor(12545435435435345354.0000001),
                       floor(12545435435435345354.0000001));
}
END_TEST

START_TEST(s21_floor_test_9) {
  ck_assert_ldouble_eq(s21_floor(-12545435435435345354.0000001),
                       floor(-12545435435435345354.0000001));
}
END_TEST

START_TEST(s21_floor_test_10) {
  ck_assert_ldouble_eq(s21_floor(2.5), floor(2.5));
}
END_TEST

START_TEST(s21_floor_test_11) {
  ck_assert_ldouble_eq(s21_floor(-2.5), floor(-2.5));
}
END_TEST

START_TEST(s21_floor_test_12) {
  ck_assert_ldouble_nan(s21_floor(S21_NAN));
  ck_assert_ldouble_nan(floor(NAN));
}
END_TEST

START_TEST(s21_floor_test_13) {
  ck_assert_ldouble_eq(s21_floor(S21_INF_P), floor(INFINITY));
}
END_TEST

START_TEST(s21_floor_test_14) {
  ck_assert_ldouble_eq(s21_floor(S21_INF_N), floor(-INFINITY));
}
END_TEST

START_TEST(s21_floor_test_15) {
  ck_assert_ldouble_eq(s21_floor(-0), floor(-0));
}
END_TEST

START_TEST(s21_floor_test_16) {
  ck_assert_ldouble_eq(s21_floor(+0), floor(+0));
}
END_TEST

START_TEST(s21_floor_test_17) {
  ck_assert_ldouble_eq_tol(s21_floor(0.345678789987), floor(0.345678789987),
                           1e-6);
}
END_TEST

START_TEST(s21_floor_test_18) {
  for (double i = -10; i <= 10; i += 1) {
    ck_assert_ldouble_eq_tol(s21_floor(i / 10), floor(i / 10), 1e-6);
  }
}
END_TEST

START_TEST(s21_floor_test_19) {
  ck_assert_ldouble_eq_tol(s21_floor((double)S21_E), floor((double)S21_E),
                           1e-6);
}
END_TEST

START_TEST(s21_floor_test_20) {
  ck_assert_ldouble_eq_tol(s21_floor((double)S21_PI), floor((double)S21_PI),
                           1e-6);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[32m-=S21_FLOOR_TEST=-\033[0m");
  TCase *tcase = tcase_create("core");

  suite_add_tcase(suite, tcase);
  tcase_add_test(tcase, s21_floor_test_1);
  tcase_add_test(tcase, s21_floor_test_2);
  tcase_add_test(tcase, s21_floor_test_3);
  tcase_add_test(tcase, s21_floor_test_4);
  tcase_add_test(tcase, s21_floor_test_5);
  tcase_add_test(tcase, s21_floor_test_6);
  tcase_add_test(tcase, s21_floor_test_7);
  tcase_add_test(tcase, s21_floor_test_8);
  tcase_add_test(tcase, s21_floor_test_9);
  tcase_add_test(tcase, s21_floor_test_10);
  tcase_add_test(tcase, s21_floor_test_11);
  tcase_add_test(tcase, s21_floor_test_12);
  tcase_add_test(tcase, s21_floor_test_13);
  tcase_add_test(tcase, s21_floor_test_14);
  tcase_add_test(tcase, s21_floor_test_15);
  tcase_add_test(tcase, s21_floor_test_16);
  tcase_add_test(tcase, s21_floor_test_17);
  tcase_add_test(tcase, s21_floor_test_18);
  tcase_add_test(tcase, s21_floor_test_19);
  tcase_add_test(tcase, s21_floor_test_20);

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
