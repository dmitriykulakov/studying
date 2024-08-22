#include "s21_decimal_test.h"

START_TEST(s21_round_test_1) {
  s21_decimal test_var_1;

  test_var_1.bits[0] = 0;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0;

  ck_assert_int_eq(s21_round(test_var_1, NULL), RETURN_VALUE_1);
}
END_TEST

START_TEST(s21_round_test_2) {
  s21_decimal test_var_1;
  s21_decimal test_var_2;

  test_var_1.bits[0] = 0;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x00000000;

  ck_assert_int_eq(s21_round(test_var_1, &test_var_2), RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[0], 0);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[3], 0x00000000);
}
END_TEST

START_TEST(s21_round_test_3) {
  s21_decimal test_var_1;
  s21_decimal test_var_2;

  test_var_1.bits[0] = 0;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x80020000;

  ck_assert_int_eq(s21_round(test_var_1, &test_var_2), RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[0], 0);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[3], 0x00000000);
}
END_TEST

START_TEST(s21_round_test_4) {
  s21_decimal test_var_1;
  s21_decimal test_var_2;

  test_var_1.bits[0] = 1234500;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x00020000;

  ck_assert_int_eq(s21_round(test_var_1, &test_var_2), RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[0], 12345);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[3], 0x00000000);
}
END_TEST

START_TEST(s21_round_test_5) {
  s21_decimal test_var_1;
  s21_decimal test_var_2;

  test_var_1.bits[0] = 1234500;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x80020000;

  ck_assert_int_eq(s21_round(test_var_1, &test_var_2), RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[0], 12345);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[3], 0x80000000);
}
END_TEST

START_TEST(s21_round_test_6) {
  s21_decimal test_var_1;
  s21_decimal test_var_2;

  test_var_1.bits[0] = 12345;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x00020000;

  ck_assert_int_eq(s21_round(test_var_1, &test_var_2), RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[0], 123);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[3], 0x00000000);
}
END_TEST

START_TEST(s21_round_test_7) {
  s21_decimal test_var_1;
  s21_decimal test_var_2;

  test_var_1.bits[0] = 12345;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x80020000;

  ck_assert_int_eq(s21_round(test_var_1, &test_var_2), RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[0], 123);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[3], 0x80000000);
}
END_TEST

START_TEST(s21_round_test_8) {
  s21_decimal test_var_1;
  s21_decimal test_var_2;

  test_var_1.bits[0] = 12345;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x00010000;

  ck_assert_int_eq(s21_round(test_var_1, &test_var_2), RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[0], 1235);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[3], 0x00000000);
}
END_TEST

START_TEST(s21_round_test_9) {
  s21_decimal test_var_1;
  s21_decimal test_var_2;

  test_var_1.bits[0] = 12345;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x80010000;

  ck_assert_int_eq(s21_round(test_var_1, &test_var_2), RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[0], 1235);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[3], 0x80000000);
}
END_TEST

START_TEST(s21_round_test_10) {
  s21_decimal test_var_1;
  s21_decimal test_var_2;

  test_var_1.bits[0] = 12345;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x00050000;

  ck_assert_int_eq(s21_round(test_var_1, &test_var_2), RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[0], 0);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[3], 0x00000000);
}
END_TEST

START_TEST(s21_round_test_11) {
  s21_decimal test_var_1;
  s21_decimal test_var_2;

  test_var_1.bits[0] = 12345;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x80050000;

  ck_assert_int_eq(s21_round(test_var_1, &test_var_2), RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[0], 0);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[3], 0x80000000);
}
END_TEST

START_TEST(s21_round_test_12) {
  s21_decimal test_var_1;
  s21_decimal test_var_2;

  test_var_1.bits[0] = 12345;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x00ff0000;

  ck_assert_int_eq(s21_round(test_var_1, &test_var_2), RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[0], 0);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[3], 0x00000000);
}
END_TEST

START_TEST(s21_round_test_13) {
  s21_decimal test_var_1;
  s21_decimal test_var_2;

  test_var_1.bits[0] = 12345;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x80ff0000;

  ck_assert_int_eq(s21_round(test_var_1, &test_var_2), RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[0], 0);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[3], 0x80000000);
}
END_TEST

