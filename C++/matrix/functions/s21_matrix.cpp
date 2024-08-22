#include "../s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int cols) {
  if (rows <= 0)
    throw std::out_of_range("ERROR: The rows_ is less or equal 0!");
  if (cols <= 0)
    throw std::out_of_range("ERROR: The cols is_ less or equal 0!");
  rows_ = rows;
  cols_ = cols;
  if (rows > 0 && cols > 0) {
    matrix_ = new double* [rows_] {};
    for (int i{}; i < rows_; i++) {
      matrix_[i] = new double[cols_]{};
    }
  }
}

S21Matrix::~S21Matrix() { free_matrix(); }

void S21Matrix::free_matrix() {
  for (int i{}; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

S21Matrix::S21Matrix(const S21Matrix& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  if (other.matrix_ != nullptr && rows_ > 0 && cols_ > 0) {
    matrix_ = new double* [rows_] {};
    for (int i{}; i < rows_; i++) {
      matrix_[i] = new double[cols_]{};
    }
    for (int i{}; i < rows_; i++) {
      for (int j{}; j < cols_; j++) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  } else
    matrix_ = nullptr;
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;
  this->matrix_ = other.matrix_;
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

void S21Matrix::checkZeroMatrix() const {
  if (this->rows_ == 0 || this->cols_ == 0)
    throw std::out_of_range("ERROR: The matrix has 0 size!");
}

void S21Matrix::checkSquareMatrix() const {
  if (this->rows_ != this->cols_)
    throw std::out_of_range("ERROR: The matrix is not square!");
}

int S21Matrix::getRows() { return this->rows_; }

int S21Matrix::getCols() { return this->cols_; }

void S21Matrix::build_matrix(int rows, int cols, double* matrix,
                             unsigned size) {
  if (rows == 0 || cols == 0)
    throw std::out_of_range("ERROR: The 0 size matrix!");
  if (matrix == nullptr)
    throw std::out_of_range("ERROR: The matrix adress is nullptr!");
  if (rows != rows_)
    throw std::out_of_range("ERROR: The matrix rows is not equal with rows_!");
  if (cols != cols_)
    throw std::out_of_range("ERROR:  The matrix cols is not equal with cols_!");
  if (size != (unsigned)rows_ * cols_ * 8)
    throw std::out_of_range(
        "ERROR: The size of matrix is not equal with size of matrix_!");
  for (int i{}, k{}; i < rows_; i++) {
    for (int j{}; j < cols_; j++, k++) {
      matrix_[i][j] = matrix[k];
    }
  }
}

void S21Matrix::change_matrix_size(int rows, int cols) {
  S21Matrix tmp(rows, cols);
  for (int i{}; i < rows; i++) {
    for (int j{}; j < cols; j++) {
      if (i < this->rows_ && j < this->cols_)
        tmp.matrix_[i][j] = this->matrix_[i][j];
      else
        tmp.matrix_[i][j] = 0;
    }
  }
  *this = tmp;
}

void S21Matrix::print() const {
  std::cout << "Rows: " << rows_ << "\tcolumns: " << cols_ << std::endl;
  if (rows_ > 0 && cols_ > 0) {
    for (int i{}; i < rows_; i++) {
      for (int j{}; j < cols_; j++) {
        std::cout << matrix_[i][j] << " ";
      }
      std::cout << std::endl;
    }
    std::cout << (void*)matrix_ << std::endl;
  }
}

double S21Matrix::operator()(int i, int j) {
  if (i < 0 || j < 0)
    throw std::out_of_range("ERROR: The index is wrong, less than 0!");
  if (this->rows_ <= i || this->cols_ <= j)
    throw std::out_of_range("ERROR: The matrix doesn't have this element!");
  return this->matrix_[i][j];
}