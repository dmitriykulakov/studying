#include "s21_matrix_test.h"

START_TEST(sum_matrix_1) {
  matrix_t matrix_1 = {NULL, 0, 0};
  s21_create_matrix(3, 3, &matrix_1);
  for (int i = 0; i < matrix_1.rows; i++) {
    for (int j = 0; j < matrix_1.columns; j++) {
      matrix_1.matrix[i][j] = (i + j) * 1.111111111;
    }
  }

  matrix_t matrix_2 = {NULL, 0, 0};
  s21_create_matrix(2, 2, &matrix_2);
  for (int i = 0; i < matrix_2.rows; i++) {
    for (int j = 0; j < matrix_2.columns; j++) {
      matrix_2.matrix[i][j] = (i + j) * 1.111111111;
    }
  }

  matrix_t matrix_3 = {NULL, 0, 0};

  matrix_t result = {NULL, 0, 0};
  matrix_t result_test = {NULL, 0, 0};
  s21_create_matrix(3, 3, &result_test);
  for (int i = 0; i < result_test.rows; i++) {
    for (int j = 0; j < result_test.columns; j++) {
      result_test.matrix[i][j] = (i + j) * 2.222222222;
    }
  }

  ck_assert_int_eq(s21_sum_matrix(&matrix_1, &matrix_2, &result), 2);
  ck_assert_int_eq(s21_sum_matrix(&matrix_1, NULL, &result), 1);
  ck_assert_int_eq(s21_sum_matrix(NULL, &matrix_2, &result), 1);
  ck_assert_int_eq(s21_sum_matrix(&matrix_3, &matrix_2, &result), 1);
  ck_assert_int_eq(s21_sum_matrix(&matrix_2, &matrix_2, NULL), 1);
  ck_assert_int_eq(s21_sum_matrix(&matrix_1, &matrix_1, &result), 0);
  ck_assert_int_eq(result_test.rows, result.rows);
  ck_assert_int_eq(result_test.columns, result.columns);
  for (int i = 0; i < result_test.rows; i++) {
    for (int j = 0; j < result_test.columns; j++) {
      ck_assert_double_eq_tol(result_test.matrix[i][j], result.matrix[i][j],
                              1e-6);
    }
  }

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&matrix_3);
  s21_remove_matrix(&result);
  s21_remove_matrix(&result_test);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[45m-=S21_SUM_MATRIX=-\033[0m");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, sum_matrix_1);

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