#include "s21_decimal_test.h"

START_TEST(s21_from_float_to_decimal_test_1) {
  float test_float_1 = 0;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, NULL),
                   RETURN_VALUE_1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_2) {
  float test_float_1 = S21_NAN;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_3) {
  float test_float_1 = S21_INF_P;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_4) {
  float test_float_1 = S21_INF_N;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_5) {
  float test_float_1 = MAX_FLOAT_TO_DECIMAL + 1e+22;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_6) {
  float test_float_1 = +MAX_FLOAT_TO_DECIMAL;
  float test_float_2 = 0.0;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_0);
  s21_from_decimal_to_float(test_var_1, &test_float_2);
  ck_assert_float_eq(7.922816 * pow(10, 28), test_float_2);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_7) {
  float test_float_1 = -MAX_FLOAT_TO_DECIMAL;
  float test_float_2 = 0.0;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_0);
  s21_from_decimal_to_float(test_var_1, &test_float_2);
  ck_assert_float_eq(-7.922816 * pow(10, 28), test_float_2);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_8) {
  float test_float_1 = MIN_FLOAT_TO_DECIMAL - 1e-7 * MIN_FLOAT_TO_DECIMAL;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_9) {
  float test_float_1 = MIN_FLOAT_TO_DECIMAL;
  float test_float_2 = 0.0;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_0);
  s21_from_decimal_to_float(test_var_1, &test_float_2);
  ck_assert_float_eq(1e-28, test_float_2);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_10) {
  float test_float_1 = -MIN_FLOAT_TO_DECIMAL;
  float test_float_2 = 0.0;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_0);
  s21_from_decimal_to_float(test_var_1, &test_float_2);
  ck_assert_float_eq(-1e-28, test_float_2);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_11) {
  float test_float_1 = 1.2345678;
  float test_float_2 = 0.0;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_0);
  s21_from_decimal_to_float(test_var_1, &test_float_2);
  s21_from_decimal_to_float(test_var_1, &test_float_2);
  ck_assert_float_eq(1.234568, test_float_2);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_12) {
  float test_float_1 = -1.2345678;
  float test_float_2 = 0.0;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_0);
  s21_from_decimal_to_float(test_var_1, &test_float_2);
  ck_assert_float_eq(-1.234568, test_float_2);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_13) {
  float test_float_1 = 1.2345678e-10;
  float test_float_2 = 0.0;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_0);
  s21_from_decimal_to_float(test_var_1, &test_float_2);
  ck_assert_float_eq(1234568 / pow(10, 16), test_float_2);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_14) {
  float test_float_1 = -1.2345678e-10;
  float test_float_2 = 0.0;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_0);
  s21_from_decimal_to_float(test_var_1, &test_float_2);
  ck_assert_float_eq(-1234568 / pow(10, 16), test_float_2);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_15) {
  float test_float_1 = 1.2345678e-26;
  float test_float_2 = 0.0;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_0);
  s21_from_decimal_to_float(test_var_1, &test_float_2);
  ck_assert_float_eq(123 / pow(10, 28), test_float_2);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_16) {
  float test_float_1 = -1.2345678e-26;
  float test_float_2 = 0.0;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_0);
  s21_from_decimal_to_float(test_var_1, &test_float_2);
  ck_assert_float_eq(-123 / pow(10, 28), test_float_2);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_17) {
  float test_float_1 = 12345.67890123;
  float test_float_2 = 0.0;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_0);
  s21_from_decimal_to_float(test_var_1, &test_float_2);
  ck_assert_float_eq(1234568 / pow(10, 2), test_float_2);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_18) {
  float test_float_1 = -12345.67890123;
  float test_float_2 = 0.0;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_0);
  s21_from_decimal_to_float(test_var_1, &test_float_2);
  ck_assert_float_eq(-1234568 / pow(10, 2), test_float_2);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_19) {
  float test_float_1 = 12345.0;
  float test_float_2 = 0.0;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_0);
  s21_from_decimal_to_float(test_var_1, &test_float_2);
  ck_assert_float_eq(1234500 / pow(10, 2), test_float_2);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_20) {
  float test_float_1 = -12345.0;
  float test_float_2 = 0.0;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_0);
  s21_from_decimal_to_float(test_var_1, &test_float_2);
  ck_assert_float_eq(-1234500 / pow(10, 2), test_float_2);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_21) {
  float test_float_1 = 1.23456789e+6;
  float test_float_2 = 0.0;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_0);
  s21_from_decimal_to_float(test_var_1, &test_float_2);
  ck_assert_float_eq(1234568 / pow(10, 0), test_float_2);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_22) {
  float test_float_1 = -1.23456789e+6;
  float test_float_2 = 0.0;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_0);
  s21_from_decimal_to_float(test_var_1, &test_float_2);
  ck_assert_float_eq(-1234568 / pow(10, 0), test_float_2);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_23) {
  float test_float_1 = 1.23456789e+7;
  float test_float_2 = 0.0;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_0);
  s21_from_decimal_to_float(test_var_1, &test_float_2);
  ck_assert_float_eq(12345680 / pow(10, 0), test_float_2);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_24) {
  float test_float_1 = -1.23456789e+7;
  float test_float_2 = 0.0;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_0);
  s21_from_decimal_to_float(test_var_1, &test_float_2);
  ck_assert_float_eq(-12345680 / pow(10, 0), test_float_2);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_25) {
  float test_float_1 = 1.23456789e+15;
  float test_float_2 = 0.0;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_0);
  s21_from_decimal_to_float(test_var_1, &test_float_2);
  ck_assert_float_eq(1.2345680 * pow(10, 15), test_float_2);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_26) {
  float test_float_1 = -1.23456789e+15;
  float test_float_2 = 0.0;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_0);
  s21_from_decimal_to_float(test_var_1, &test_float_2);
  ck_assert_float_eq(-1.2345680 * pow(10, 15), test_float_2);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_27) {
  float test_float_1 = 1.23456789e+28;
  float test_float_2 = 0.0;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_0);
  s21_from_decimal_to_float(test_var_1, &test_float_2);
  ck_assert_float_eq(1.2345680 * pow(10, 28), test_float_2);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_28) {
  float test_float_1 = -1.23456789e+28;
  float test_float_2 = 0.0;
  s21_decimal test_var_1;

  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_0);
  s21_from_decimal_to_float(test_var_1, &test_float_2);
  ck_assert_float_eq(-1.2345680 * pow(10, 28), test_float_2);
}
END_TEST

