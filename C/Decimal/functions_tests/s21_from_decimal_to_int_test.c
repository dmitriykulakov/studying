#include "s21_decimal_test.h"

START_TEST(s21_from_decimal_to_int_test_1) {
  s21_decimal test_var_1;

  test_var_1.bits[0] = 0;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0;

  ck_assert_int_eq(s21_from_decimal_to_int(test_var_1, NULL), RETURN_VALUE_1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_2) {
  int test_int = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 123;
  test_var_1.bits[1] = 0xffffffff;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x80000000;

  ck_assert_int_eq(s21_from_decimal_to_int(test_var_1, &test_int),
                   RETURN_VALUE_1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_3) {
  int test_int = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 123;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0xffffffff;
  test_var_1.bits[3] = 0x00000000;

  ck_assert_int_eq(s21_from_decimal_to_int(test_var_1, &test_int),
                   RETURN_VALUE_1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_4) {
  int test_int = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 123;
  test_var_1.bits[1] = 0xffffffff;
  test_var_1.bits[2] = 0xffffffff;
  test_var_1.bits[3] = 0x80000000;

  ck_assert_int_eq(s21_from_decimal_to_int(test_var_1, &test_int),
                   RETURN_VALUE_1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_5) {
  int test_int = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 0x80000000;  // INT_MAX+1
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x00000000;

  ck_assert_int_eq(s21_from_decimal_to_int(test_var_1, &test_int),
                   RETURN_VALUE_1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_6) {
  int test_int = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 0x80000001;  // ABS(-INT_MIN-1)=ABS((-INT_MAX-1)-1)
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x80000000;

  ck_assert_int_eq(s21_from_decimal_to_int(test_var_1, &test_int),
                   RETURN_VALUE_1);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_7) {
  int test_int = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 0x7fffffff;  // INT_MAX
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x00000000;

  ck_assert_int_eq(s21_from_decimal_to_int(test_var_1, &test_int),
                   RETURN_VALUE_0);
  ck_assert_int_eq(test_int, INT_MAX);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_8) {
  int test_int = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 0x80000000;  // INT_MIN
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x80000000;

  ck_assert_int_eq(s21_from_decimal_to_int(test_var_1, &test_int),
                   RETURN_VALUE_0);
  ck_assert_int_eq(test_int, INT_MIN);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_9) {
  int test_int = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 0;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x00000000;

  ck_assert_int_eq(s21_from_decimal_to_int(test_var_1, &test_int),
                   RETURN_VALUE_0);
  ck_assert_int_eq(test_int, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_10) {
  int test_int = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 0;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x80000000;

  ck_assert_int_eq(s21_from_decimal_to_int(test_var_1, &test_int),
                   RETURN_VALUE_0);
  ck_assert_int_eq(test_int, 0);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_11) {
  int test_int = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 12345;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x00000000;

  ck_assert_int_eq(s21_from_decimal_to_int(test_var_1, &test_int),
                   RETURN_VALUE_0);
  ck_assert_int_eq(test_int, 12345);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_12) {
  int test_int = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 12345;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x80000000;

  ck_assert_int_eq(s21_from_decimal_to_int(test_var_1, &test_int),
                   RETURN_VALUE_0);
  ck_assert_int_eq(test_int, -12345);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_13) {
  int test_int = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 12345;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x00020000;

  ck_assert_int_eq(s21_from_decimal_to_int(test_var_1, &test_int),
                   RETURN_VALUE_0);
  ck_assert_int_eq(test_int, 123);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_14) {
  int test_int = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 12345;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x80020000;

  ck_assert_int_eq(s21_from_decimal_to_int(test_var_1, &test_int),
                   RETURN_VALUE_0);
  ck_assert_int_eq(test_int, -123);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_15) {
  int test_int = 0;
  s21_decimal test_var_1;

  // +2107483647
  // +2107483647.785045367e+9 = +1d3f4936 342c0d77
  test_var_1.bits[0] = 0x342c0d77;
  test_var_1.bits[1] = 0x1d3f4936;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x00090000;

  ck_assert_int_eq(s21_from_decimal_to_int(test_var_1, &test_int),
                   RETURN_VALUE_0);
  ck_assert_int_eq(test_int, 2107483647);
}
END_TEST

START_TEST(s21_from_decimal_to_int_test_16) {
  int test_int = 0;
  s21_decimal test_var_1;

  // -2107483647
  // -2107483647.785045367e+9 = -1d3f4936 342c0d77
  test_var_1.bits[0] = 0x342c0d77;
  test_var_1.bits[1] = 0x1d3f4936;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x80090000;

  ck_assert_int_eq(s21_from_decimal_to_int(test_var_1, &test_int),
                   RETURN_VALUE_0);
  ck_assert_int_eq(test_int, -2107483647);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[32m s21_from_decimal_to_int_test \033[0m");
  TCase *tcase = tcase_create("core");

  tcase_add_test(tcase, s21_from_decimal_to_int_test_1);
  tcase_add_test(tcase, s21_from_decimal_to_int_test_2);
  tcase_add_test(tcase, s21_from_decimal_to_int_test_3);
  tcase_add_test(tcase, s21_from_decimal_to_int_test_4);
  tcase_add_test(tcase, s21_from_decimal_to_int_test_5);
  tcase_add_test(tcase, s21_from_decimal_to_int_test_6);
  tcase_add_test(tcase, s21_from_decimal_to_int_test_7);
  tcase_add_test(tcase, s21_from_decimal_to_int_test_8);
  tcase_add_test(tcase, s21_from_decimal_to_int_test_9);
  tcase_add_test(tcase, s21_from_decimal_to_int_test_10);
  tcase_add_test(tcase, s21_from_decimal_to_int_test_11);
  tcase_add_test(tcase, s21_from_decimal_to_int_test_12);
  tcase_add_test(tcase, s21_from_decimal_to_int_test_13);
  tcase_add_test(tcase, s21_from_decimal_to_int_test_14);
  tcase_add_test(tcase, s21_from_decimal_to_int_test_15);
  tcase_add_test(tcase, s21_from_decimal_to_int_test_16);

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
