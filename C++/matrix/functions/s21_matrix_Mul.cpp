#include "../s21_matrix_oop.h"

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

void S21Matrix::operator*=(const S21Matrix& other) { MulMatrix(other); }

void S21Matrix::operator*=(const double num) { MulNumber(num); }

void S21Matrix::MulMatrix(const S21Matrix& other) {
  checkZeroMatrix();
  other.checkZeroMatrix();
  if (this->cols_ != other.rows_)
    throw std::out_of_range("ERROR: The matrixes have wrong size!");
  S21Matrix tmp(this->rows_, other.cols_);
  for (int i{}; i < tmp.rows_; i++) {
    for (int j{}; j < tmp.cols_; j++) {
      tmp.matrix_[i][j] = 0.0;
      for (int k = 0; k < this->cols_; k++) {
        tmp.matrix_[i][j] += this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = tmp;
}

void S21Matrix::MulNumber(const double num) {
  if (this->rows_ == 0 || this->cols_ == 0)
    throw std::out_of_range("ERROR: The matrix has 0 size!");
  for (int i{}; i < this->rows_; i++) {
    for (int j{}; j < this->cols_; j++) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}