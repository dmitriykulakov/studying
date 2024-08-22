#include "s21_matrix_test.h"

START_TEST(determinant_1) {
  matrix_t matrix_1 = {NULL, 0, 0};
  s21_create_matrix(3, 3, &matrix_1);
  matrix_1.matrix[0][0] = 0.0;
  matrix_1.matrix[0][1] = 1.1111111;
  matrix_1.matrix[0][2] = 2.2222222;
  matrix_1.matrix[1][0] = 1.1111111;
  matrix_1.matrix[1][1] = 0.0;
  matrix_1.matrix[1][2] = 3.3333333;
  matrix_1.matrix[2][0] = 2.2222222;
  matrix_1.matrix[2][1] = 3.3333333;
  matrix_1.matrix[2][2] = 0.0;

  matrix_t matrix_2 = {NULL, 0, 0};
  s21_create_matrix(2, 2, &matrix_2);
  matrix_2.matrix[0][0] = 0.0;
  matrix_2.matrix[0][1] = 1.1111111;
  matrix_2.matrix[1][0] = 2.2222222;
  matrix_2.matrix[1][1] = 0.0;

  matrix_t matrix_3 = {NULL, 0, 0};

  matrix_t matrix_4 = {NULL, 0, 0};
  s21_create_matrix(1, 3, &matrix_4);
  matrix_4.matrix[0][0] = 123.1234567;
  matrix_4.matrix[0][1] = 234.1234567;
  matrix_4.matrix[0][2] = 345.1234567;

  matrix_t matrix_5 = {NULL, 0, 0};
  s21_create_matrix(1, 1, &matrix_5);
  matrix_5.matrix[0][0] = 123.1234567;

  double result;
  ck_assert_int_eq(s21_determinant(NULL, &result), 1);
  ck_assert_int_eq(s21_determinant(&matrix_3, &result), 1);
  ck_assert_int_eq(s21_determinant(&matrix_2, NULL), 1);
  ck_assert_int_eq(s21_determinant(&matrix_4, &result), 2);

  ck_assert_int_eq(s21_determinant(&matrix_1, &result), 0);
  double result_1 = 16.4609048560;
  ck_assert_double_eq_tol(result_1, result, 1e-6);

  ck_assert_int_eq(s21_determinant(&matrix_2, &result), 0);
  double result_2 = -2.4691357531;
  ck_assert_double_eq_tol(result_2, result, 1e-6);

  ck_assert_int_eq(s21_determinant(&matrix_5, &result), 0);
  ck_assert_double_eq_tol(matrix_5.matrix[0][0], result, 1e-6);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&matrix_3);
  s21_remove_matrix(&matrix_4);
  s21_remove_matrix(&matrix_5);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[45m-=S21_DETERMINANT=-\033[0m");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, determinant_1);

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