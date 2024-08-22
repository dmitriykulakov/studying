#include "s21_containers_test.h"

TEST(List, Functions) {
  list<int> list1;
  EXPECT_EQ(list1.size(), 0);

  std::initializer_list<int> l2{1, 3, 5, 7, 9};
  list<int> list2(l2);
  EXPECT_EQ(list2.size(), 5);
  EXPECT_EQ(list2.front(), 1);
  EXPECT_EQ(list2.back(), 9);

  list<int> list3(list2);
  EXPECT_EQ(list2.size(), 5);
  EXPECT_EQ(list2.front(), 1);
  EXPECT_EQ(list2.back(), 9);
  EXPECT_EQ(list3.size(), 5);
  EXPECT_EQ(list3.front(), 1);
  EXPECT_EQ(list3.back(), 9);

  list<int> list4(std::move(list3));
  EXPECT_EQ(list3.size(), 0);
  EXPECT_EQ(list4.size(), 5);
  EXPECT_EQ(list4.front(), 1);
  EXPECT_EQ(list4.back(), 9);

  list4.~list();
  EXPECT_EQ(list4.size(), 0);

  list<int> list5;
  list5 = list5;
  list5 = std::move(list5);

  list<int> list6(0);
  EXPECT_EQ(list6.size(), 0);
  list<int> list7(7);
  EXPECT_EQ(list7.size(), 7);
  EXPECT_EQ(list7.front(), 0);
  EXPECT_EQ(list7.back(), 0);

  s21::list<int>::iterator it;
  it = it;
}

TEST(List, Element_access) {
  std::initializer_list<int> l1{1, 3, 5, 7, 9};
  list<int> list1(l1);
  EXPECT_EQ(list1.front(), 1);
  EXPECT_EQ(list1.back(), 9);

  list<int> list2;
  EXPECT_THROW(list2.front(), std::out_of_range);
  EXPECT_THROW(list2.back(), std::out_of_range);
}

TEST(List, Iterators) {
  std::initializer_list<int> l1{1, 3, 5, 7, 9};
  list<int> list1(l1);
  EXPECT_EQ(*list1.begin(), 1);
  EXPECT_EQ(*(--list1.end()), 9);
}

TEST(List, Capacity) {
  std::initializer_list<int> l1{1, 3, 5, 7, 9};
  list<int> list1(l1);
  EXPECT_EQ(list1.size(), 5);
  EXPECT_EQ(list1.empty(), false);

  list<int> list2;
  EXPECT_EQ(list2.empty(), true);

  list2.max_size();
}

TEST(List, Modifiers1) {
  std::initializer_list<int> l1{1, 3, 5, 7, 9};
  list<int> list1(l1);
  list1.clear();
  EXPECT_EQ(list1.size(), 0);

  list<int> list2;
  list2.erase(list2.begin());
  list2.erase(list2.end());

  list<int> list3(l1);
  list3.erase(list3.begin());
  EXPECT_EQ(list3.front(), 3);
  list3.erase(list3.end());
  EXPECT_EQ(list3.back(), 7);
  list3.erase(++list3.begin());
  EXPECT_EQ(list3.size(), 2);
  EXPECT_EQ(list3.front(), 3);
  EXPECT_EQ(list3.back(), 7);

  s21::list<int> list4(l1);
  EXPECT_EQ(*(list4.insert(list4.begin(), 777)), 777);
  EXPECT_EQ(*(++list4.begin()), 1);
  EXPECT_EQ(*(list4.insert(--list4.end(), 888)), 888);
  EXPECT_EQ(*(--(--list4.end())), 9);
  EXPECT_EQ(*(list4.insert(++list4.begin(), -3)), -3);
  EXPECT_EQ(*(list4.insert(--list4.end(), -3)), -3);

  s21::list<int> list5;
  EXPECT_EQ(*(list5.insert(list5.begin(), 777)), 777);
  list5.clear();
  EXPECT_EQ(*(list5.insert(list5.end(), 777)), 777);

  s21::list<int> list6;
  list6.push_front(7);
  EXPECT_EQ(list6.size(), 1);
  EXPECT_EQ(list6.front(), 7);
  list6.pop_front();
  EXPECT_EQ(list6.size(), 0);
  list6.clear();
  list6.push_back(7);
  EXPECT_EQ(list6.size(), 1);
  EXPECT_EQ(list6.back(), 7);
  list6.pop_back();
  EXPECT_EQ(list6.size(), 0);
}

