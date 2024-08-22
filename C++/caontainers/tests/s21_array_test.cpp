#include "s21_containers_test.h"

TEST(Array, Functions) {
  array<int, 3> array1;
  EXPECT_EQ(array1.size(), 3);

  std::initializer_list<int> l2{1, 3, 5, 7, 9};
  array<int, 5> array2(l2);
  EXPECT_EQ(array2.size(), 5);
  EXPECT_EQ(array2[0], 1);
  EXPECT_EQ(array2[4], 9);

  array<int, 5> array3(array2);
  EXPECT_EQ(array3.size(), 5);
  EXPECT_EQ(array3[0], 1);
  EXPECT_EQ(array3[4], 9);

  array<int, 5> array4(std::move(array3));
  EXPECT_EQ(array4.size(), 5);
  EXPECT_EQ(array4[0], 1);
  EXPECT_EQ(array4[4], 9);

  array4 = std::move(array4);

  array4 = std::move(array2);
  EXPECT_EQ(array4.size(), 5);
  EXPECT_EQ(array4[0], 1);
  EXPECT_EQ(array4[4], 9);
}

TEST(Array, Element_access) {
  std::initializer_list<int> l1{1, 3, 5, 7, 9};
  array<int, 5> array1(l1);
  EXPECT_EQ(array1.at(2), 5);
  EXPECT_EQ(array1[2], 5);
  EXPECT_EQ(array1.front(), 1);
  EXPECT_EQ(array1.back(), 9);
  EXPECT_EQ(*(array1.data()), 1);
}

TEST(Array, Iterators) {
  std::initializer_list<int> l1{1, 3, 5, 7, 9};
  array<int, 5> array1(l1);
  EXPECT_EQ(*(array1.begin()), 1);
  EXPECT_EQ(*array1.end(), 9);
}

TEST(Array, Capacity) {
  std::initializer_list<int> l1{1, 3, 5, 7, 9};
  array<int, 5> array1(l1);
  EXPECT_EQ(array1.size(), 5);
  EXPECT_EQ(array1.empty(), false);

  array<int, 0> array2;
  EXPECT_EQ(array2.empty(), true);

  array2.max_size();
}

TEST(Array, Modifiers) {
  array<int, 3> array1;
  array<int, 3> array2;
  array2.fill(7);

  array2.swap(array1);
  EXPECT_EQ(array1[0], 7);
  EXPECT_EQ(array1[1], 7);
  EXPECT_EQ(array1[2], 7);
}
