#include "s21_decimal_test.h"

START_TEST(div_1) {
  s21_decimal number1;
  s21_decimal number2;
  s21_decimal number3;
  s21_decimal result;

  number1.bits[0] = 0xffffffff;
  number1.bits[1] = 0xffffffff;
  number1.bits[2] = 0b11111111111111111111111111111111;
  number1.bits[3] = 0x801E0000;

  number2.bits[0] = 0x12345678;
  number2.bits[1] = 0x12345678;
  number2.bits[2] = 0b10010001101000101011001111000;
  number2.bits[3] = 0b10000000000000000000000000000000;

  number3.bits[0] = 0;
  number3.bits[1] = 0;
  number3.bits[2] = 0b0;
  number3.bits[3] = 0b10000000000111100000000000000000;

  ck_assert_int_eq(s21_div(number1, number3, &result), 3);

  ck_assert_int_eq(s21_div(number3, number3, &result), 3);

  ck_assert_int_eq(s21_div(number3, number2, &result), 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(div_2) {
  s21_decimal number1;
  s21_decimal number2;
  s21_decimal number3;
  s21_decimal number4;
  s21_decimal number5;
  s21_decimal number6;
  s21_decimal number7;
  s21_decimal result;

  number1.bits[0] = 0xffffffff;
  number1.bits[1] = 0xffffffff;
  number1.bits[2] = 0xffffffff;
  number1.bits[3] = 0x00020000;

  number2.bits[0] = 0x12345678;
  number2.bits[1] = 0x12345678;
  number2.bits[2] = 0x12345678;
  number2.bits[3] = 0x00000000;

  number3.bits[0] = 0x00000001;
  number3.bits[1] = 0x00000000;
  number3.bits[2] = 0x00000000;
  number3.bits[3] = 0x80040000;

  number4.bits[0] = 0xffffffff;
  number4.bits[1] = 0xffffffff;
  number4.bits[2] = 0xffffffff;
  number4.bits[3] = 0x00000000;

  number5.bits[0] = 0x12345678;
  number5.bits[1] = 0x12345678;
  number5.bits[2] = 0x12345678;
  number5.bits[3] = 0x801b0000;

  number6.bits[0] = 0x00000001;
  number6.bits[1] = 0x00000000;
  number6.bits[2] = 0x00000000;
  number6.bits[3] = 0x80000000;

  number7.bits[0] = 0x00000001;
  number7.bits[1] = 0x00000000;
  number7.bits[2] = 0x00000000;
  number7.bits[3] = 0x001c0000;

  ck_assert_int_eq(s21_div(number1, number1, &result), 0);
  ck_assert_int_eq((unsigned int)result.bits[2], 0x204fce5e);
  ck_assert_int_eq((unsigned int)result.bits[1], 0x3e250261);
  ck_assert_int_eq((unsigned int)result.bits[0], 0x10000000);
  ck_assert_int_eq((unsigned int)result.bits[3], 0x001c0000);

  ck_assert_int_eq(s21_div(number1, number2, &result), 0);
  ck_assert_int_eq((unsigned int)result.bits[2], 0x048b3905);
  ck_assert_int_eq((unsigned int)result.bits[1], 0x62d15ffe);
  ck_assert_int_eq((unsigned int)result.bits[0], 0x2d767b9b);
  ck_assert_int_eq((unsigned int)result.bits[3], 0x001c0000);

  ck_assert_int_eq(s21_div(number1, number3, &result), 2);

  ck_assert_int_eq(s21_div(number2, number1, &result), 0);
  ck_assert_int_eq((unsigned int)result.bits[2], 0xe5c5bb7a);
  ck_assert_int_eq((unsigned int)result.bits[1], 0xfe9fbd42);
  ck_assert_int_eq((unsigned int)result.bits[0], 0x1970f490);
  ck_assert_int_eq((unsigned int)result.bits[3], 0x001c0000);

  ck_assert_int_eq(s21_div(number4, number5, &result), 0);
  ck_assert_int_eq((unsigned int)result.bits[2], 0x2d703a35);
  ck_assert_int_eq((unsigned int)result.bits[1], 0xdc2dbfed);
  ck_assert_int_eq((unsigned int)result.bits[0], 0xc6a0d40d);
  ck_assert_int_eq((unsigned int)result.bits[3], 0x80000000);

  ck_assert_int_eq(s21_div(number1, number6, &result), 0);
  ck_assert_int_eq((unsigned int)result.bits[2], (unsigned int)number1.bits[2]);
  ck_assert_int_eq((unsigned int)result.bits[1], (unsigned int)number1.bits[1]);
  ck_assert_int_eq((unsigned int)result.bits[0], (unsigned int)number1.bits[0]);
  ck_assert_int_eq((unsigned int)result.bits[3], 0x80020000);

  ck_assert_int_eq(s21_div(number6, number1, &result), 0);
  ck_assert_int_eq((unsigned int)result.bits[2], 0x00000000);
  ck_assert_int_eq((unsigned int)result.bits[1], 0x00000000);
  ck_assert_int_eq((unsigned int)result.bits[0], 0x0000000d);
  ck_assert_int_eq((unsigned int)result.bits[3], 0x801c0000);

  ck_assert_int_eq(s21_div(number1, number7, &result), 1);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[45m-=S21_DIV=-\033[0m");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, div_1);
  tcase_add_test(tc, div_2);

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