#include "../s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int function_result = 0;
  if (result == NULL)
    function_result = 1;
  else if (rows < 1 || columns < 1)
    function_result = 1;
  else {
    result->matrix = (double **)malloc(rows * sizeof(double *));
    if (result->matrix == NULL)
      function_result = 1;
    else {
      for (int i = 0; i < rows && function_result == 0; ++i) {
        result->matrix[i] = (double *)malloc(columns * sizeof(double));
        if (result->matrix[i] == NULL) {
          free(result->matrix);
          function_result = 1;
        }
      }
    }
    result->rows = rows;
    result->columns = columns;
  }
  return function_result;
}
