#include "s21_containers_test.h"

TEST(Queue, Functions) {
  queue<int> queue1;
  EXPECT_EQ(queue1.size(), 0);

  std::initializer_list<int> list2{1, 3, 5, 7, 9};
  queue<int> queue2(list2);
  EXPECT_EQ(queue2.size(), 5);
  EXPECT_EQ(queue2.front(), 1);
  EXPECT_EQ(queue2.back(), 9);

  queue<int> queue3(queue2);
  EXPECT_EQ(queue2.size(), 5);
  EXPECT_EQ(queue2.front(), 1);
  EXPECT_EQ(queue2.back(), 9);
  EXPECT_EQ(queue3.size(), 5);
  EXPECT_EQ(queue3.front(), 1);
  EXPECT_EQ(queue3.back(), 9);

  queue<int> queue4(std::move(queue3));
  EXPECT_EQ(queue3.size(), 0);
  EXPECT_EQ(queue4.size(), 5);
  EXPECT_EQ(queue2.front(), 1);
  EXPECT_EQ(queue2.back(), 9);

  queue4.~queue();
  EXPECT_EQ(queue4.size(), 0);

  queue<int> queue5;
  queue5 = queue5;
  queue5 = std::move(queue5);
  queue5 = std::move(queue2);
  EXPECT_EQ(queue2.size(), 0);
  EXPECT_EQ(queue5.size(), 5);
  EXPECT_EQ(queue5.front(), 1);
  EXPECT_EQ(queue5.back(), 9);
  ;
}

TEST(Queue, Element_access) {
  std::initializer_list<int> list1{1, 3, 5, 7, 9};
  queue<int> queue1(list1);
  EXPECT_EQ(queue1.front(), 1);
  EXPECT_EQ(queue1.back(), 9);
}

TEST(Queue, Capacity) {
  std::initializer_list<int> list1{1, 3, 5, 7, 9};
  queue<int> queue1(list1);
  EXPECT_EQ(queue1.size(), 5);
  EXPECT_EQ(queue1.empty(), false);

  queue<int> queue2;
  EXPECT_EQ(queue2.empty(), true);
}

TEST(Queue, Modifiers) {
  queue<int> queue1;
  queue1.push(-1);
  queue1.push(-2);
  queue1.push(-3);
  EXPECT_EQ(queue1.size(), 3);
  EXPECT_EQ(queue1.front(), -1);
  EXPECT_EQ(queue1.back(), -3);

  queue<int> queue2;
  queue2.swap(queue1);
  EXPECT_EQ(queue1.size(), 0);
  EXPECT_EQ(queue2.size(), 3);
  EXPECT_EQ(queue2.front(), -1);
  EXPECT_EQ(queue2.back(), -3);

  queue2.pop();
  EXPECT_EQ(queue2.size(), 2);
  EXPECT_EQ(queue2.front(), -2);
  EXPECT_EQ(queue2.back(), -3);

  queue2.pop();
  EXPECT_EQ(queue2.size(), 1);
  EXPECT_EQ(queue2.front(), -3);
  EXPECT_EQ(queue2.back(), -3);

  queue2.pop();
  EXPECT_EQ(queue2.size(), 0);

  EXPECT_THROW(queue2.front(), std::out_of_range);
  EXPECT_THROW(queue2.back(), std::out_of_range);
}

TEST(Queue, Part_3) {
  queue<int> queue1;
  queue1.push(1);
  EXPECT_EQ(queue1.size(), 1);
  EXPECT_EQ(queue1.front(), 1);

  queue1.insert_many_back(2, 3, 4);

  EXPECT_EQ(queue1.size(), 4);
  EXPECT_EQ(queue1.front(), 1);
  queue1.pop();
  EXPECT_EQ(queue1.front(), 2);
  queue1.pop();
  EXPECT_EQ(queue1.front(), 3);
  queue1.pop();
  EXPECT_EQ(queue1.front(), 4);
  queue1.pop();

  EXPECT_EQ(queue1.size(), 0);
}