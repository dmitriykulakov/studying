#include "s21_matrix_test_oop.h"

TEST(SUB, Sub_test_1) {
  double matrix_1[3][3]{{1, 2, 3}, {4, 5, 6}, {1, 2, 3}};
  S21Matrix matrix_1_(3, 3);
  matrix_1_.build_matrix(3, 3, &matrix_1[0][0], sizeof(matrix_1));
  matrix_1_.SubMatrix(matrix_1_);
  for (int i{}; i < 3; i++) {
    for (int j{}; j < 3; j++) {
      ASSERT_NEAR(matrix_1_(i, j), 0, 1E-6);
    }
  }
}

TEST(SUB, Sub_test_2) {
  double matrix_1[3][3]{{1, 2, 3}, {4, 5, 6}, {1, 2, 3}};
  double matrix_2[3][3]{{2, 4, 6}, {8, 10, 12}, {2, 4, 6}};
  S21Matrix matrix_1_(3, 3);
  matrix_1_.build_matrix(3, 3, &matrix_1[0][0], sizeof(matrix_1));
  S21Matrix matrix_2_(3, 3);
  matrix_2_.build_matrix(3, 3, &matrix_2[0][0], sizeof(matrix_2));
  S21Matrix matrix_3_ = matrix_2_ - matrix_1_;
  for (int i{}; i < 3; i++) {
    for (int j{}; j < 3; j++) {
      ASSERT_NEAR(matrix_3_(i, j), matrix_1_(i, j), 1E-6);
    }
  }
}

TEST(SUB, Sub_test_3) {
  double matrix_1[3][3]{{1, 2, 3}, {4, 5, 6}, {1, 2, 3}};
  double matrix_2[3][3]{{2, 4, 6}, {8, 10, 12}, {2, 4, 6}};
  S21Matrix matrix_1_(3, 3);
  matrix_1_.build_matrix(3, 3, &matrix_1[0][0], sizeof(matrix_1));
  S21Matrix matrix_2_(3, 3);
  matrix_2_.build_matrix(3, 3, &matrix_2[0][0], sizeof(matrix_2));
  matrix_2_ -= matrix_1_;
  for (int i{}; i < 3; i++) {
    for (int j{}; j < 3; j++) {
      ASSERT_NEAR(matrix_2_(i, j), matrix_1_(i, j), 1E-6);
    }
  }
}

TEST(SUB, Sub_test_4) {
  try {
    double matrix_1[3][3]{{1, 2, 3}, {4, 5, 6}, {1, 2, 3}};
    S21Matrix matrix_1_(3, 3);
    matrix_1_.build_matrix(3, 3, &matrix_1[0][0], sizeof(matrix_1));
    S21Matrix matrix_2_;
    matrix_1_.SubMatrix(matrix_2_);
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

TEST(SUB, Sub_test_5) {
  try {
    double matrix_1[3][3]{{1, 2, 3}, {4, 5, 6}, {1, 2, 3}};
    double matrix_2[4][4]{{1, 2, 3}, {4, 5, 6}, {1, 2, 3}};
    S21Matrix matrix_1_(3, 3);
    matrix_1_.build_matrix(3, 3, &matrix_1[0][0], sizeof(matrix_1));
    S21Matrix matrix_2_(4, 4);
    matrix_2_.build_matrix(4, 4, &matrix_2[0][0], sizeof(matrix_2));
    matrix_1_.SubMatrix(matrix_2_);
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}