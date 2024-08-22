#include "../s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int function_result = SUCCESS;
  if (s21_check_matrix(A) || s21_check_matrix(B))
    function_result = FAILURE;
  else if (A->rows != B->rows || A->columns != B->columns)
    function_result = FAILURE;
  else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1E-7L) return FAILURE;
      }
    }
  }
  return function_result;
}

int s21_check_matrix(matrix_t *A) {
  int function_result = 0;
  if (A == NULL)
    function_result = 1;
  else if (A->matrix == NULL || A->rows == 0 || A->columns == 0)
    function_result = 1;
  else {
    for (int i = 0; i < A->rows && function_result == 0; i++) {
      for (int j = 0; j < A->columns && function_result == 0; j++) {
        if (&(A->matrix[i][j]) == NULL)
          function_result = 1;
        else if (A->matrix[i][j] != A->matrix[i][j])
          function_result = 1;
      }
    }
  }
  return function_result;
}