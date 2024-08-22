#include "s21_matrix_test_oop.h"

TEST(MUL, Mul_test_1) {
  double matrix_1[3][3]{{1, 2, 3}, {4, 5, 6}, {1, 2, 3}};
  double result[3][3]{{2, 4, 6}, {8, 10, 12}, {2, 4, 6}};
  S21Matrix matrix_1_(3, 3);
  matrix_1_.build_matrix(3, 3, &matrix_1[0][0], sizeof(matrix_1));
  S21Matrix result_(3, 3);
  result_.build_matrix(3, 3, &result[0][0], sizeof(result));
  matrix_1_.MulNumber(2.0);
  for (int i{}; i < 3; i++) {
    for (int j{}; j < 3; j++) {
      ASSERT_NEAR(matrix_1_(i, j), result_(i, j), 1E-6);
    }
  }
}

TEST(MUL, Mul_test_2) {
  double matrix_1[3][3]{{1, 2, 3}, {4, 5, 6}, {1, 2, 3}};
  double result[3][3]{{2, 4, 6}, {8, 10, 12}, {2, 4, 6}};
  S21Matrix matrix_1_(3, 3);
  matrix_1_.build_matrix(3, 3, &matrix_1[0][0], sizeof(matrix_1));
  S21Matrix matrix_2_;
  S21Matrix result_(3, 3);
  result_.build_matrix(3, 3, &result[0][0], sizeof(result));
  matrix_2_ = matrix_1_ * 2;
  for (int i{}; i < 3; i++) {
    for (int j{}; j < 3; j++) {
      ASSERT_NEAR(matrix_2_(i, j), result_(i, j), 1E-6);
    }
  }
}

TEST(Mul, Mul_test_3) {
  double matrix_1[3][3]{{1, 2, 3}, {4, 5, 6}, {1, 2, 3}};
  double result[3][3]{{2, 4, 6}, {8, 10, 12}, {2, 4, 6}};
  S21Matrix matrix_1_(3, 3);
  matrix_1_.build_matrix(3, 3, &matrix_1[0][0], sizeof(matrix_1));
  S21Matrix result_(3, 3);
  result_.build_matrix(3, 3, &result[0][0], sizeof(result));
  matrix_1_ *= 2;
  for (int i{}; i < 3; i++) {
    for (int j{}; j < 3; j++) {
      ASSERT_NEAR(matrix_1_(i, j), result_(i, j), 1E-6);
    }
  }
}

TEST(MUL, Mul_test_4) {
  try {
    S21Matrix matrix_1_;
    matrix_1_.MulNumber(22.4);
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

TEST(MUL, Mul_test_5) {
  double matrix_1[3][3]{{1, 2, 3}, {4, 5, 6}, {1, 2, 3}};
  double result[3][3]{{12, 18, 24}, {30, 45, 60}, {12, 18, 24}};
  S21Matrix matrix_1_(3, 3);
  matrix_1_.build_matrix(3, 3, &matrix_1[0][0], sizeof(matrix_1));
  S21Matrix result_(3, 3);
  result_.build_matrix(3, 3, &result[0][0], sizeof(result));
  matrix_1_.MulMatrix(matrix_1_);
  for (int i{}; i < 3; i++) {
    for (int j{}; j < 3; j++) {
      ASSERT_NEAR(matrix_1_(i, j), result_(i, j), 1E-6);
    }
  }
}

TEST(MUL, Mul_test_6) {
  double matrix_1[2][3]{{44.2, 123.8, 3.01}, {22.3, 23.1, 44.2}};
  double matrix_2[3][2]{{22.3, 12.4}, {42.12, 33.1}, {12.2, 66.34}};
  double result[3][3]{{1262.180000, 3047.180000, 615.203000},
                      {2599.834000, 5979.066000, 1589.801200},
                      {2018.622000, 3042.814000, 2968.950000}};
  S21Matrix matrix_1_(2, 3);
  matrix_1_.build_matrix(2, 3, &matrix_1[0][0], sizeof(matrix_1));
  S21Matrix matrix_2_(3, 2);
  matrix_2_.build_matrix(3, 2, &matrix_2[0][0], sizeof(matrix_2));
  S21Matrix result_(3, 3);
  result_.build_matrix(3, 3, &result[0][0], sizeof(result));
  S21Matrix matrix_3_ = matrix_2_ * matrix_1_;
  for (int i{}; i < 3; i++) {
    for (int j{}; j < 3; j++) {
      ASSERT_NEAR(matrix_3_(i, j), result_(i, j), 1E-6);
    }
  }
}

TEST(MUL, Mul_test_7) {
  double matrix_1[2][3]{{44.2, 123.8, 3.01}, {22.3, 23.1, 44.2}};
  double matrix_2[3][2]{{22.3, 12.4}, {42.12, 33.1}, {12.2, 66.34}};
  double result[3][3]{{1262.180000, 3047.180000, 615.203000},
                      {2599.834000, 5979.066000, 1589.801200},
                      {2018.622000, 3042.814000, 2968.950000}};
  S21Matrix matrix_1_(2, 3);
  matrix_1_.build_matrix(2, 3, &matrix_1[0][0], sizeof(matrix_1));
  S21Matrix matrix_2_(3, 2);
  matrix_2_.build_matrix(3, 2, &matrix_2[0][0], sizeof(matrix_2));
  S21Matrix result_(3, 3);
  result_.build_matrix(3, 3, &result[0][0], sizeof(result));
  matrix_2_ *= matrix_1_;
  for (int i{}; i < 3; i++) {
    for (int j{}; j < 3; j++) {
      ASSERT_NEAR(matrix_2_(i, j), result_(i, j), 1E-6);
    }
  }
}

TEST(MUL, Mul_test_8) {
  try {
    double matrix_1[3][3]{{1, 2, 3}, {4, 5, 6}, {1, 2, 3}};
    S21Matrix matrix_1_(3, 3);
    matrix_1_.build_matrix(3, 3, &matrix_1[0][0], sizeof(matrix_1));
    S21Matrix matrix_2_;
    matrix_1_.MulMatrix(matrix_2_);
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

TEST(MUL, Mul_test_9) {
  try {
    double matrix_1[2][3]{{1, 2, 3}, {4, 5, 6}};
    S21Matrix matrix_1_(2, 3);
    matrix_1_.build_matrix(2, 3, &matrix_1[0][0], sizeof(matrix_1));
    matrix_1_.MulMatrix(matrix_1_);
    ASSERT_ANY_THROW();
  } catch (const std::out_of_range& ex) {
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}