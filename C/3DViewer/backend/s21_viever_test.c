#include "s21_viever_test.h"

START_TEST(viever_1) {
  data_t count;
  matrix_t matrix_of_vertexes = {NULL, 0, 0};
  polygon_t *polygons = NULL;
  int count_edges;
  char filename[256] = "./Object_files/cube_first.obj";
  ck_assert_int_eq(
      parsing(filename, &count, &matrix_of_vertexes, &polygons, &count_edges),
      0);
  double result[9][3] = {
      {0, 0, 0},          {0.5, 0.5, -0.5}, {0.5, -0.5, -0.5},
      {0.5, 0.5, 0.5},    {0.5, -0.5, 0.5}, {-0.5, 0.5, -0.5},
      {-0.5, -0.5, -0.5}, {-0.5, 0.5, 0.5}, {-0.5, -0.5, 0.5}};
  for (int i = 1; i < matrix_of_vertexes.rows; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(result[i][j], matrix_of_vertexes.matrix[i][j],
                              1e-6);
    }
  }
  move_figure(&matrix_of_vertexes, 1, 1, 1);
  rotate_figure(&matrix_of_vertexes, 180, 180, 180);
  change_figure(&matrix_of_vertexes, 2);
  double result2[9][3] = {{0, 0, 0}, {3, 3, 1}, {3, 1, 1}, {3, 3, 3}, {3, 1, 3},
                          {1, 3, 1}, {1, 1, 1}, {1, 3, 3}, {1, 1, 3}};
  for (int i = 1; i < matrix_of_vertexes.rows; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_double_eq_tol(result2[i][j], matrix_of_vertexes.matrix[i][j],
                              1e-6);
    }
  }
  free_memory(&matrix_of_vertexes, &polygons, count.count_of_facets);
}
END_TEST

START_TEST(viever_2) {
  data_t count;
  matrix_t matrix_of_vertexes = {NULL, 0, 0};
  polygon_t *polygons = NULL;
  int count_edges;
  char filename[256] = "./Object_files/skull.obj";
  ck_assert_int_eq(
      parsing(filename, &count, &matrix_of_vertexes, &polygons, &count_edges),
      0);
  free_memory(&matrix_of_vertexes, &polygons, count.count_of_facets);
}
END_TEST

START_TEST(viever_3) {
  data_t count;
  matrix_t matrix_of_vertexes = {NULL, 0, 0};
  polygon_t *polygons = NULL;
  int count_edges;
  char filename1[256] = "./Object_files/123.obj";
  ck_assert_int_eq(
      parsing(filename1, &count, &matrix_of_vertexes, &polygons, &count_edges),
      3);
  free_memory(&matrix_of_vertexes, &polygons, count.count_of_facets);
  char filename2[256] = "./Makefile";
  count.count_of_facets = 0;
  count.count_of_vertexes = 0;
  ck_assert_int_eq(
      parsing(filename2, &count, &matrix_of_vertexes, &polygons, &count_edges),
      4);
  free_memory(&matrix_of_vertexes, &polygons, count.count_of_facets);
  char filename3[256] = "./Object_files/wrong.obj";
  count.count_of_facets = 0;
  count.count_of_vertexes = 0;
  ck_assert_int_eq(
      parsing(filename3, &count, &matrix_of_vertexes, &polygons, &count_edges),
      2);
  char filename4[256] = "./Object_files/wrong2.obj";
  count.count_of_facets = 0;
  count.count_of_vertexes = 0;
  ck_assert_int_eq(
      parsing(filename4, &count, &matrix_of_vertexes, &polygons, &count_edges),
      2);
  free_memory(&matrix_of_vertexes, &polygons, count.count_of_facets);
}
END_TEST

Suite *suite(void) {
  Suite *suite = suite_create("\033[45m-=S21_viever=-\033[0m");
  TCase *tc = tcase_create("core");

  tcase_add_test(tc, viever_1);
  tcase_add_test(tc, viever_2);
  tcase_add_test(tc, viever_3);

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
