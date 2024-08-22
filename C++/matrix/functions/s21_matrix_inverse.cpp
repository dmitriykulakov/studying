#include "../s21_matrix_oop.h"

S21Matrix S21Matrix::InverseMatrix() {
  checkZeroMatrix();
  checkSquareMatrix();
  S21Matrix result(this->rows_, this->cols_);
  if (this->rows_ == 1) {
    if (this->matrix_[0][0] == 0)
      throw std::out_of_range(
          "ERROR: The matrix has only one element and it is 0!");
    else
      result.matrix_[0][0] = 1 / this->matrix_[0][0];
  } else {
    double determinant = this->Determinant();
    if (!determinant) throw std::out_of_range("ERROR: The determinant is 0!");
    result = this->CalcComplements().Transpose() * (1 / determinant);
  }
  return result;
}