#include "s21_decimal_test.h"

START_TEST(mul_1) {
  s21_decimal number1;
  s21_decimal number2;
  s21_decimal number3;
  s21_decimal number4;
  s21_decimal number5;
  s21_decimal number6;
  s21_decimal number7;
  s21_decimal number8;
  s21_decimal number9;

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

  number4.bits[0] = 0x12345679;
  number4.bits[1] = 0x12345678;
  number4.bits[2] = 0b10010001101000101011001111000;
  number4.bits[3] = 0b10000000000000000000000000000000;

  number5.bits[0] = 0xffffffff;
  number5.bits[1] = 0xffffffff;
  number5.bits[2] = 0b11111111111111111111111111111111;
  number5.bits[3] = 0x00020000;

  number6.bits[0] = 0xffffffff;
  number6.bits[1] = 0xffffffff;
  number6.bits[2] = 0b11111111111111111111111111111111;
  number6.bits[3] = 0x00010000;

  number7.bits[0] = 0xffffffff;
  number7.bits[1] = 0xffffffff;
  number7.bits[2] = 0xffffffff;
  number7.bits[3] = 0x80000000;

  number8.bits[0] = 0x00000001;
  number8.bits[1] = 0x00000000;
  number8.bits[2] = 0x00000000;
  number8.bits[3] = 0x00000000;

  number9.bits[0] = 0x00000001;
  number9.bits[1] = 0x00000000;
  number9.bits[2] = 0x00000000;
  number9.bits[3] = 0x80000000;

  ck_assert_int_eq(s21_mul(number1, number3, &result), 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[3], 0);

  ck_assert_int_eq(s21_mul(number3, number3, &result), 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[3], 0);

  ck_assert_int_eq(s21_mul(number3, number2, &result), 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[3], 0);

  ck_assert_int_eq(s21_mul(number7, number8, &result), 0);
  ck_assert_int_eq(result.bits[2], number7.bits[2]);
  ck_assert_int_eq(result.bits[1], number7.bits[1]);
  ck_assert_int_eq(result.bits[0], number7.bits[0]);
  ck_assert_int_eq(result.bits[3], number7.bits[3]);

  ck_assert_int_eq(s21_mul(number7, number9, &result), 0);
  ck_assert_int_eq(result.bits[2], number7.bits[2]);
  ck_assert_int_eq(result.bits[1], number7.bits[1]);
  ck_assert_int_eq(result.bits[0], number7.bits[0]);
  ck_assert_int_eq(result.bits[3], 0);

  ck_assert_int_eq(s21_mul(number5, number6, &result), 1);

  ck_assert_int_eq(s21_mul(number5, number7, &result), 2);

  ck_assert_int_eq(s21_mul(number2, number4, &result), 1);
}
END_TEST

START_TEST(mul_2) {
  s21_decimal number1;
  s21_decimal number2;
  s21_decimal number3;
  s21_decimal result;
  number1.bits[0] = 0x12345678;
  number1.bits[1] = 0x12345678;
  number1.bits[2] = 0x12345678;
  number1.bits[3] = 0x00100000;

  number2.bits[0] = 0x12345678;
  number2.bits[1] = 0x12345678;
  number2.bits[2] = 0x12345678;
  number2.bits[3] = 0x001a0000;

  number3.bits[0] = 0x12345678;
  number3.bits[1] = 0x12345678;
  number3.bits[2] = 0x12345678;
  number3.bits[3] = 0x80100000;

  ck_assert_int_eq(s21_mul(number1, number1, &result), 0);
  ck_assert_int_eq((unsigned int)result.bits[2], 0x66905afa);
  ck_assert_int_eq((unsigned int)result.bits[1], 0x3902c1ed);
  ck_assert_int_eq((unsigned int)result.bits[0], 0xd5b8623c);
  ck_assert_int_eq((unsigned int)result.bits[3], 0x00050000);

  ck_assert_int_eq(s21_mul(number1, number2, &result), 0);
  ck_assert_int_eq((unsigned int)result.bits[2], 0x66905afa);
  ck_assert_int_eq((unsigned int)result.bits[1], 0x3902c1ed);
  ck_assert_int_eq((unsigned int)result.bits[0], 0xd5b8623c);
  ck_assert_int_eq((unsigned int)result.bits[3], 0x000f0000);

  ck_assert_int_eq(s21_mul(number3, number3, &result), 0);
  ck_assert_int_eq((unsigned int)result.bits[2], 0x66905afa);
  ck_assert_int_eq((unsigned int)result.bits[1], 0x3902c1ed);
  ck_assert_int_eq((unsigned int)result.bits[0], 0xd5b8623c);
  ck_assert_int_eq((unsigned int)result.bits[3], 0x00050000);

  ck_assert_int_eq(s21_mul(number1, number3, &result), 0);
  ck_assert_int_eq((unsigned int)result.bits[2], 0x66905afa);
  ck_assert_int_eq((unsigned int)result.bits[1], 0x3902c1ed);
  ck_assert_int_eq((unsigned int)result.bits[0], 0xd5b8623c);
  ck_assert_int_eq((unsigned int)result.bits[3], 0x80050000);
}
END_TEST

