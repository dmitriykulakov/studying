#include "../s21_matrix_oop.h"

bool S21Matrix::EqMatrix(const S21Matrix& other) {
  checkZeroMatrix();
  other.checkZeroMatrix();
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) return 0;
  for (int i{}; i < this->rows_; i++) {
    for (int j{}; j < this->cols_; j++) {
      if (this->matrix_[i][j] != other.matrix_[i][j]) return 0;
    }
  }
  return 1;
}

bool S21Matrix::operator==(const S21Matrix& other) { return EqMatrix(other); }

void S21Matrix::operator=(const S21Matrix& other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    this->free_matrix();
    this->rows_ = other.rows_;
    this->cols_ = other.cols_;
    if (other.matrix_ != nullptr && rows_ > 0 && cols_ > 0) {
      matrix_ = new double* [this->rows_] {};
      for (int i{}; i < other.rows_; i++) {
        this->matrix_[i] = new double[this->cols_]{};
      }
    } else
      this->matrix_ = nullptr;
  }
  for (int i{}; i < this->rows_; i++) {
    for (int j{}; j < this->cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}