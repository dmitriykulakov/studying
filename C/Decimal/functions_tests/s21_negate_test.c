#include "s21_decimal_test.h"

START_TEST(s21_negate_test_1) {
  s21_decimal test_var_1;

  test_var_1.bits[0] = 0;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0;

  ck_assert_int_eq(s21_negate(test_var_1, NULL), RETURN_VALUE_1);
}
END_TEST

START_TEST(s21_negate_test_2) {
  s21_decimal test_var_1;
  s21_decimal test_var_2;

  test_var_1.bits[0] = 0;
  test_var_1.bits[1] = 0;
  test_var_1.bits[2] = 0;
  test_var_1.bits[3] = 0;

  ck_assert_int_eq(s21_negate(test_var_1, &test_var_2), RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[0],
                    (unsigned int)test_var_2.bits[0]);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[1],
                    (unsigned int)test_var_2.bits[1]);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[2],
                    (unsigned int)test_var_2.bits[2]);
  ck_assert_uint_eq((unsigned int)(test_var_1.bits[3] ^ test_var_2.bits[3]),
                    ZERO_32);
}
END_TEST

START_TEST(s21_negate_test_3) {
  s21_decimal test_var_1;
  s21_decimal test_var_2;

  test_var_1.bits[0] = 0xffffffff;
  test_var_1.bits[1] = 0xffffffff;
  test_var_1.bits[2] = 0xffffffff;
  test_var_1.bits[3] = 0x00ff0000;

  ck_assert_int_eq(s21_negate(test_var_1, &test_var_2), RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[0],
                    (unsigned int)test_var_2.bits[0]);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[1],
                    (unsigned int)test_var_2.bits[1]);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[2],
                    (unsigned int)test_var_2.bits[2]);
  ck_assert_uint_eq((unsigned int)(test_var_1.bits[3] ^ test_var_2.bits[3]),
                    MINUS_32);
}
END_TEST

START_TEST(s21_negate_test_4) {
  s21_decimal test_var_1;
  s21_decimal test_var_2;

  test_var_1.bits[0] = 0xffffffff;
  test_var_1.bits[1] = 0xffffffff;
  test_var_1.bits[2] = 0xffffffff;
  test_var_1.bits[3] = 0x80ff0000;

  ck_assert_int_eq(s21_negate(test_var_1, &test_var_2), RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[0],
                    (unsigned int)test_var_2.bits[0]);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[1],
                    (unsigned int)test_var_2.bits[1]);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[2],
                    (unsigned int)test_var_2.bits[2]);
  ck_assert_uint_eq((unsigned int)(test_var_1.bits[3] ^ test_var_2.bits[3]),
                    MINUS_32);
}
END_TEST

START_TEST(s21_negate_test_5) {
  s21_decimal test_var_1;
  s21_decimal test_var_2;

  test_var_1.bits[0] = 0xffffffff;
  test_var_1.bits[1] = 0xffffffff;
  test_var_1.bits[2] = 0xffffffff;
  test_var_1.bits[3] = 0x00000000;

  ck_assert_int_eq(s21_negate(test_var_1, &test_var_2), RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[0],
                    (unsigned int)test_var_2.bits[0]);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[1],
                    (unsigned int)test_var_2.bits[1]);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[2],
                    (unsigned int)test_var_2.bits[2]);
  ck_assert_uint_eq((unsigned int)(test_var_1.bits[3] ^ test_var_2.bits[3]),
                    MINUS_32);
}
END_TEST

START_TEST(s21_negate_test_6) {
  s21_decimal test_var_1;
  s21_decimal test_var_2;

  test_var_1.bits[0] = 0xffffffff;
  test_var_1.bits[1] = 0xffffffff;
  test_var_1.bits[2] = 0xffffffff;
  test_var_1.bits[3] = 0x80000000;

  ck_assert_int_eq(s21_negate(test_var_1, &test_var_2), RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[0],
                    (unsigned int)test_var_2.bits[0]);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[1],
                    (unsigned int)test_var_2.bits[1]);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[2],
                    (unsigned int)test_var_2.bits[2]);
  ck_assert_uint_eq((unsigned int)(test_var_1.bits[3] ^ test_var_2.bits[3]),
                    MINUS_32);
}
END_TEST

START_TEST(s21_negate_test_7) {
  s21_decimal test_var_1;
  s21_decimal test_var_2;

  test_var_1.bits[0] = 0x01254def;
  test_var_1.bits[1] = 0x12345678;
  test_var_1.bits[2] = 0xfa9bcfff;
  test_var_1.bits[3] = 0x80e90000;

  ck_assert_int_eq(s21_negate(test_var_1, &test_var_2), RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[0],
                    (unsigned int)test_var_2.bits[0]);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[1],
                    (unsigned int)test_var_2.bits[1]);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[2],
                    (unsigned int)test_var_2.bits[2]);
  ck_assert_uint_eq((unsigned int)(test_var_1.bits[3] ^ test_var_2.bits[3]),
                    MINUS_32);
}
END_TEST

START_TEST(s21_negate_test_8) {
  s21_decimal test_var_1;
  s21_decimal test_var_2;

  test_var_1.bits[0] = 0x01254def;
  test_var_1.bits[1] = 0x12345678;
  test_var_1.bits[2] = 0xfa9bcfff;
  test_var_1.bits[3] = 0x00e90000;

  ck_assert_int_eq(s21_negate(test_var_1, &test_var_2), RETURN_VALUE_0);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[0],
                    (unsigned int)test_var_2.bits[0]);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[1],
                    (unsigned int)test_var_2.bits[1]);
  ck_assert_uint_eq((unsigned int)test_var_1.bits[2],
                    (unsigned int)test_var_2.bits[2]);
  ck_assert_uint_eq((unsigned int)(test_var_1.bits[3] ^ test_var_2.bits[3]),
                    MINUS_32);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[32m s21_negate_test \033[0m");
  TCase *tcase = tcase_create("core");

  tcase_add_test(tcase, s21_negate_test_1);
  tcase_add_test(tcase, s21_negate_test_2);
  tcase_add_test(tcase, s21_negate_test_3);
  tcase_add_test(tcase, s21_negate_test_4);
  tcase_add_test(tcase, s21_negate_test_5);
  tcase_add_test(tcase, s21_negate_test_6);
  tcase_add_test(tcase, s21_negate_test_7);
  tcase_add_test(tcase, s21_negate_test_8);

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