START_TEST(s21_round_test_14) {
  s21_decimal test_var_1;
  s21_decimal test_var_2;

  test_var_1.bits[0] = 0xffffffff;
  test_var_1.bits[1] = 0x000000ff;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x00020000;

  ck_assert_int_eq(s21_round(test_var_1, &test_var_2), RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[0], 0x8F5C28F6);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[1], 0x00000002);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[3], 0x00000000);
}
END_TEST

START_TEST(s21_round_test_15) {
  s21_decimal test_var_1;
  s21_decimal test_var_2;

  test_var_1.bits[0] = 0xffffffff;
  test_var_1.bits[1] = 0x000000ff;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0x80020000;

  ck_assert_int_eq(s21_round(test_var_1, &test_var_2), RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[0], 0x8F5C28F6);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[1], 0x00000002);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[3], 0x80000000);
}
END_TEST

START_TEST(s21_round_test_16) {
  s21_decimal test_var_1;
  s21_decimal test_var_2;

  test_var_1.bits[0] = 0xffffffff;
  test_var_1.bits[1] = 0xffffffff;
  test_var_1.bits[2] = 0xffffffff;
  test_var_1.bits[3] = 0x00000000;

  ck_assert_int_eq(s21_round(test_var_1, &test_var_2), RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[0], 0xffffffff);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[1], 0xffffffff);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[2], 0xffffffff);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[3], 0x00000000);
}
END_TEST

START_TEST(s21_round_test_17) {
  s21_decimal test_var_1;
  s21_decimal test_var_2;

  test_var_1.bits[0] = 0xffffffff;
  test_var_1.bits[1] = 0xffffffff;
  test_var_1.bits[2] = 0xffffffff;
  test_var_1.bits[3] = 0x80000000;

  ck_assert_int_eq(s21_round(test_var_1, &test_var_2), RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[0], 0xffffffff);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[1], 0xffffffff);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[2], 0xffffffff);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[3], 0x80000000);
}
END_TEST

START_TEST(s21_round_test_18) {
  s21_decimal test_var_1;
  s21_decimal test_var_2;

  test_var_1.bits[0] = 0xffffffff;
  test_var_1.bits[1] = 0x00000009;
  test_var_1.bits[2] = 0x00000000;
  test_var_1.bits[3] = 0x00010000;

  ck_assert_int_eq(s21_round(test_var_1, &test_var_2), RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[0], 0x00000000);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[1], 0x00000001);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[2], 0x00000000);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[3], 0x00000000);
}
END_TEST

START_TEST(s21_round_test_19) {
  s21_decimal test_var_1;
  s21_decimal test_var_2;

  test_var_1.bits[0] = 0xffffffff;
  test_var_1.bits[1] = 0x00000009;
  test_var_1.bits[2] = 0x00000000;
  test_var_1.bits[3] = 0x80010000;

  ck_assert_int_eq(s21_round(test_var_1, &test_var_2), RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[0], 0x00000000);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[1], 0x00000001);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[2], 0x00000000);
  ck_assert_uint_eq((unsigned int)test_var_2.bits[3], 0x80000000);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[32m s21_round_test \033[0m");
  TCase *tcase = tcase_create("core");

  tcase_add_test(tcase, s21_round_test_1);
  tcase_add_test(tcase, s21_round_test_2);
  tcase_add_test(tcase, s21_round_test_3);
  tcase_add_test(tcase, s21_round_test_4);
  tcase_add_test(tcase, s21_round_test_5);
  tcase_add_test(tcase, s21_round_test_6);
  tcase_add_test(tcase, s21_round_test_7);
  tcase_add_test(tcase, s21_round_test_8);
  tcase_add_test(tcase, s21_round_test_9);
  tcase_add_test(tcase, s21_round_test_10);
  tcase_add_test(tcase, s21_round_test_11);
  tcase_add_test(tcase, s21_round_test_12);
  tcase_add_test(tcase, s21_round_test_13);
  tcase_add_test(tcase, s21_round_test_14);
  tcase_add_test(tcase, s21_round_test_15);
  tcase_add_test(tcase, s21_round_test_16);
  tcase_add_test(tcase, s21_round_test_17);
  tcase_add_test(tcase, s21_round_test_18);
  tcase_add_test(tcase, s21_round_test_19);

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
