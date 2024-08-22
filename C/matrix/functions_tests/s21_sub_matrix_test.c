#include "s21_matrix_test.h"

START_TEST(sub_matrix_1) {
  matrix_t matrix_1 = {NULL, 0, 0};
  s21_create_matrix(3, 3, &matrix_1);
  for (int i = 0; i < matrix_1.rows; i++) {
    for (int j = 0; j < matrix_1.columns; j++) {
      matrix_1.matrix[i][j] = (i + j) * 0.111111111;
    }
  }

  matrix_t matrix_2 = {NULL, 0, 0};
  s21_create_matrix(2, 2, &matrix_2);
  for (int i = 0; i < matrix_2.rows; i++) {
    for (int j = 0; j < matrix_2.columns; j++) {
      matrix_2.matrix[i][j] = (i + j) * 0.111111111;
    }
  }

  matrix_t matrix_3 = {NULL, 0, 0};

  matrix_t matrix_4 = {NULL, 0, 0};
  s21_create_matrix(3, 3, &matrix_4);
  for (int i = 0; i < matrix_4.rows; i++) {
    for (int j = 0; j < matrix_4.columns; j++) {
      matrix_4.matrix[i][j] = (i + j) * -0.111111111;
    }
  }

  matrix_t result = {NULL, 0, 0};
  matrix_t result_1_test = {NULL, 0, 0};
  s21_create_matrix(3, 3, &result_1_test);
  for (int i = 0; i < result_1_test.rows; i++) {
    for (int j = 0; j < result_1_test.columns; j++) {
      result_1_test.matrix[i][j] = (i + j) * 0.222222222;
    }
  }

  ck_assert_int_eq(s21_sub_matrix(&matrix_1, &matrix_2, &result), 2);
  ck_assert_int_eq(s21_sub_matrix(&matrix_1, NULL, &result), 1);
  ck_assert_int_eq(s21_sub_matrix(NULL, &matrix_2, &result), 1);
  ck_assert_int_eq(s21_sub_matrix(&matrix_3, &matrix_2, &result), 1);
  ck_assert_int_eq(s21_sub_matrix(&matrix_2, &matrix_2, NULL), 1);
  ck_assert_int_eq(s21_sub_matrix(&matrix_1, &matrix_1, &result), 0);
  ck_assert_int_eq(matrix_1.rows, result.rows);
  ck_assert_int_eq(matrix_1.columns, result.columns);
  for (int i = 0; i < matrix_1.rows; i++) {
    for (int j = 0; j < matrix_1.columns; j++) {
      ck_assert_double_eq_tol(0, result.matrix[i][j], 1e-6);
    }
  }
  s21_remove_matrix(&result);

  // matrix_t result = {NULL, 0, 0};
  ck_assert_int_eq(s21_sub_matrix(&matrix_1, &matrix_4, &result), 0);
  for (int i = 0; i < result_1_test.rows; i++) {
    for (int j = 0; j < result_1_test.columns; j++) {
      ck_assert_double_eq_tol(result_1_test.matrix[i][j], result.matrix[i][j],
                              1e-6);
    }
  }

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&matrix_3);
  s21_remove_matrix(&matrix_4);
  s21_remove_matrix(&result);
  s21_remove_matrix(&result_1_test);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[45m-=S21_SUB_MATRIX=-\033[0m");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, sub_matrix_1);

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