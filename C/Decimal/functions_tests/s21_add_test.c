#include "s21_decimal_test.h"

START_TEST(add_1) {
  s21_decimal number1;
  s21_decimal number2;
  s21_decimal number3;
  s21_decimal number4;
  s21_decimal number5;
  s21_decimal number6;
  s21_decimal number7;
  s21_decimal number8;
  s21_decimal number9;
  s21_decimal number10;
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
  number8.bits[3] = 0x80000000;

  number9.bits[0] = 0xffffffff;
  number9.bits[1] = 0xffffffff;
  number9.bits[2] = 0xffffffff;
  number9.bits[3] = 0x00000000;

  number10.bits[0] = 0x00000001;
  number10.bits[1] = 0x00000000;
  number10.bits[2] = 0x00000000;
  number10.bits[3] = 0x00000000;
  ck_assert_int_eq(s21_add(number1, number3, &result), 0);
  ck_assert_int_eq(result.bits[2], number1.bits[2]);
  ck_assert_int_eq(result.bits[1], number1.bits[1]);
  ck_assert_int_eq(result.bits[0], number1.bits[0]);
  ck_assert_int_eq(result.bits[3], number1.bits[3]);

  ck_assert_int_eq(s21_add(number3, number3, &result), 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[3], 0);

  ck_assert_int_eq(s21_add(number3, number2, &result), 0);
  ck_assert_int_eq(result.bits[2], number2.bits[2]);
  ck_assert_int_eq(result.bits[1], number2.bits[1]);
  ck_assert_int_eq(result.bits[0], number2.bits[0]);
  ck_assert_int_eq(result.bits[3], number2.bits[3]);

  ck_assert_int_eq(s21_add(number7, number8, &result), 2);

  ck_assert_int_eq(s21_add(number9, number10, &result), 1);

  ck_assert_int_eq(s21_add(number5, number6, &result), 0);
  ck_assert_int_eq((result.bits[3] & SC_32) >> 16, 0);
  ck_assert_int_eq(result.bits[2],
                   0b11100001010001111010111000010);  //надо решить как лучше
  ck_assert_int_eq((unsigned int)result.bits[1], 0x8f5c28f5);
  ck_assert_int_eq((unsigned int)result.bits[0], 0xc28f5c29);
  ck_assert_int_eq(result.bits[3], 0);

  ck_assert_int_eq(s21_add(number2, number4, &result), 0);
  ck_assert_int_eq((result.bits[3] & SC_32) >> 16, 0);
  ck_assert_int_eq((unsigned int)result.bits[2], 0x2468acf0);
  ck_assert_int_eq((unsigned int)result.bits[1], 0x2468acf0);
  ck_assert_int_eq((unsigned int)result.bits[0], 0x2468acf1);
  ck_assert_int_eq((unsigned int)result.bits[3], 2147483648);
}
END_TEST

START_TEST(add_2) {
  s21_decimal number1;
  s21_decimal number2;
  s21_decimal number3;
  s21_decimal number4;
  s21_decimal result;
  number1.bits[0] = 0xab4321f8;
  number1.bits[1] = 0x98765432;
  number1.bits[2] = 0x12345678;
  number1.bits[3] = 0x00050000;

  number2.bits[0] = 0x98765432;
  number2.bits[1] = 0xabcdefab;
  number2.bits[2] = 0x12345678;
  number2.bits[3] = 0x00150000;

  number3.bits[0] = 0x98765432;
  number3.bits[1] = 0xabcdefab;
  number3.bits[2] = 0x12345678;
  number3.bits[3] = 0x80150000;

  number4.bits[0] = 0xab4321f8;
  number4.bits[1] = 0x98765432;
  number4.bits[2] = 0x12345678;
  number4.bits[3] = 0x80050000;

  ck_assert_int_eq(s21_add(number1, number2, &result), 0);
  ck_assert_int_eq((result.bits[3] & SC_32) >> 16, 6);
  ck_assert_int_eq((unsigned int)result.bits[2], 0xb60b60b5);
  ck_assert_int_eq((unsigned int)result.bits[1], 0xf49f4f1a);
  ck_assert_int_eq((unsigned int)result.bits[0], 0x7559a11f);
  ck_assert_int_eq((unsigned int)result.bits[3], 393216);

  ck_assert_int_eq(s21_add(number1, number3, &result), 0);
  ck_assert_int_eq((result.bits[3] & SC_32) >> 16, 6);
  ck_assert_int_eq((unsigned int)result.bits[2], 0xb60b60b5);
  ck_assert_int_eq((unsigned int)result.bits[1], 0xf49f44da);
  ck_assert_int_eq((unsigned int)result.bits[0], 0xebe50641);
  ck_assert_int_eq((unsigned int)result.bits[3], 393216);

  ck_assert_int_eq(s21_add(number2, number4, &result), 0);
  ck_assert_int_eq((result.bits[3] & SC_32) >> 16, 6);
  ck_assert_int_eq((unsigned int)result.bits[2], 0xb60b60b5);
  ck_assert_int_eq((unsigned int)result.bits[1], 0xf49f44da);
  ck_assert_int_eq((unsigned int)result.bits[0], 0xebe50641);
  ck_assert_int_eq((unsigned int)result.bits[3], 2147876864);

  ck_assert_int_eq(s21_add(number4, number2, &result), 0);
  ck_assert_int_eq((result.bits[3] & SC_32) >> 16, 6);
  ck_assert_int_eq((unsigned int)result.bits[2], 0xb60b60b5);
  ck_assert_int_eq((unsigned int)result.bits[1], 0xf49f44da);
  ck_assert_int_eq((unsigned int)result.bits[0], 0xebe50641);
  ck_assert_int_eq((unsigned int)result.bits[3], 2147876864);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[45m-=S21_ADD=-\033[0m");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, add_1);
  tcase_add_test(tc, add_2);

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