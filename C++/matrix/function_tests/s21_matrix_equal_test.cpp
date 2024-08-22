#include "s21_matrix_test_oop.h"

TEST(Equal, Equal_test_1) {
  double matrix_1[3][3]{{1, 2, 3}, {4, 5, 6}, {1, 2, 3}};
  double matrix_2[3][3]{{1, 2, 3}, {4, 5, 6}, {1, 2, 6}};
  S21Matrix matrix_1_(3, 3);
  matrix_1_.build_matrix(3, 3, &matrix_1[0][0], sizeof(matrix_1));
  S21Matrix matrix_2_(3, 3);
  matrix_2_.build_matrix(3, 3, &matrix_2[0][0], sizeof(matrix_2));
  ASSERT_EQ(matrix_1_.EqMatrix(matrix_2_), 0);
  ASSERT_EQ(matrix_1_ == matrix_1_, 1);
}

TEST(Equal, Equal_test_2) {
  double matrix_1[3][3]{{1, 2, 3}, {4, 5, 6}, {1, 2, 3}};
  double matrix_2[2][3]{{1, 2, 3}, {4, 5, 6}};
  S21Matrix matrix_1_(3, 3);
  matrix_1_.build_matrix(3, 3, &matrix_1[0][0], sizeof(matrix_1));
  S21Matrix matrix_2_(2, 3);
  matrix_2_.build_matrix(2, 3, &matrix_2[0][0], sizeof(matrix_2));
  ASSERT_EQ(matrix_1_.EqMatrix(matrix_2_), 0);
}

TEST(Equal, Equal_test_3) {
  try {
    double matrix_1[3][3]{{1, 2, 3}, {4, 5, 6}, {1, 2, 3}};
    S21Matrix matrix_1_(3, 3);
    matrix_1_.build_matrix(3, 3, &matrix_1[0][0], sizeof(matrix_1));
    S21Matrix matrix_2_;
    matrix_1_.EqMatrix(matrix_2_);
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

TEST(Equal, Equal_test_4) {
  try {
    double matrix_1[3][3]{{1, 2, 3}, {4, 5, 6}, {1, 2, 3}};
    S21Matrix matrix_1_(3, 3);
    matrix_1_.build_matrix(3, 3, &matrix_1[0][0], sizeof(matrix_1));
    S21Matrix matrix_2_;
    matrix_2_.EqMatrix(matrix_1_);
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

TEST(Equal, Equal_test_5) {
  double matrix_1[3][3]{{1, 2, 3}, {4, 5, 6}, {1, 2, 3}};
  S21Matrix matrix_1_(3, 3);
  matrix_1_.build_matrix(3, 3, &matrix_1[0][0], sizeof(matrix_1));
  S21Matrix matrix_2_(3, 3);
  matrix_2_ = matrix_1_;
  ASSERT_EQ(matrix_1_.getRows(), 3);
  ASSERT_EQ(matrix_1_.getCols(), 3);
  for (int i{}; i < 3; i++) {
    for (int j{}; j < 3; j++) {
      ASSERT_NEAR(matrix_1_(i, j), matrix_2_(i, j), 1E-6);
    }
  }
}

TEST(Equal, Equal_test_6) {
  double matrix_1[3][3]{{1, 2, 3}, {4, 5, 6}, {1, 2, 3}};
  S21Matrix matrix_1_(3, 3);
  matrix_1_.build_matrix(3, 3, &matrix_1[0][0], sizeof(matrix_1));
  S21Matrix matrix_2_(2, 3);
  matrix_2_ = matrix_1_;
  ASSERT_EQ(matrix_2_.getRows(), 3);
  ASSERT_EQ(matrix_2_.getCols(), 3);
  for (int i{}; i < 3; i++) {
    for (int j{}; j < 3; j++) {
      ASSERT_NEAR(matrix_1_(i, j), matrix_2_(i, j), 1E-6);
    }
  }
}

TEST(Equal, Equal_test_7) {
  double matrix_1[3][3]{{1, 2, 3}, {4, 5, 6}, {1, 2, 3}};
  S21Matrix matrix_1_(3, 3);
  matrix_1_.build_matrix(3, 3, &matrix_1[0][0], sizeof(matrix_1));
  S21Matrix matrix_2_;
  matrix_1_ = matrix_2_;
  ASSERT_EQ(matrix_1_.getRows(), 0);
  ASSERT_EQ(matrix_1_.getCols(), 0);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}