START_TEST(s21_from_float_to_decimal_test_999) {
  float test_float_1 = 1.0;
  float test_float_2 = 0.0;
  s21_decimal test_var_1;

  s21_from_float_to_decimal(test_float_1, &test_var_1);
  ck_assert_int_eq(s21_from_float_to_decimal(test_float_1, &test_var_1),
                   RETURN_VALUE_0);

  s21_from_decimal_to_float(test_var_1, &test_float_2);

  //  printf(" **************\n");
  //   for (int i=0;i<4;i++) {
  //   printf("     bit %d   %08x\n",i,test_var_1.bits[i]);
  //   printf("     bit %d   %d\n",i,test_var_1.bits[i]);
  //   }
  //   printf("\n");
  //   printf("     test_float_1 %f\n",test_float_1);
  //   printf("     test_float_2 %f\n",test_float_2);
  //   printf(" **************\n");

  ck_assert_float_eq(1.0, test_float_2);
}
END_TEST

Suite *suite(void) {
  Suite *suite =
      suite_create("\033[32m s21_from_float_to_decimal_test \033[0m");
  TCase *tcase = tcase_create("core");

  tcase_add_test(tcase, s21_from_float_to_decimal_test_1);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_2);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_3);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_4);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_5);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_6);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_7);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_8);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_9);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_10);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_11);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_12);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_13);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_14);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_15);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_16);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_17);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_18);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_19);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_20);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_21);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_22);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_23);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_24);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_25);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_26);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_27);
  tcase_add_test(tcase, s21_from_float_to_decimal_test_28);

  tcase_add_test(tcase, s21_from_float_to_decimal_test_999);

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
