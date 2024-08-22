#include "s21_matrix_test_oop.h"

TEST(TRANSPOSE, Transpose_test_1) {
  double matrix_1[2][3]{{1, 2, 3}, {4, 5, 6}};
  double result[3][2]{{1, 4}, {2, 5}, {3, 6}};
  S21Matrix matrix_1_(2, 3);
  matrix_1_.build_matrix(2, 3, &matrix_1[0][0], sizeof(matrix_1));
  S21Matrix result_(3, 2);
  result_.build_matrix(3, 2, &result[0][0], sizeof(result));
  matrix_1_ = matrix_1_.Transpose();
  for (int i{}; i < 3; i++) {
    for (int j{}; j < 2; j++) {
      ASSERT_NEAR(matrix_1_(i, j), result_(i, j), 1E-6);
    }
  }
}

TEST(TRANSPOSE, transpose_test_2) {
  try {
    S21Matrix matrix_1_;
    matrix_1_.Transpose();
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}