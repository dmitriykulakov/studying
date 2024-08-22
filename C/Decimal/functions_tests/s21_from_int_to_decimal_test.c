#include "s21_decimal_test.h"

START_TEST(s21_from_int_to_decimal_test_1) {
  int test_int = 0;

  ck_assert_int_eq(s21_from_int_to_decimal(test_int, NULL), RETURN_VALUE_1);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_2) {
  int test_int = 0;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_int_to_decimal(test_int, &test_var_1),
                   RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[0], (unsigned int)test_int);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[3], 0x00000000);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_3) {
  int test_int = +10;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_int_to_decimal(test_int, &test_var_1),
                   RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[0], (unsigned int)test_int);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[3], 0x00000000);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_4) {
  int test_int = -10;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_int_to_decimal(test_int, &test_var_1),
                   RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[0],
                    (unsigned int)abs(test_int));
  ck_assert_uint_eq((unsigned int)test_var_1.bits[3], 0x80000000);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_5) {
  int test_int = +123456;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_int_to_decimal(test_int, &test_var_1),
                   RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[0], (unsigned int)test_int);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[3], 0x00000000);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_6) {
  int test_int = -123456;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_int_to_decimal(test_int, &test_var_1),
                   RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[0],
                    (unsigned int)abs(test_int));
  ck_assert_uint_eq((unsigned int)test_var_1.bits[3], 0x80000000);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_7) {
  int test_int = INT_MAX;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_int_to_decimal(test_int, &test_var_1),
                   RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[0], (unsigned int)test_int);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[3], 0x00000000);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_8) {
  int test_int = INT_MIN;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_int_to_decimal(test_int, &test_var_1),
                   RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[0],
                    (unsigned int)abs(test_int));
  ck_assert_uint_eq((unsigned int)test_var_1.bits[3], 0x80000000);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_9) {
  int test_int = INT_MAX - 1;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_int_to_decimal(test_int, &test_var_1),
                   RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[0], (unsigned int)test_int);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[3], 0x00000000);
}
END_TEST

START_TEST(s21_from_int_to_decimal_test_10) {
  int test_int = INT_MIN + 1;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_int_to_decimal(test_int, &test_var_1),
                   RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[0],
                    (unsigned int)abs(test_int));
  ck_assert_uint_eq((unsigned int)test_var_1.bits[3], 0x80000000);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[32m s21_from_int_to_decimal_test \033[0m");
  TCase *tcase = tcase_create("core");

  tcase_add_test(tcase, s21_from_int_to_decimal_test_1);
  tcase_add_test(tcase, s21_from_int_to_decimal_test_2);
  tcase_add_test(tcase, s21_from_int_to_decimal_test_3);
  tcase_add_test(tcase, s21_from_int_to_decimal_test_4);
  tcase_add_test(tcase, s21_from_int_to_decimal_test_5);
  tcase_add_test(tcase, s21_from_int_to_decimal_test_6);
  tcase_add_test(tcase, s21_from_int_to_decimal_test_7);
  tcase_add_test(tcase, s21_from_int_to_decimal_test_8);
  tcase_add_test(tcase, s21_from_int_to_decimal_test_9);
  tcase_add_test(tcase, s21_from_int_to_decimal_test_10);

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
