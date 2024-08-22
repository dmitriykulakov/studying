#include "s21_matrix_test_oop.h"

TEST(Inverse, Inverse_test_1) {
  double matrix_1[5][5]{{0, 2, 3, 4, 5},
                        {5, 0, 7, 8, 9},
                        {1, 2, 0, 5, -6},
                        {6, 7, 8, 0, 10},
                        {6, 7, 8, 9, 0}};
  double result[5][5]{{-0.253394, 0.180995, 0.475113, 0.248869, -0.312217},
                      {0.147059, -0.0764706, 0.311765, 0.182353, -0.170588},
                      {-0.0531674, -0.147738, -0.906561, -0.384389, 0.658597},
                      {0.10181, 0.0701357, 0.246606, 0.0339367, -0.133484},
                      {0.091629, 0.0631222, 0.221946, 0.130543, -0.220136}};
  S21Matrix matrix_1_(5, 5);
  matrix_1_.build_matrix(5, 5, &matrix_1[0][0], sizeof(matrix_1));
  S21Matrix result_(5, 5);
  result_.build_matrix(5, 5, &result[0][0], sizeof(result));
  S21Matrix matrix_2_ = matrix_1_.InverseMatrix();
  for (int i{}; i < 5; i++) {
    for (int j{}; j < 5; j++) {
      ASSERT_NEAR(matrix_2_(i, j), result_(i, j), 1E-6);
    }
  }
}

TEST(Inverse, Inverse_test_2) {
  double matrix_1[1][1]{123.12314};
  double result[1][1]{0.00812195010621074};
  S21Matrix matrix_1_(1, 1);
  matrix_1_.build_matrix(1, 1, &matrix_1[0][0], sizeof(matrix_1));
  S21Matrix result_(1, 1);
  result_.build_matrix(1, 1, &result[0][0], sizeof(result));
  S21Matrix matrix_2_ = matrix_1_.InverseMatrix();
  for (int i{}; i < 1; i++) {
    for (int j{}; j < 1; j++) {
      ASSERT_NEAR(matrix_2_(i, j), result_(i, j), 1E-6);
    }
  }
}

TEST(Inverse, Inverse_test_3) {
  try {
    double matrix_1[2][3]{{1, 2, 3}, {4, 5, 6}};
    S21Matrix matrix_1_(2, 3);
    matrix_1_.build_matrix(2, 3, &matrix_1[0][0], sizeof(matrix_1));
    matrix_1_.InverseMatrix();
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

TEST(Inverse, Inverse_test_4) {
  try {
    S21Matrix matrix_1_;
    matrix_1_.InverseMatrix();
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

TEST(Inverse, Inverse_test_5) {
  try {
    double matrix_1[3][3]{{1, 2, 3}, {4, 5, 6}, {1, 2, 3}};
    S21Matrix matrix_1_(3, 3);
    matrix_1_.build_matrix(3, 3, &matrix_1[0][0], sizeof(matrix_1));
    matrix_1_.InverseMatrix();
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

TEST(Inverse, Inverse_test_6) {
  try {
    S21Matrix matrix_1_(1, 1);
    matrix_1_.InverseMatrix();
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}