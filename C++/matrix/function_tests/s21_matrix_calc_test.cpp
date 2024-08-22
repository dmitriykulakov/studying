#include "s21_matrix_test_oop.h"

TEST(Calc, Calc_test_1) {
  double matrix_1[5][5]{{0, 2, 3, 4, 5},
                        {5, 0, 7, 8, 9},
                        {1, 2, 0, 5, -6},
                        {6, 7, 8, 0, 10},
                        {6, 7, 8, 9, 0}};
  double result[5][5]{{-1120, 650, -235, 450, 405},
                      {800, -338, -653, 310, 279},
                      {2100, 1378, -4007, 1090, 981},
                      {1100, 806, -1699, 150, 577},
                      {-1380, -754, 2911, -590, -973}};
  S21Matrix matrix_1_(5, 5);
  matrix_1_.build_matrix(5, 5, &matrix_1[0][0], sizeof(matrix_1));
  S21Matrix result_(5, 5);
  result_.build_matrix(5, 5, &result[0][0], sizeof(result));
  S21Matrix matrix_2_ = matrix_1_.CalcComplements();
  for (int i{}; i < 5; i++) {
    for (int j{}; j < 5; j++) {
      ASSERT_NEAR(matrix_2_(i, j), result_(i, j), 1E-6);
    }
  }
}

TEST(Calc, Calc_test_2) {
  double matrix_1[1][1]{123.12314};
  double result[1][1]{1};
  S21Matrix matrix_1_(1, 1);
  matrix_1_.build_matrix(1, 1, &matrix_1[0][0], sizeof(matrix_1));
  S21Matrix result_(1, 1);
  result_.build_matrix(1, 1, &result[0][0], sizeof(result));
  S21Matrix matrix_2_ = matrix_1_.CalcComplements();
  for (int i{}; i < 1; i++) {
    for (int j{}; j < 1; j++) {
      ASSERT_NEAR(matrix_2_(i, j), result_(i, j), 1E-6);
    }
  }
}

TEST(Calc, Calc_test_3) {
  try {
    double matrix_1[2][3]{{1, 2, 3}, {4, 5, 6}};
    S21Matrix matrix_1_(2, 3);
    matrix_1_.build_matrix(2, 3, &matrix_1[0][0], sizeof(matrix_1));
    matrix_1_.CalcComplements();
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

TEST(Calc, Calc_test_4) {
  try {
    S21Matrix matrix_1_;
    matrix_1_.CalcComplements();
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}