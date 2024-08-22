#include "s21_decimal_test.h"

START_TEST(sub_1) {
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
  number1.bits[2] = 0b11111111111111111111111111111111;
  number1.bits[3] = 0x801A0000;

  number2.bits[0] = 0x12345678;
  number2.bits[1] = 0x12345678;
  number2.bits[2] = 0b10010001101000101011001111000;
  number2.bits[3] = 0b10000000000000000000000000000000;

  number3.bits[0] = 0;
  number3.bits[1] = 0;
  number3.bits[2] = 0b0;
  number3.bits[3] = 0b10000000000111100000000000000000;

  number4.bits[0] = 0xffffffff;
  number4.bits[1] = 0xffffffff;
  number4.bits[2] = 0xffffffff;
  number4.bits[3] = 0x80000000;

  number5.bits[0] = 0x00000001;
  number5.bits[1] = 0x00000000;
  number5.bits[2] = 0x00000000;
  number5.bits[3] = 0x00000000;

  number6.bits[0] = 0xffffffff;
  number6.bits[1] = 0xffffffff;
  number6.bits[2] = 0xffffffff;
  number6.bits[3] = 0x00000000;

  number7.bits[0] = 0x00000001;
  number7.bits[1] = 0x00000000;
  number7.bits[2] = 0x00000000;
  number7.bits[3] = 0x80000000;

  ck_assert_int_eq(s21_sub(number1, number3, &result), 0);
  ck_assert_int_eq(result.bits[2], number1.bits[2]);
  ck_assert_int_eq(result.bits[1], number1.bits[1]);
  ck_assert_int_eq(result.bits[0], number1.bits[0]);
  ck_assert_int_eq(result.bits[3], number1.bits[3]);

  ck_assert_int_eq(s21_sub(number3, number3, &result), 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[3], 0);

  ck_assert_int_eq(s21_sub(number3, number2, &result), 0);
  ck_assert_int_eq(result.bits[2], number2.bits[2]);
  ck_assert_int_eq(result.bits[1], number2.bits[1]);
  ck_assert_int_eq(result.bits[0], number2.bits[0]);
  ck_assert_int_eq(result.bits[3], 0);

  ck_assert_int_eq(s21_sub(number4, number5, &result), 2);

  ck_assert_int_eq(s21_sub(number4, number6, &result), 2);

  ck_assert_int_eq(s21_sub(number6, number7, &result), 1);
}
END_TEST

START_TEST(sub_2) {
  s21_decimal number1;
  s21_decimal number2;
  s21_decimal number3;
  s21_decimal number4;
  s21_decimal number5;
  s21_decimal result;
  number1.bits[0] = 0xab4321f8;
  number1.bits[1] = 0x98765432;
  number1.bits[2] = 0x12345678;
  number1.bits[3] = 0x00050000;

  number2.bits[0] = 0x98765432;
  number2.bits[1] = 0xabcdefab;
  number2.bits[2] = 0x12345678;
  number2.bits[3] = 0x80150000;

  number3.bits[0] = 0x98765432;
  number3.bits[1] = 0xabcdefab;
  number3.bits[2] = 0x12345678;
  number3.bits[3] = 0x00150000;

  number4.bits[0] = 0xab4321f8;
  number4.bits[1] = 0x98765432;
  number4.bits[2] = 0x12345678;
  number4.bits[3] = 0x00050000;

  number5.bits[0] = 0xab4321f8;
  number5.bits[1] = 0x98765432;
  number5.bits[2] = 0x12345678;
  number5.bits[3] = 0x80050000;

  ck_assert_int_eq(s21_sub(number1, number2, &result), 0);
  ck_assert_int_eq((result.bits[3] & SC_32) >> 16, 6);
  ck_assert_int_eq((unsigned int)result.bits[2], 0xb60b60b5);
  ck_assert_int_eq((unsigned int)result.bits[1], 0xf49f4f1a);
  ck_assert_int_eq((unsigned int)result.bits[0], 0x7559a11f);
  ck_assert_int_eq((unsigned int)result.bits[3], 393216);

  ck_assert_int_eq(s21_sub(number1, number3, &result), 0);
  ck_assert_int_eq((result.bits[3] & SC_32) >> 16, 6);
  ck_assert_int_eq((unsigned int)result.bits[2], 0xb60b60b5);
  ck_assert_int_eq((unsigned int)result.bits[1], 0xf49f44da);
  ck_assert_int_eq((unsigned int)result.bits[0], 0xebe50641);
  ck_assert_int_eq((unsigned int)result.bits[3], 393216);

  ck_assert_int_eq(s21_sub(number3, number4, &result), 0);
  ck_assert_int_eq((result.bits[3] & SC_32) >> 16, 6);
  ck_assert_int_eq((unsigned int)result.bits[2], 0xb60b60b5);
  ck_assert_int_eq((unsigned int)result.bits[1], 0xf49f44da);
  ck_assert_int_eq((unsigned int)result.bits[0], 0xebe50641);
  ck_assert_int_eq((unsigned int)result.bits[3], 2147876864);

  ck_assert_int_eq(s21_sub(number2, number2, &result), 0);
  ck_assert_int_eq((result.bits[3] & SC_32) >> 16, 0);
  ck_assert_int_eq((unsigned int)result.bits[2], 0x00000000);
  ck_assert_int_eq((unsigned int)result.bits[1], 0x00000000);
  ck_assert_int_eq((unsigned int)result.bits[0], 0x00000000);
  ck_assert_int_eq((unsigned int)result.bits[3], 0x00000000);

  ck_assert_int_eq(s21_sub(number2, number5, &result), 0);
  ck_assert_int_eq((result.bits[3] & SC_32) >> 16, 6);
  ck_assert_int_eq((unsigned int)result.bits[2], 0xb60b60b5);
  ck_assert_int_eq((unsigned int)result.bits[1], 0xf49f44da);
  ck_assert_int_eq((unsigned int)result.bits[0], 0xebe50641);
  ck_assert_int_eq((unsigned int)result.bits[3], 393216);
}
END_TEST

START_TEST(sub_3) {
  s21_decimal number1;
  s21_decimal number2;

  s21_decimal result;
  number1.bits[0] = 0x00000000;
  number1.bits[1] = 0x00000000;
  number1.bits[2] = 0x00000002;
  number1.bits[3] = 0x00000000;

  number2.bits[0] = 0x00000001;
  number2.bits[1] = 0x00000000;
  number2.bits[2] = 0x00000000;
  number2.bits[3] = 0x00000000;

  ck_assert_int_eq(s21_sub(number1, number2, &result), 0);
  ck_assert_int_eq((result.bits[3] & SC_32) >> 16, 0);
  ck_assert_int_eq((unsigned int)result.bits[2], 0x00000001);
  ck_assert_int_eq((unsigned int)result.bits[1], 0xffffffff);
  ck_assert_int_eq((unsigned int)result.bits[0], 0xffffffff);
  ck_assert_int_eq((unsigned int)result.bits[3], 0);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[45m-=S21_SUB=-\033[0m");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, sub_1);
  tcase_add_test(tc, sub_2);
  tcase_add_test(tc, sub_3);

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