TEST(List, Modifiers12) {
  std::initializer_list<int> l1{1, 3, 5, 7, 9};
  list<int> list1(l1);

  s21::list<int> list7(l1);
  list7.push_front(7);
  EXPECT_EQ(list7.size(), 6);
  EXPECT_EQ(list7.front(), 7);
  list7.pop_front();
  EXPECT_EQ(list7.size(), 5);
  list7.push_back(7);
  EXPECT_EQ(list7.size(), 6);
  EXPECT_EQ(list7.back(), 7);
  list7.pop_back();
  EXPECT_EQ(list7.size(), 5);

  s21::list<int> list8(l1);
  s21::list<int> list9;
  list8.swap(list9);
  EXPECT_EQ(list8.size(), 0);
  EXPECT_EQ(list9.size(), 5);

  std::initializer_list<int> l21{1, 3, 2};
  s21::list<int> list21(l21);

  std::initializer_list<int> l22{1, 3, 7, 3, 4, 5, 6};
  s21::list<int> list22(l22);

  list21.sort();
  list22.sort();

  list21.merge(list22);
  EXPECT_EQ(list21.size(), 10);
  EXPECT_EQ(list21.front(), 1);
  EXPECT_EQ(list21.back(), 7);
}

TEST(List, Modifiers13) {
  std::initializer_list<int> l1{1, 3, 5, 7, 9};
  list<int> list1(l1);

  std::initializer_list<int> l21{1, 3, 2};
  s21::list<int> list21(l21);

  list21.merge(list21);
  EXPECT_EQ(list21.size(), 3);
  EXPECT_EQ(list21.front(), 1);
  EXPECT_EQ(list21.back(), 2);

  std::initializer_list<int> l23{1, 2, 3, 4};
  s21::list<int> list23(l23);

  std::initializer_list<int> l24{7, 8, 9};
  s21::list<int> list24(l24);

  list23.splice(list23.begin(), list23);
  EXPECT_EQ(list23.size(), 4);

  list23.splice(list23.begin(), list24);
  EXPECT_EQ(list23.size(), 7);
  EXPECT_EQ(list23.front(), 7);
  EXPECT_EQ(list24.size(), 0);

  s21::list<int> list31(l1);
  list31.reverse();
  EXPECT_EQ(list31.front(), 9);
  list31.pop_front();
  EXPECT_EQ(list31.front(), 7);
  list31.pop_front();
  EXPECT_EQ(list31.front(), 5);
  list31.pop_front();
  EXPECT_EQ(list31.front(), 3);
  list31.pop_front();
  EXPECT_EQ(list31.front(), 1);
  list31.pop_front();

  std::initializer_list<int> l2{1, 1, 3, 3, 5, 1, 7, 9, 11, 12, 13, 13};
  s21::list<int> list32(l2);
  list32.unique();
  EXPECT_EQ(list32.size(), 8);

  std::initializer_list<int> l3{9, 11, 12, 13, 13, 1, 1, 3, 3, 5, 1, 7};
  s21::list<int> list33(l3);
  list33.sort();
  EXPECT_EQ(list33.front(), 1);
  EXPECT_EQ(list33.back(), 13);
}

TEST(List, Part_3) {
  std::initializer_list<int> l1{3, 7, 8};
  list<int> list1(l1);

  list1.insert_many(++list1.begin(), 4, 5, 6);
  list1.insert_many_front(2, 1);
  list1.insert_many_back(9, 10);

  int i = 1;
  for (auto &x : list1) {
    EXPECT_EQ(x, i);
    i++;
  }
}
