#include "s21_containers_test.h"

TEST(vector, Functions) {
  Vector<int> vector1;
  EXPECT_EQ(vector1.size(), 0);

  Vector<int> vector2{1, 3, 5, 7, 9};
  EXPECT_EQ(vector2.size(), 5);
  EXPECT_EQ(vector2.front(), 1);
  EXPECT_EQ(vector2.back(), 9);

  Vector<int> vector3(vector2);
  EXPECT_EQ(vector2.size(), 5);
  EXPECT_EQ(vector2.front(), 1);
  EXPECT_EQ(vector2.back(), 9);
  EXPECT_EQ(vector3.size(), 5);
  EXPECT_EQ(vector3.front(), 1);
  EXPECT_EQ(vector3.back(), 9);

  Vector<int> vector4(std::move(vector3));
  EXPECT_EQ(vector3.size(), 0);
  EXPECT_EQ(vector4.size(), 5);
  EXPECT_EQ(vector4.front(), 1);
  EXPECT_EQ(vector4.back(), 9);

  vector4.~Vector();
  EXPECT_EQ(vector4.size(), 0);

  Vector<int> vector5;
  vector5 = vector5;
  vector5 = std::move(vector5);
  EXPECT_EQ(vector5.size(), 0);

  Vector<int> vector6(0);
  EXPECT_EQ(vector6.size(), 0);
  Vector<int> vector7(7);
  EXPECT_EQ(vector7.size(), 7);
  EXPECT_EQ(vector7.front(), 0);
  EXPECT_EQ(vector7.back(), 0);

  Vector<int> vector8(0);
  Vector<int> vector9(vector8);
  EXPECT_EQ(vector9.size(), 0);

  Vector<int> vector10{1, 3, 5, 7, 9};
  Vector<int> vector11{5, 6, 7, 8, 9};
  Vector<int> vector12;
  vector11 = vector10;
  EXPECT_EQ(vector11.size(), 5);
  EXPECT_EQ(vector11.front(), 1);
  EXPECT_EQ(vector11.back(), 9);

  vector11 = vector12;
  EXPECT_EQ(vector11.size(), 0);

  vector11 = std::move(vector10);
  EXPECT_EQ(vector11.size(), 5);
  EXPECT_EQ(vector11.front(), 1);
  EXPECT_EQ(vector11.back(), 9);
  EXPECT_EQ(vector10.size(), 0);

  vector11 = std::move(vector12);
  EXPECT_EQ(vector11.size(), 0);
  EXPECT_EQ(vector12.size(), 0);
}

TEST(vector, Element_access) {
  Vector<int> vector1{1, 3, 5, 7, 9};
  EXPECT_EQ(vector1.front(), 1);
  EXPECT_EQ(vector1.back(), 9);
  EXPECT_EQ(vector1.at(2), 5);
  vector1.at(2) = 10;
  EXPECT_EQ(vector1.at(2), 10);
  EXPECT_EQ(vector1[3], 7);
  vector1[3] = 15;
  EXPECT_EQ(vector1[3], 15);

  Vector<int> vector2{1, 3, 5, 7, 9};
  Vector<int> vector3;
  EXPECT_THROW(vector2.at(6), std::out_of_range);
  EXPECT_THROW(vector3.at(0), std::out_of_range);

  Vector<int> vector4{1, 3, 5, 7, 9};
  EXPECT_EQ(vector4.data() != nullptr, 1);
}

TEST(vector, Iterators) {
  Vector<int> vector1{1, 3, 5, 7, 9};
  EXPECT_EQ(*vector1.begin(), 1);
  auto it = vector1.end();
  --it;
  EXPECT_EQ(*it, 9);
}

TEST(vector, Capacity) {
  Vector<int> vector1{1, 3, 5, 7, 9};
  EXPECT_EQ(vector1.size(), 5);
  EXPECT_EQ(vector1.empty(), false);

  Vector<int> vector2;
  EXPECT_EQ(vector2.empty(), true);

  EXPECT_EQ(vector1.max_size() > 0, 1);

  Vector<int> vector3{1, 3, 5, 7, 9};
  EXPECT_EQ(vector3.capacity(), 5);
  vector3.reserve(10);
  EXPECT_EQ(vector3.capacity(), 10);

  vector3.shrink_to_fit();
  EXPECT_EQ(vector3.capacity(), 5);
}

TEST(vector, Modifiers1) {
  Vector<int> vector1{1, 3, 5, 7, 9};
  vector1.clear();
  EXPECT_EQ(vector1.size(), 0);

  Vector<int> vector2{1, 3, 5, 7, 9};
  EXPECT_EQ(*(vector2.insert(vector2.end(), 20)), 20);
  EXPECT_EQ(vector2.size(), 6);
  EXPECT_EQ(vector2[5], 20);
  auto it = vector2.begin();
  EXPECT_EQ(*(vector2.insert(vector2.begin(), 15)), 15);
  EXPECT_EQ(vector2.size(), 7);
  EXPECT_EQ(vector2[0], 15);
  it++;
  EXPECT_EQ(*(vector2.insert(it, 12)), 12);
  EXPECT_EQ(vector2.size(), 8);
  EXPECT_EQ(vector2[1], 12);

  Vector<int> vector3{1, 3, 5, 7, 9};
  vector3.erase(vector3.begin());
  EXPECT_EQ(vector3.front(), 3);
  auto it1 = vector3.end();
  --it1;
  vector3.erase(it1);
  EXPECT_EQ(vector3.back(), 7);

  Vector<int> vector4{1, 3, 5, 7, 9};
  vector4.push_back(15);
  EXPECT_EQ(vector4.size(), 6);
  EXPECT_EQ(vector4[5], 15);

  Vector<int> vector5{1, 3, 5, 7, 9};
  vector5.push_back(15);
  EXPECT_EQ(vector5.size(), 6);
  EXPECT_EQ(vector5[5], 15);

  vector5.pop_back();
  EXPECT_EQ(vector5.size(), 5);

  Vector<int> vector6{1, 3, 5, 7, 0, 10};
  Vector<int> vector7{1, 3, 5, 7, 9};
  vector6.swap(vector7);
  EXPECT_EQ(vector6.size(), 5);
  EXPECT_EQ(vector7.size(), 6);
  EXPECT_EQ(vector7[5], 10);
  EXPECT_EQ(vector6[4], 9);
}

TEST(vector, Modifiers12) {
  Vector<int> vector1{1, 3, 5, 7, 9};
  vector1.insert_many_back(11, 13, 15);
  EXPECT_EQ(vector1.size(), 8);
  EXPECT_EQ(vector1.at(5), 11);
  EXPECT_EQ(vector1.at(6), 13);
  EXPECT_EQ(vector1.at(7), 15);

  Vector<int> vector2{1, 3, 5, 7, 9};
  vector2.insert_many(vector2.begin(), 11, 13);
  EXPECT_EQ(vector2.at(0), 13);
  EXPECT_EQ(vector2.at(1), 11);
  EXPECT_EQ(vector2.at(2), 1);
}