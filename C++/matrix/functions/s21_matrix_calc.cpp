#include "../s21_matrix_oop.h"

S21Matrix S21Matrix::CalcComplements() {
  checkZeroMatrix();
  checkSquareMatrix();
  S21Matrix result(this->rows_, this->cols_);
  if (this->rows_ == 1)
    result.matrix_[0][0] = 1;
  else {
    for (int i{}; i < this->rows_; i++) {
      for (int j{}; j < this->cols_; j++) {
        S21Matrix tmp_matrix(this->rows_ - 1, this->cols_ - 1);
        result.matrix_[i][j] = tmp_matrix.s21_minor_count(*this, i, j);
        if ((i + j) % 2 == 1)
          result.matrix_[i][j] = result.matrix_[i][j] * (-1);
      }
    }
  }
  return result;
}

double S21Matrix::s21_minor_count(const S21Matrix& A, int i, int j) {
  for (int k = 0, m = 0; k < this->rows_; k++, m++) {
    for (int t = 0, n = 0; t < this->cols_; t++, n++) {
      if (m == i) m++;
      if (n == j) n++;
      this->matrix_[k][t] = A.matrix_[m][n];
    }
  }
  return this->Determinant();
}