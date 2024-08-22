#include "s21_matrix_test.h"

START_TEST(create_remove_matrix_1) {
  matrix_t result_1 = {NULL, 0, 0};
  ck_assert_int_eq(s21_create_matrix(0, 5, &result_1), 1);

  matrix_t result_2 = {NULL, 0, 0};
  ck_assert_int_eq(s21_create_matrix(5, 0, &result_2), 1);

  ck_assert_int_eq(s21_create_matrix(5, 5, NULL), 1);
}
END_TEST

START_TEST(create_remove_matrix_2) {
  matrix_t result = {NULL, 0, 0};
  ck_assert_int_eq(s21_create_matrix(5, 5, &result), 0);
  ck_assert_int_eq(result.rows, 5);
  ck_assert_int_eq(result.columns, 5);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(create_remove_matrix_3) {
  matrix_t result = {NULL, 0, 0};
  ck_assert_int_eq(s21_create_matrix(1, 2, &result), 0);
  ck_assert_int_eq(result.rows, 1);
  ck_assert_int_eq(result.columns, 2);
  s21_remove_matrix(&result);
  ck_assert_pstr_eq((void *)NULL, (void *)(result.matrix));
}
END_TEST

START_TEST(create_remove_matrix_4) {
  matrix_t result = {NULL, 0, 0};
  ck_assert_int_eq(s21_create_matrix(1, 1, &result), 0);
  ck_assert_int_eq(result.rows, 1);
  ck_assert_int_eq(result.columns, 1);
  s21_remove_matrix(&result);
  ck_assert_pstr_eq((void *)NULL, (void *)(result.matrix));
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[45m-=S21_CREATE_REMOVE_MATRIX=-\033[0m");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, create_remove_matrix_1);
  tcase_add_test(tc, create_remove_matrix_2);
  tcase_add_test(tc, create_remove_matrix_3);
  tcase_add_test(tc, create_remove_matrix_4);
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