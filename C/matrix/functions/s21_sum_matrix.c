#include "../s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int function_result = 0;
  if (s21_check_matrix(A) || s21_check_matrix(B) || result == NULL)
    function_result = 1;
  else if (A->rows != B->rows || A->columns != B->columns)
    function_result = 2;
  else if (s21_create_matrix(A->rows, A->columns, result))
    function_result = 1;
  else {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return function_result;
}