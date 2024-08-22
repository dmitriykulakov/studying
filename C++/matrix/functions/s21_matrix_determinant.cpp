#include "../s21_matrix_oop.h"

double S21Matrix::Determinant() {
  checkZeroMatrix();
  checkSquareMatrix();
  if (this->rows_ == 1) return this->matrix_[0][0];
  if (this->rows_ == 2)
    return this->matrix_[0][0] * this->matrix_[1][1] -
           this->matrix_[0][1] * this->matrix_[1][0];
  double result = 0.0;
  for (int j = 0; j < this->cols_; j++) {
    S21Matrix tmp_matrix(this->rows_ - 1, this->cols_ - 1);
    double minor = tmp_matrix.s21_minor_count(*this, 0, j);
    if (!(j % 2)) result = result + this->matrix_[0][j] * minor;
    if (j % 2) result = result - this->matrix_[0][j] * minor;
  }
  return result;
}