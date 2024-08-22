#include "../s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int function_result = 0;
  if (s21_check_matrix(A) || result == NULL)
    function_result = 1;
  else if (A->columns != A->rows)
    function_result = 2;
  else if (s21_create_matrix(A->columns, A->rows, result))
    function_result = 1;
  else if (A->columns == 1 && A->rows == 1)
    result->matrix[0][0] = 1;
  else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        matrix_t tmp_result;
        if (s21_create_matrix(A->columns - 1, A->rows - 1, &tmp_result)) {
          function_result = 1;
          s21_remove_matrix(result);
        } else {
          result->matrix[i][j] = 0;
          function_result =
              s21_minor_count(*A, &tmp_result, &(result->matrix[i][j]), i, j);
          s21_remove_matrix(&tmp_result);
          if (function_result != 0) s21_remove_matrix(result);
        }
        if (function_result == 0 && (i + j) % 2 == 1)
          result->matrix[i][j] = result->matrix[i][j] * (-1);
      }
    }
  }
  return function_result;
}

int s21_minor_count(matrix_t A, matrix_t *tmp_result, double *minor, int i,
                    int j) {
  int function_result = 0;
  for (int k = 0, m = 0; k < tmp_result->rows; k++, m++) {
    for (int t = 0, n = 0; t < tmp_result->columns; t++, n++) {
      if (m == i) m++;
      if (n == j) n++;
      tmp_result->matrix[k][t] = A.matrix[m][n];
    }
  }
  function_result = s21_determinant(tmp_result, minor);
  return function_result;
}