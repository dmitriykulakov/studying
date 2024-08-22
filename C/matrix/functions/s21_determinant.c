#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int function_result = 0;
  if (result == NULL)
    function_result = 1;
  else if (s21_check_matrix(A))
    function_result = 1;
  else if (A->rows != A->columns)
    function_result = 2;
  else if (A->rows == 1)
    *result = A->matrix[0][0];
  else if (A->rows == 2)
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  else {
    *result = 0;
    for (int j = 0; j < A->columns; j++) {
      matrix_t tmp_result;
      if (s21_create_matrix(A->columns - 1, A->rows - 1, &tmp_result))
        function_result = 1;
      else {
        double tmp = A->matrix[0][j];
        function_result = s21_minor_count(*A, &tmp_result, &tmp, 0, j);
        s21_remove_matrix(&tmp_result);
        if (function_result == 0 && j % 2 == 0)
          *result = *result + A->matrix[0][j] * tmp;
        if (function_result == 0 && j % 2 == 1)
          *result = *result - A->matrix[0][j] * tmp;
      }
    }
  }
  return function_result;
}