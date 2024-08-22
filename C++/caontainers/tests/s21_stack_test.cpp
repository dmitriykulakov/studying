#include "s21_containers_test.h"

TEST(Stack, Functions) {
  stack<int> stack1;
  EXPECT_EQ(stack1.size(), 0);

  std::initializer_list<int> list2{1, 3, 5, 7, 9};
  stack<int> stack2(list2);
  EXPECT_EQ(stack2.size(), 5);
  EXPECT_EQ(stack2.top(), 9);

  stack<int> stack3(stack2);
  EXPECT_EQ(stack2.size(), 5);
  EXPECT_EQ(stack2.top(), 9);
  EXPECT_EQ(stack3.size(), 5);
  EXPECT_EQ(stack3.top(), 9);

  stack<int> stack4(std::move(stack3));
  EXPECT_EQ(stack3.size(), 0);
  EXPECT_EQ(stack4.size(), 5);
  EXPECT_EQ(stack4.top(), 9);

  stack4.~stack();
  EXPECT_EQ(stack4.size(), 0);

  stack<int> stack5;
  stack5 = stack5;
  stack5 = std::move(stack5);
  stack5 = std::move(stack2);
  EXPECT_EQ(stack2.size(), 0);
  EXPECT_EQ(stack5.size(), 5);
  EXPECT_EQ(stack5.top(), 9);
}

TEST(Stack, Element_access) {
  std::initializer_list<int> list1{1, 3, 5, 7, 9};
  stack<int> stack1(list1);
  EXPECT_EQ(stack1.top(), 9);
}

TEST(Stack, Capacity) {
  std::initializer_list<int> list1{1, 3, 5, 7, 9};
  stack<int> stack1(list1);
  EXPECT_EQ(stack1.size(), 5);
  EXPECT_EQ(stack1.empty(), false);

  stack<int> stack2;
  EXPECT_EQ(stack2.empty(), true);
}

TEST(Stack, Modifiers) {
  stack<int> stack1;
  stack1.push(-1);
  stack1.push(-2);
  EXPECT_EQ(stack1.size(), 2);
  EXPECT_EQ(stack1.top(), -2);

  stack<int> stack2;
  stack2.swap(stack1);
  EXPECT_EQ(stack1.size(), 0);
  EXPECT_EQ(stack2.size(), 2);
  EXPECT_EQ(stack2.top(), -2);

  stack2.pop();
  EXPECT_EQ(stack2.size(), 1);
  EXPECT_EQ(stack2.top(), -1);
  stack2.pop();
  EXPECT_EQ(stack2.size(), 0);

  EXPECT_THROW(stack2.top(), std::out_of_range);
}

TEST(Stack, Part_3) {
  stack<int> stack1;
  stack1.push(-1);
  stack1.push(-2);
  EXPECT_EQ(stack1.size(), 2);
  EXPECT_EQ(stack1.top(), -2);

  stack1.insert_many_front(-3, -4, -5);
  EXPECT_EQ(stack1.size(), 5);
  EXPECT_EQ(stack1.top(), -5);
  stack1.pop();
  EXPECT_EQ(stack1.top(), -4);
  stack1.pop();
  EXPECT_EQ(stack1.top(), -3);
  stack1.pop();
  EXPECT_EQ(stack1.top(), -2);
}
