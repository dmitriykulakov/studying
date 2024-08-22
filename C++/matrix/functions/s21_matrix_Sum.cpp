#include "../s21_matrix_oop.h"

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

void S21Matrix::operator+=(const S21Matrix& other) { SumMatrix(other); }

void S21Matrix::SumMatrix(const S21Matrix& other) {
  checkZeroMatrix();
  other.print();
  other.checkZeroMatrix();
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_)
    throw std::out_of_range("ERROR: The matrixes have different size!");
  for (int i{}; i < this->rows_; i++) {
    for (int j{}; j < this->cols_; j++) {
      matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }
}