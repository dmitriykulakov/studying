#include "s21_matrix_test.h"

START_TEST(calc_complements_1) {
  matrix_t matrix_1 = {NULL, 0, 0};
  s21_create_matrix(3, 3, &matrix_1);
  for (int i = 0; i < matrix_1.rows; i++) {
    for (int j = 0; j < matrix_1.columns; j++) {
      matrix_1.matrix[i][j] = (i + j) * 0.1111111;
    }
  }

  matrix_t matrix_2 = {NULL, 0, 0};
  s21_create_matrix(2, 2, &matrix_2);
  for (int i = 0; i < matrix_2.rows; i++) {
    for (int j = 0; j < matrix_2.columns; j++) {
      matrix_2.matrix[i][j] = (i + j) * 0.1111111;
    }
  }

  matrix_t matrix_3 = {NULL, 0, 0};

  matrix_t matrix_4 = {NULL, 0, 0};
  s21_create_matrix(1, 3, &matrix_4);
  matrix_4.matrix[0][0] = 123.1234567;
  matrix_4.matrix[0][1] = 234.1234567;
  matrix_4.matrix[0][2] = 345.1234567;

  matrix_t matrix_5 = {NULL, 0, 0};
  s21_create_matrix(1, 1, &matrix_5);
  matrix_5.matrix[0][0] = 123.1234567;

  matrix_t result = {NULL, 0, 0};
  ck_assert_int_eq(s21_calc_complements(NULL, &result), 1);
  ck_assert_int_eq(s21_calc_complements(&matrix_3, &result), 1);
  ck_assert_int_eq(s21_calc_complements(&matrix_2, NULL), 1);
  ck_assert_int_eq(s21_calc_complements(&matrix_4, &result), 2);

  ck_assert_int_eq(s21_calc_complements(&matrix_5, &result), 0);
  ck_assert_double_eq_tol(1, result.matrix[0][0], 1e-6);
  s21_remove_matrix(&result);

  matrix_t result_1_test = {NULL, 0, 0};
  s21_create_matrix(3, 3, &result_1_test);
  result_1_test.matrix[0][0] = -0.012345678765432098;
  result_1_test.matrix[0][1] = 0.024691357530864204;
  result_1_test.matrix[0][2] = -0.012345678765432098;
  result_1_test.matrix[1][0] = 0.024691357530864204;
  result_1_test.matrix[1][1] = -0.049382715;
  result_1_test.matrix[1][2] = 0.024691357530864204;
  result_1_test.matrix[2][0] = -0.012345678765432098;
  result_1_test.matrix[2][1] = 0.024691357530864204;
  result_1_test.matrix[2][2] = -0.012345678765432098;

  ck_assert_int_eq(s21_calc_complements(&matrix_1, &result), 0);
  ck_assert_int_eq(result_1_test.rows, result.rows);
  ck_assert_int_eq(result_1_test.columns, result.columns);
  for (int i = 0; i < result_1_test.rows; i++) {
    for (int j = 0; j < result_1_test.columns; j++) {
      ck_assert_double_eq_tol(result_1_test.matrix[i][j], result.matrix[i][j],
                              1e-6);
    }
  }

  s21_remove_matrix(&result);

  // matrix_t result = {NULL, 0, 0};
  matrix_t result_2_test = {NULL, 0, 0};
  s21_create_matrix(2, 2, &result_2_test);
  result_2_test.matrix[0][0] = 0.22222222;
  result_2_test.matrix[0][1] = -0.11111111;
  result_2_test.matrix[1][0] = -0.11111111;
  result_2_test.matrix[1][1] = 0.0;

  ck_assert_int_eq(s21_calc_complements(&matrix_2, &result), 0);
  ck_assert_int_eq(result_2_test.rows, result.rows);
  ck_assert_int_eq(result_2_test.columns, result.columns);
  for (int i = 0; i < result_2_test.rows; i++) {
    for (int j = 0; j < result_2_test.columns; j++) {
      ck_assert_double_eq_tol(result_2_test.matrix[i][j], result.matrix[i][j],
                              1e-6);
    }
  }

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&matrix_3);
  s21_remove_matrix(&matrix_4);
  s21_remove_matrix(&matrix_5);
  s21_remove_matrix(&result_1_test);
  s21_remove_matrix(&result_2_test);
  s21_remove_matrix(&result);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[45m-=S21_calc_complements=-\033[0m");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, calc_complements_1);

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