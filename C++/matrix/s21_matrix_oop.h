#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <iostream>

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix_ = nullptr;

 public:
  S21Matrix();
  S21Matrix(int rows, int cols);
  ~S21Matrix();
  void free_matrix();
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  void checkZeroMatrix() const;
  void checkSquareMatrix() const;
  void build_matrix(int rows, int cols, double* matrix, unsigned size);
  void change_matrix_size(int rows, int cols);
  void print() const;
  int getRows();
  int getCols();
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double num);
  bool operator==(const S21Matrix& other);
  void operator=(const S21Matrix& other);
  void operator+=(const S21Matrix& other);
  void operator-=(const S21Matrix& other);
  void operator*=(const S21Matrix& other);
  void operator*=(const double num);
  double operator()(int i, int j);
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  double s21_minor_count(const S21Matrix& A, int i, int j);
  S21Matrix InverseMatrix();
};

#endif