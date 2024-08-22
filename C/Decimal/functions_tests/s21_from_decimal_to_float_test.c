#include "s21_decimal_test.h"

START_TEST(s21_from_decimal_to_float_test_1) {
  s21_decimal test_var_1;

  test_var_1.bits[0] = 0;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0;

  ck_assert_int_eq(s21_from_decimal_to_float(test_var_1, NULL), RETURN_VALUE_1);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_2) {
  float test_float = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 0;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x00000000;

  ck_assert_int_eq(s21_from_decimal_to_float(test_var_1, &test_float),
                   RETURN_VALUE_0);
  ck_assert_float_eq(0.0, test_float);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_3) {
  float test_float = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 0;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x80000000;

  ck_assert_int_eq(s21_from_decimal_to_float(test_var_1, &test_float),
                   RETURN_VALUE_0);
  ck_assert_float_eq(0.0, test_float);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_4) {
  float test_float = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 123;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x00000000;

  ck_assert_int_eq(s21_from_decimal_to_float(test_var_1, &test_float),
                   RETURN_VALUE_0);
  ck_assert_float_eq(123.0, test_float);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_5) {
  float test_float = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 123;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x80000000;

  ck_assert_int_eq(s21_from_decimal_to_float(test_var_1, &test_float),
                   RETURN_VALUE_0);
  ck_assert_float_eq(-123.0, test_float);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_6) {
  float test_float = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 1234567;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x00040000;

  ck_assert_int_eq(s21_from_decimal_to_float(test_var_1, &test_float),
                   RETURN_VALUE_0);
  ck_assert_float_eq(123.4567, test_float);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_7) {
  float test_float = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 1234567;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x80040000;

  ck_assert_int_eq(s21_from_decimal_to_float(test_var_1, &test_float),
                   RETURN_VALUE_0);
  ck_assert_float_eq(-123.4567, test_float);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_8) {
  float test_float = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 123;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x000f0000;

  ck_assert_int_eq(s21_from_decimal_to_float(test_var_1, &test_float),
                   RETURN_VALUE_0);
  ck_assert_float_eq(1.23e-13, test_float);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_9) {
  float test_float = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 123;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x800f0000;

  ck_assert_int_eq(s21_from_decimal_to_float(test_var_1, &test_float),
                   RETURN_VALUE_0);
  ck_assert_float_eq(-1.23e-13, test_float);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_10) {
  float test_float = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 0xffffffff;
  test_var_1.bits[1] = 0xffffffff;
  test_var_1.bits[2] = 0xffffffff;
  test_var_1.bits[3] = 0x00000000;

  ck_assert_int_eq(s21_from_decimal_to_float(test_var_1, &test_float),
                   RETURN_VALUE_0);
  ck_assert_float_eq(7.9228162514264E+28, test_float);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_11) {
  float test_float = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 0xffffffff;
  test_var_1.bits[1] = 0xffffffff;
  test_var_1.bits[2] = 0xffffffff;
  test_var_1.bits[3] = 0x80000000;

  ck_assert_int_eq(s21_from_decimal_to_float(test_var_1, &test_float),
                   RETURN_VALUE_0);
  ck_assert_float_eq(-7.9228162514264E+28, test_float);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_12) {
  float test_float = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 0xffffffff;
  test_var_1.bits[1] = 0xffffffff;
  test_var_1.bits[2] = 0xffffffff;
  test_var_1.bits[3] = 0x001c0000;

  ck_assert_int_eq(s21_from_decimal_to_float(test_var_1, &test_float),
                   RETURN_VALUE_0);
  ck_assert_float_eq(7.9228162514264, test_float);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_13) {
  float test_float = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 0xffffffff;
  test_var_1.bits[1] = 0xffffffff;
  test_var_1.bits[2] = 0xffffffff;
  test_var_1.bits[3] = 0x801c0000;

  ck_assert_int_eq(s21_from_decimal_to_float(test_var_1, &test_float),
                   RETURN_VALUE_0);
  ck_assert_float_eq(-7.9228162514264, test_float);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_14) {
  float test_float = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 1;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x001c0000;

  ck_assert_int_eq(s21_from_decimal_to_float(test_var_1, &test_float),
                   RETURN_VALUE_0);
  ck_assert_float_eq(1.0e-28, test_float);
}
END_TEST

START_TEST(s21_from_decimal_to_float_test_15) {
  float test_float = 0;
  s21_decimal test_var_1;

  test_var_1.bits[0] = 1;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x801c0000;

  ck_assert_int_eq(s21_from_decimal_to_float(test_var_1, &test_float),
                   RETURN_VALUE_0);
  ck_assert_float_eq(-1.0e-28, test_float);
}
END_TEST

Suite *suite(void) {
  Suite *suite =
      suite_create("\033[32m s21_from_decimal_to_float_test \033[0m");
  TCase *tcase = tcase_create("core");

  tcase_add_test(tcase, s21_from_decimal_to_float_test_1);
  tcase_add_test(tcase, s21_from_decimal_to_float_test_2);
  tcase_add_test(tcase, s21_from_decimal_to_float_test_3);
  tcase_add_test(tcase, s21_from_decimal_to_float_test_4);
  tcase_add_test(tcase, s21_from_decimal_to_float_test_5);
  tcase_add_test(tcase, s21_from_decimal_to_float_test_6);
  tcase_add_test(tcase, s21_from_decimal_to_float_test_7);
  tcase_add_test(tcase, s21_from_decimal_to_float_test_8);
  tcase_add_test(tcase, s21_from_decimal_to_float_test_9);
  tcase_add_test(tcase, s21_from_decimal_to_float_test_10);
  tcase_add_test(tcase, s21_from_decimal_to_float_test_11);
  tcase_add_test(tcase, s21_from_decimal_to_float_test_12);
  tcase_add_test(tcase, s21_from_decimal_to_float_test_13);
  tcase_add_test(tcase, s21_from_decimal_to_float_test_14);
  tcase_add_test(tcase, s21_from_decimal_to_float_test_15);

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
