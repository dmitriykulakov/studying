#include "s21_matrix_test.h"

START_TEST(mult_matrix_1) {
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
  s21_create_matrix(3, 3, &matrix_4);
  for (int i = 0; i < matrix_4.rows; i++) {
    for (int j = 0; j < matrix_4.columns; j++) {
      matrix_4.matrix[i][j] = 1;
    }
  }

  matrix_t matrix_5 = {NULL, 0, 0};
  s21_create_matrix(3, 3, &matrix_5);
  for (int i = 0; i < matrix_5.rows; i++) {
    for (int j = 0; j < matrix_5.columns; j++) {
      matrix_5.matrix[i][j] = 0;
    }
  }

  matrix_t result = {NULL, 0, 0};
  ck_assert_int_eq(s21_mult_matrix(&matrix_1, &matrix_2, &result), 2);
  ck_assert_int_eq(s21_mult_matrix(&matrix_1, NULL, &result), 1);
  ck_assert_int_eq(s21_mult_matrix(NULL, &matrix_2, &result), 1);
  ck_assert_int_eq(s21_mult_matrix(&matrix_3, &matrix_2, &result), 1);
  ck_assert_int_eq(s21_mult_matrix(&matrix_2, &matrix_2, NULL), 1);
  ck_assert_int_eq(s21_mult_matrix(&matrix_1, &matrix_5, &result), 0);
  ck_assert_int_eq(matrix_1.rows, result.rows);
  ck_assert_int_eq(matrix_1.columns, result.columns);
  for (int i = 0; i < matrix_1.rows; i++) {
    for (int j = 0; j < matrix_1.columns; j++) {
      ck_assert_double_eq(0, result.matrix[i][j]);
    }
  }
  s21_remove_matrix(&result);

  matrix_t result_1_test = {NULL, 0, 0};
  s21_create_matrix(3, 3, &result_1_test);
  result_1_test.matrix[0][0] = 0.3333333;
  result_1_test.matrix[0][1] = 0.3333333;
  result_1_test.matrix[0][2] = 0.3333333;
  result_1_test.matrix[1][0] = 0.6666666;
  result_1_test.matrix[1][1] = 0.6666666;
  result_1_test.matrix[1][2] = 0.6666666;
  result_1_test.matrix[2][0] = 0.9999999;
  result_1_test.matrix[2][1] = 0.9999999;
  result_1_test.matrix[2][2] = 0.9999999;

  ck_assert_int_eq(s21_mult_matrix(&matrix_1, &matrix_4, &result), 0);
  ck_assert_int_eq(result_1_test.rows, result.rows);
  ck_assert_int_eq(result_1_test.columns, result.columns);
  for (int i = 0; i < result_1_test.rows; i++) {
    for (int j = 0; j < result_1_test.columns; j++) {
      ck_assert_double_eq_tol(result_1_test.matrix[i][j], result.matrix[i][j],
                              1e-6);
    }
  }
  s21_remove_matrix(&result);
  s21_remove_matrix(&result_1_test);

  matrix_t result_2_test = {NULL, 0, 0};
  s21_create_matrix(3, 3, &result_2_test);
  result_2_test.matrix[0][0] = 0.06172838271605;
  result_2_test.matrix[0][1] = 0.09876541234568;
  result_2_test.matrix[0][2] = 0.13580244197531;
  result_2_test.matrix[1][0] = 0.09876541234568;
  result_2_test.matrix[1][1] = 0.17283947160494;
  result_2_test.matrix[1][2] = 0.2469135308642;
  result_2_test.matrix[2][0] = 0.13580244197531;
  result_2_test.matrix[2][1] = 0.2469135308642;
  result_2_test.matrix[2][2] = 0.35802461975309;

  ck_assert_int_eq(s21_mult_matrix(&matrix_1, &matrix_1, &result), 0);
  ck_assert_int_eq(result_2_test.rows, result.rows);
  ck_assert_int_eq(result_2_test.columns, result.columns);
  for (int i = 0; i < result_2_test.rows; i++) {
    for (int j = 0; j < result_2_test.columns; j++) {
      ck_assert_double_eq_tol(result_2_test.matrix[i][j], result.matrix[i][j],
                              1e-6);
    }
  }
  s21_remove_matrix(&result);
  s21_remove_matrix(&result_2_test);

  matrix_t matrix_6 = {NULL, 0, 0};
  s21_create_matrix(4, 3, &matrix_6);
  for (int i = 0; i < matrix_6.rows; i++) {
    for (int j = 0; j < matrix_6.columns; j++) {
      matrix_6.matrix[i][j] = (double)(i + j);
    }
  }
  matrix_t matrix_7 = {NULL, 0, 0};
  s21_create_matrix(3, 4, &matrix_7);
  for (int i = 0; i < matrix_7.rows; i++) {
    for (int j = 0; j < matrix_7.columns; j++) {
      matrix_7.matrix[i][j] = (double)(i + j);
    }
  }

  // matrix_t result = {NULL, 0, 0};
  matrix_t result_test = {NULL, 0, 0};
  s21_create_matrix(4, 4, &result_test);
  result_test.matrix[0][0] = 5.0;
  result_test.matrix[0][1] = 8.0;
  result_test.matrix[0][2] = 11.0;
  result_test.matrix[0][3] = 14.0;
  result_test.matrix[1][0] = 8.0;
  result_test.matrix[1][1] = 14.0;
  result_test.matrix[1][2] = 20.0;
  result_test.matrix[1][3] = 26.0;
  result_test.matrix[2][0] = 11.0;
  result_test.matrix[2][1] = 20.0;
  result_test.matrix[2][2] = 29.0;
  result_test.matrix[2][3] = 38.0;
  result_test.matrix[3][0] = 14.0;
  result_test.matrix[3][1] = 26.0;
  result_test.matrix[3][2] = 38.0;
  result_test.matrix[3][3] = 50.0;
  ck_assert_int_eq(s21_mult_matrix(&matrix_6, &matrix_7, &result), 0);
  for (int i = 0; i < result_test.rows; i++) {
    for (int j = 0; j < result_test.columns; j++) {
      ck_assert_double_eq_tol(result_test.matrix[i][j], result.matrix[i][j],
                              1e-6);
    }
  }
  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&matrix_3);
  s21_remove_matrix(&matrix_4);
  s21_remove_matrix(&matrix_5);
  s21_remove_matrix(&matrix_6);
  s21_remove_matrix(&matrix_7);
  s21_remove_matrix(&result_test);
  s21_remove_matrix(&result);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[45m-=S21_MULT_MATRIX=-\033[0m");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, mult_matrix_1);

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