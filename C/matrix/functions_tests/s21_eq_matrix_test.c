#include "s21_matrix_test.h"

START_TEST(eq_matrix_1) {
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

  matrix_t matrix_5 = {NULL, 0, 0};
  s21_create_matrix(3, 3, &matrix_5);
  for (int i = 0; i < matrix_5.rows; i++) {
    for (int j = 0; j < matrix_5.columns; j++) {
      matrix_5.matrix[i][j] = (i + j) * -0.1111111222;
    }
  }

  matrix_t matrix_6 = {NULL, 0, 0};
  s21_create_matrix(3, 3, &matrix_6);
  for (int i = 0; i < matrix_6.rows; i++) {
    for (int j = 0; j < matrix_6.columns; j++) {
      matrix_6.matrix[i][j] = (i + j) * -0.11111222;
    }
  }

  ck_assert_int_eq(s21_eq_matrix(&matrix_1, &matrix_2), 0);
  ck_assert_int_eq(s21_eq_matrix(&matrix_1, NULL), 0);
  ck_assert_int_eq(s21_eq_matrix(NULL, &matrix_2), 0);
  ck_assert_int_eq(s21_eq_matrix(&matrix_3, &matrix_2), 0);
  ck_assert_int_eq(s21_eq_matrix(&matrix_2, &matrix_2), 1);
  ck_assert_int_eq(s21_eq_matrix(&matrix_4, &matrix_5), 1);
  ck_assert_int_eq(s21_eq_matrix(&matrix_4, &matrix_6), 0);
  ck_assert_int_eq(s21_eq_matrix(&matrix_2, &matrix_3), 0);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&matrix_3);
  s21_remove_matrix(&matrix_4);
  s21_remove_matrix(&matrix_5);
  s21_remove_matrix(&matrix_6);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[45m-=S21_eq_MATRIX=-\033[0m");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, eq_matrix_1);

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