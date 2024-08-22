#include "s21_matrix_test_oop.h"

TEST(Matrix, Matrix_test_1) {
  S21Matrix matrix_1_;
  ASSERT_EQ(matrix_1_.getRows(), 0);
  ASSERT_EQ(matrix_1_.getCols(), 0);
  S21Matrix matrix_2_(3, 3);
  ASSERT_EQ(matrix_2_.getRows(), 3);
  ASSERT_EQ(matrix_2_.getCols(), 3);
  for (int i{}; i < 3; i++) {
    for (int j{}; j < 3; j++) {
      ASSERT_NEAR(matrix_2_(i, j), 0, 1E-6);
    }
  }
  double matrix_2[3][3]{{1, 2, 3}, {4, 5, 6}, {1, 2, 3}};
  matrix_2_.build_matrix(3, 3, &matrix_2[0][0], sizeof(matrix_2));
  S21Matrix matrix_3_{matrix_2_};
  ASSERT_EQ(matrix_3_.getRows(), 3);
  ASSERT_EQ(matrix_3_.getCols(), 3);
  for (int i{}; i < 3; i++) {
    for (int j{}; j < 3; j++) {
      ASSERT_NEAR(matrix_2_(i, j), matrix_3_(i, j), 1E-6);
    }
  }
  S21Matrix matrix_4_{std::move(matrix_3_)};
  for (int i{}; i < 3; i++) {
    for (int j{}; j < 3; j++) {
      ASSERT_NEAR(matrix_4_(i, j), matrix_2_(i, j), 1E-6);
    }
  }
  ASSERT_EQ(matrix_3_.getRows(), 0);
  ASSERT_EQ(matrix_3_.getCols(), 0);
  matrix_4_.change_matrix_size(2, 3);
  ASSERT_EQ(matrix_4_.getRows(), 2);
  ASSERT_EQ(matrix_4_.getCols(), 3);
  for (int i{}; i < 2; i++) {
    for (int j{}; j < 3; j++) {
      ASSERT_NEAR(matrix_4_(i, j), matrix_2_(i, j), 1E-6);
    }
  }
  matrix_4_.change_matrix_size(4, 4);
  ASSERT_EQ(matrix_4_.getRows(), 4);
  ASSERT_EQ(matrix_4_.getCols(), 4);
  for (int i{}; i < 2; i++) {
    for (int j{}; j < 3; j++) {
      ASSERT_NEAR(matrix_4_(i, j), matrix_2_(i, j), 1E-6);
    }
  }
  ASSERT_NEAR(matrix_4_(0, 3), 0, 1E-6);
  ASSERT_NEAR(matrix_4_(1, 3), 0, 1E-6);
  for (int i{2}; i < 4; i++) {
    for (int j{}; j < 4; j++) {
      ASSERT_NEAR(matrix_4_(i, j), 0, 1E-6);
    }
  }
  S21Matrix matrix_5_{matrix_1_};
  ASSERT_EQ(matrix_5_.getRows(), 0);
  ASSERT_EQ(matrix_5_.getCols(), 0);
  matrix_4_.print();
}

TEST(Matrix, Matrix_test_2) {
  try {
    S21Matrix matrix_1_(0, 3);
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

TEST(Matrix, Matrix_test_3) {
  try {
    S21Matrix matrix_1_(10, 0);
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

TEST(Matrix, Matrix_test_4) {
  try {
    S21Matrix matrix_1_(10, 0);
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

TEST(Matrix, Matrix_test_5) {
  try {
    S21Matrix matrix_1_;
    matrix_1_.checkZeroMatrix();
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

TEST(Matrix, Matrix_test_6) {
  try {
    S21Matrix matrix_1_(3, 4);
    matrix_1_.checkSquareMatrix();
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

TEST(Matrix, Matrix_test_7) {
  try {
    S21Matrix matrix_2_(3, 3);
    double matrix_2[3][3]{{1, 2, 3}, {4, 5, 6}, {1, 2, 3}};
    matrix_2_.build_matrix(0, 3, &matrix_2[0][0], sizeof(matrix_2));
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

TEST(Matrix, Matrix_test_8) {
  try {
    S21Matrix matrix_2_(3, 3);
    double matrix_2[3][3]{{1, 2, 3}, {4, 5, 6}, {1, 2, 3}};
    matrix_2_.build_matrix(4, 3, &matrix_2[0][0], sizeof(matrix_2));
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

TEST(Matrix, Matrix_test_9) {
  try {
    S21Matrix matrix_2_(3, 3);
    double matrix_2[3][3]{{1, 2, 3}, {4, 5, 6}, {1, 2, 3}};
    matrix_2_.build_matrix(3, 4, &matrix_2[0][0], sizeof(matrix_2));
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

TEST(Matrix, Matrix_test_10) {
  try {
    S21Matrix matrix_2_(3, 3);
    double matrix_2[4][3]{{1, 2, 3}, {4, 5, 6}, {1, 2, 3}};
    matrix_2_.build_matrix(3, 3, &matrix_2[0][0], sizeof(matrix_2));
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

TEST(Matrix, Matrix_test_11) {
  try {
    S21Matrix matrix_1_(3, 3);
    matrix_1_(-1, 3);
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

TEST(Matrix, Matrix_test_12) {
  try {
    S21Matrix matrix_1_(3, 3);
    matrix_1_(3, 5);
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

TEST(Matrix, Matrix_test_13) {
  try {
    S21Matrix matrix_1_(3, 3);
    matrix_1_.build_matrix(3, 3, nullptr, 72);
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}