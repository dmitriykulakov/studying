#include "s21_smart_calculator_test.h"

#include "s21_smart_calculator.h"

START_TEST(smart_calculator_1) {
  double result;
  char *str_input = "cos(-log(25.123^10))=";
  ck_assert_int_eq(smart_calculator_simple(str_input, 0, &result), 0);
  ck_assert_double_eq_tol(result, cos(-log10(pow(25.123, 10))), 1e-6);
}
END_TEST

START_TEST(smart_calculator_2) {
  double result;
  char *str_input = "asin(atan(sqrt(1)))=";
  ck_assert_int_eq(smart_calculator_simple(str_input, 0, &result), 0);
  ck_assert_double_eq_tol(result, asin(atan(sqrt(1))), 1e-6);
}
END_TEST

START_TEST(smart_calculator_3) {
  double result;
  char *str_input_1 = "cos(1))=";
  ck_assert_int_eq(smart_calculator_simple(str_input_1, 0, &result), 4);

  char *str_input_2 = "123.12.3*123-1=";
  ck_assert_int_eq(smart_calculator_simple(str_input_2, 0, &result), 2);

  char *str_input_3 = ")*123=";
  ck_assert_int_eq(smart_calculator_simple(str_input_3, 0, &result), 2);

  char *str_input_4 = "1+5-3";
  ck_assert_int_eq(smart_calculator_simple(str_input_4, 0, &result), 1);

  char *str_input_5 = "1*3/2*/3=";
  ck_assert_int_eq(smart_calculator_simple(str_input_5, 0, &result), 2);

  char *str_input_6 = "123.*17=";
  ck_assert_int_eq(smart_calculator_simple(str_input_6, 0, &result), 2);

  char *str_input_7 =
      "-123.24124*17-42141+cos(123.5532)-sin(195/acos(x/"
      "7))++123+ln(7.43244534535)*tan(0.432532566363)+0.312424142+0.414124124+"
      "0.434324234+0.757456456+0.3432432442+0.3242342423+0.324324324324242-"
      "1421421421410-432424234200-42423424000+4234242+432423420+54353511000=";
  ck_assert_int_eq(smart_calculator_simple(str_input_7, 0, &result), 1);
}
END_TEST

START_TEST(smart_calculator_4) {
  double result;
  char *str_input =
      "-123.24124*17-42141+cos(123.5532)-sin(195/acos(x/"
      "7))++123+ln(7.43244534535)*tan(0.432532566363)+0.312424142+0.414124124+"
      "0.434324234+0.757456456+0.3432432442+0.3242342423+0.324324324324242-"
      "1421421421410-432424234200-42423424000+4234242+432423420+5435351100=";
  ck_assert_int_eq(smart_calculator_simple(str_input, 0, &result), 0);
  ck_assert_double_eq_tol(
      result,
      -123.24124 * 17 - 42141 + cos(123.5532) - sin(195 / acos(0 / 7)) + 123 +
          log(7.43244534535) * tan(0.432532566363) + 0.312424142 + 0.414124124 +
          0.434324234 + 0.757456456 + 0.3432432442 + 0.3242342423 +
          0.324324324324242 - 1421421421410 - 432424234200 - 42423424000 +
          4234242 + 432423420 + 5435351100,
      1e10);
}
END_TEST

START_TEST(smart_calculator_5) {
  double result;
  char *str_input = "5*3^3^3=";
  ck_assert_int_eq(smart_calculator_simple(str_input, 0, &result), 0);
  ck_assert_double_eq_tol(result, 5 * pow(pow(3, 3), 3), 1e-6);
}
END_TEST

START_TEST(smart_calculator_6) {
  double result;
  char *str_input = "7mod3*6=";
  ck_assert_int_eq(smart_calculator_simple(str_input, 0, &result), 0);
  ck_assert_double_eq_tol(result, fmod(7, 3) * 6, 1e-6);
}
END_TEST

START_TEST(smart_calculator_7) {
  double overpayment, total_payment, month_payment;
  annuity(50000, 36, 20, &overpayment, &total_payment, &month_payment);
  ck_assert_double_eq_tol(overpayment, 16894.450048, 1e-6);
  ck_assert_double_eq_tol(total_payment, 66894.450048, 1e-6);
  ck_assert_double_eq_tol(month_payment, 1858.179168, 1e-6);

  diff(50000, 36, 20, &overpayment, &total_payment, &month_payment);
  ck_assert_double_eq_tol(overpayment, 15416.6666667, 1e-6);
  ck_assert_double_eq_tol(total_payment, 65416.6666667, 1e-6);
  ck_assert_double_eq_tol(month_payment, 2222.222222, 1e-6);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[45m-=S21_smart_calculator=-\033[0m");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, smart_calculator_1);
  tcase_add_test(tc, smart_calculator_2);
  tcase_add_test(tc, smart_calculator_3);
  tcase_add_test(tc, smart_calculator_4);
  tcase_add_test(tc, smart_calculator_5);
  tcase_add_test(tc, smart_calculator_6);
  tcase_add_test(tc, smart_calculator_7);

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
