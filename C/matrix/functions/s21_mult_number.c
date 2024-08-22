#include "../s21_matrix.h"

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int function_result = 0;
  if (s21_check_matrix(A) || result == NULL)
    function_result = 1;
  else if (s21_create_matrix(A->rows, A->columns, result))
    function_result = 1;
  else {
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return function_result;
}