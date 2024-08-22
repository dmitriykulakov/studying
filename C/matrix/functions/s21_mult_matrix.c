#include "../s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int function_result = 0;
  if (s21_check_matrix(A) || s21_check_matrix(B) || result == NULL)
    function_result = 1;
  else if (A->columns != B->rows)
    function_result = 2;
  else if (s21_create_matrix(A->rows, B->columns, result))
    function_result = 1;
  else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        result->matrix[i][j] = 0.0;
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          ;
        }
      }
    }
  }
  return function_result;
}