#include "../s21_matrix_oop.h"

S21Matrix S21Matrix::Transpose() {
  checkZeroMatrix();
  S21Matrix result(this->cols_, this->rows_);
  for (int i{}; i < this->rows_; i++) {
    for (int j{}; j < this->cols_; j++) {
      result.matrix_[j][i] = this->matrix_[i][j];
    }
  }
  return result;
}