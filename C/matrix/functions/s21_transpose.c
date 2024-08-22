#include "../s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {
  int function_result = 0;
  if (s21_check_matrix(A) || result == NULL)
    function_result = 1;
  else if (s21_create_matrix(A->columns, A->rows, result))
    function_result = 1;
  else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return function_result;
}