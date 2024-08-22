#include "s21_matrix_test_oop.h"

TEST(Determinant, Determinant_test_1) {
  double matrix_1[5][5]{{0, 2, 3, 4, 5},
                        {5, 0, 7, 8, 9},
                        {1, 2, 0, 5, -6},
                        {6, 7, 8, 0, 10},
                        {6, 7, 8, 9, 0}};
  S21Matrix matrix_1_(5, 5);
  matrix_1_.build_matrix(5, 5, &matrix_1[0][0], sizeof(matrix_1));
  ASSERT_NEAR(matrix_1_.Determinant(), 4420, 1E-6);
}

TEST(Determinant, Determinant_test_2) {
  double matrix_1[1][1]{2.22};
  S21Matrix matrix_1_(1, 1);
  matrix_1_.build_matrix(1, 1, &matrix_1[0][0], sizeof(matrix_1));
  ASSERT_NEAR(matrix_1_.Determinant(), 2.22, 1E-6);
}

TEST(Determinant, Determinant_test_3) {
  try {
    S21Matrix matrix_1_;
    matrix_1_.Determinant();
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

TEST(Determinant, Determinant_test_4) {
  try {
    double matrix_1[2][3]{{1, 2, 3}, {4, 5, 6}};
    S21Matrix matrix_1_(2, 3);
    matrix_1_.build_matrix(2, 3, &matrix_1[0][0], sizeof(matrix_1));
    matrix_1_.Determinant();
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}