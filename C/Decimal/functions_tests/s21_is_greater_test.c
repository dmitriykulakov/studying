#include "s21_decimal_test.h"

START_TEST(is_greater_1) {
  s21_decimal number1;
  s21_decimal number2;
  s21_decimal number3;
  s21_decimal number4;
  s21_decimal number5;
  s21_decimal number6;
  number1.bits[0] = 0xffffffff;
  number1.bits[1] = 0xffffffff;
  number1.bits[2] = 0b11111111111111111111111111111111;
  number1.bits[3] = 0x801E0000;

  number2.bits[0] = 0x12345678;
  number2.bits[1] = 0x12345678;
  number2.bits[2] = 0b10010001101000101011001111000;
  number2.bits[3] = 0b10000000000111100000000000000000;

  number3.bits[0] = 0;
  number3.bits[1] = 0;
  number3.bits[2] = 0b0;
  number3.bits[3] = 0b10000000000111100000000000000000;

  number4.bits[0] = 0x12345679;
  number4.bits[1] = 0x12345678;
  number4.bits[2] = 0b10010001101000101011001111000;
  number4.bits[3] = 0b10000000000111100000000000000000;

  number5.bits[0] = 0xffffffff;
  number5.bits[1] = 0xffffffff;
  number5.bits[2] = 0b11111111111111111111111111111111;
  number5.bits[3] = 0x00020000;

  number6.bits[0] = 0xffffffff;
  number6.bits[1] = 0xffffffff;
  number6.bits[2] = 0b11111111111111111111111111111111;
  number6.bits[3] = 0x00010000;
  ck_assert_int_eq(s21_is_greater(number1, number2), 0);
  ck_assert_int_eq(s21_is_greater(number1, number1), 0);
  ck_assert_int_eq(s21_is_greater(number1, number3), 0);
  ck_assert_int_eq(s21_is_greater(number6, number3), 1);
  ck_assert_int_eq(s21_is_greater(number3, number1), 1);
  ck_assert_int_eq(s21_is_greater(number3, number6), 0);
  ck_assert_int_eq(s21_is_greater(number3, number3), 0);
  ck_assert_int_eq(s21_is_greater(number2, number4), 1);
  ck_assert_int_eq(s21_is_greater(number1, number5), 0);
  ck_assert_int_eq(s21_is_greater(number5, number6), 0);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[45m-=S21_IS_GREATER=-\033[0m");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, is_greater_1);

  suite_add_tcase(suite, tc);
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