START_TEST(mul_3) {
  s21_decimal number1;
  s21_decimal number2;
  s21_decimal number3;
  s21_decimal number4;
  s21_decimal number5;
  s21_decimal number6;
  s21_decimal result;
  number1.bits[0] = 0x12345678;
  number1.bits[1] = 0x12345678;
  number1.bits[2] = 0x12345678;
  number1.bits[3] = 0x001c0000;

  number2.bits[0] = 0x00000001;
  number2.bits[1] = 0x00000000;
  number2.bits[2] = 0x00000000;
  number2.bits[3] = 0x00010000;

  number3.bits[0] = 0x00000001;
  number3.bits[1] = 0x00000000;
  number3.bits[2] = 0x00000000;
  number3.bits[3] = 0x00020000;

  number4.bits[0] = 0x00000001;
  number4.bits[1] = 0x00000000;
  number4.bits[2] = 0x00000000;
  number4.bits[3] = 0x00050000;

  number5.bits[0] = 0xFFFFFEB1;
  number5.bits[1] = 0xFFFFFFFF;
  number5.bits[2] = 0xFFFFFFFF;
  number5.bits[3] = 0x001c0000;

  number6.bits[0] = 0xFFFFFEB0;
  number6.bits[1] = 0xFFFFFFFF;
  number6.bits[2] = 0xFFFFFFFF;
  number6.bits[3] = 0x001c0000;

  ck_assert_int_eq(s21_mul(number1, number2, &result), 0);
  ck_assert_int_eq((unsigned int)result.bits[2], 0x01D208A5);
  ck_assert_int_eq((unsigned int)result.bits[1], 0x9B6BA23F);
  ck_assert_int_eq((unsigned int)result.bits[0], 0x35053BD9);
  ck_assert_int_eq((unsigned int)result.bits[3], 0x001c0000);

  ck_assert_int_eq(s21_mul(number1, number3, &result), 0);
  ck_assert_int_eq((unsigned int)result.bits[2], 0x002E9A76);
  ck_assert_int_eq((unsigned int)result.bits[1], 0xF5F129D3);
  ck_assert_int_eq((unsigned int)result.bits[0], 0x1EE6EC62);
  ck_assert_int_eq((unsigned int)result.bits[3], 0x001c0000);

  ck_assert_int_eq(s21_mul(number1, number4, &result), 0);
  ck_assert_int_eq((unsigned int)result.bits[2], 0x00000BEE);
  ck_assert_int_eq((unsigned int)result.bits[1], 0x32EF16D3);
  ck_assert_int_eq((unsigned int)result.bits[0], 0x693F34F9);
  ck_assert_int_eq((unsigned int)result.bits[3], 0x001c0000);

  ck_assert_int_eq(s21_mul(number5, number2, &result), 0);
  ck_assert_int_eq((unsigned int)result.bits[2], 0x19999999);
  ck_assert_int_eq((unsigned int)result.bits[1], 0x99999999);
  ck_assert_int_eq((unsigned int)result.bits[0], 0x99999978);
  ck_assert_int_eq((unsigned int)result.bits[3], 0x001c0000);

  ck_assert_int_eq(s21_mul(number5, number3, &result), 0);
  ck_assert_int_eq((unsigned int)result.bits[2], 0x028F5C28);
  ck_assert_int_eq((unsigned int)result.bits[1], 0xF5C28F5C);
  ck_assert_int_eq((unsigned int)result.bits[0], 0x28F5C28C);
  ck_assert_int_eq((unsigned int)result.bits[3], 0x001c0000);

  ck_assert_int_eq(s21_mul(number5, number4, &result), 0);
  ck_assert_int_eq((unsigned int)result.bits[2], 0x0000A7C5);
  ck_assert_int_eq((unsigned int)result.bits[1], 0xAC471B47);
  ck_assert_int_eq((unsigned int)result.bits[0], 0x84230FD0);
  ck_assert_int_eq((unsigned int)result.bits[3], 0x001c0000);

  ck_assert_int_eq(s21_mul(number6, number4, &result), 0);
  ck_assert_int_eq((unsigned int)result.bits[2], 0x0000A7C5);
  ck_assert_int_eq((unsigned int)result.bits[1], 0xAC471B47);
  ck_assert_int_eq((unsigned int)result.bits[0], 0x84230Fd0);
  ck_assert_int_eq((unsigned int)result.bits[3], 0x001c0000);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[45m-=S21_MUL=-\033[0m");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, mul_1);
  tcase_add_test(tc, mul_2);
  tcase_add_test(tc, mul_3);

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