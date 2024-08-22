#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int function_result = 0;
  double determinant = 0;
  if (s21_check_matrix(A) || result == NULL)
    function_result = 1;
  else if (A->rows != A->columns)
    function_result = 2;
  else if (A->rows == 1 && A->matrix[0][0] != 0) {
    if (s21_create_matrix(A->columns, A->rows, result))
      function_result = 1;
    else
      result->matrix[0][0] = 1 / A->matrix[0][0];
  } else {
    matrix_t tmp_result;
    matrix_t tmp_result_1;
    function_result = s21_calc_complements(A, &tmp_result) ||
                      s21_determinant(A, &determinant);

    if (function_result == 0) {
      if (determinant == 0)
        function_result = 2;
      else {
        function_result = s21_transpose(&tmp_result, &tmp_result_1);
      }
      s21_remove_matrix(&tmp_result);
    }
    if (function_result == 0) {
      function_result =
          s21_mult_number(&tmp_result_1, (double)1 / determinant, result);
      s21_remove_matrix(&tmp_result_1);
    }
  }
  return function_result;
}
