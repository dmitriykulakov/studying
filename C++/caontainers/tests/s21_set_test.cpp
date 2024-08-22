//#include "../s21_set.h"

#include "s21_containers_test.h"

TEST(Set, Functions) {
  Set<int> Set1;
  EXPECT_EQ(Set1.size(), 0);

  Set<int> Set2{3, 1, 5, 7, 5, 9};
  EXPECT_EQ(Set2.size(), 5);
  EXPECT_EQ(*(Set2.begin()), 1);

  Set<int> Set3(Set2);
  EXPECT_EQ(Set3.size(), 5);
  EXPECT_EQ(*(Set3.begin()), 1);
  EXPECT_EQ(*(Set2.begin()), 1);
  EXPECT_EQ(Set2.size(), 5);

  Set<int> Set4(std::move(Set3));
  EXPECT_EQ(Set3.size(), 0);
  EXPECT_EQ(Set4.size(), 5);
  EXPECT_EQ(*(Set4.begin()), 1);

  Set<int> Set5{3, 1, 5, 7, 5, 9};
  Set5 = Set5;
  EXPECT_EQ(*(Set5.begin()), 1);
  Set5 = std::move(Set5);
  EXPECT_EQ(*(Set5.begin()), 1);

  Set<int> Set6{3, 5, 9};
  Set6 = Set5;
  EXPECT_EQ(Set5.size(), 5);
  EXPECT_EQ(Set6.size(), 5);
  EXPECT_EQ(*(Set6.begin()), 1);
  EXPECT_EQ(*(Set5.begin()), 1);
  Set6 = std::move(Set5);
  EXPECT_EQ(Set5.size(), 0);
  EXPECT_EQ(Set6.size(), 5);
  EXPECT_EQ(*(Set6.begin()), 1);

  Set<int> Set7 = Set6;
  EXPECT_EQ(Set7.size(), 5);
  EXPECT_EQ(*(Set7.begin()), 1);

  Set<int> Set8 = std::move(Set7);
  EXPECT_EQ(Set8.size(), 5);
  EXPECT_EQ(*(Set8.begin()), 1);
  Set<int>::iterator it;
  it = it;
}

TEST(Set, Iterators) {
  Set<int> Set1{10, 7, 2, 3, 101, 99, 97, 7, 1000, -2};
  EXPECT_EQ(*(Set1.begin()), -2);
  EXPECT_EQ(*(Set1.end()), 0);
  EXPECT_EQ(*(--(Set1.end())), 1000);
  auto it = --(Set1.end());
  --it;
  EXPECT_EQ(*it, 101);
  --it;
  EXPECT_EQ(*it, 99);
  --it;
  EXPECT_EQ(*it, 97);
  --it;
  EXPECT_EQ(*it, 10);
  auto it1 = Set1.begin();
  EXPECT_EQ(*it1, -2);
  ++it1;
  EXPECT_EQ(*it1, 2);
  ++it1;
  EXPECT_EQ(*it1, 3);
  ++it1;
  EXPECT_EQ(*it1, 7);
  ++it1;
  EXPECT_EQ(*it1, 10);
  EXPECT_EQ(Set1.begin() == Set1.end(), 0);
  EXPECT_EQ(Set1.begin() != Set1.end(), 1);
}

TEST(Set, Capacity) {
  Set<int> Set1{10, 7, 2, 3, 101, 99, 97, 7, 1000, -2};
  EXPECT_EQ(Set1.size(), 9);
  EXPECT_EQ(Set1.empty(), false);

  Set<int> Set2;
  EXPECT_EQ(Set2.empty(), true);

  EXPECT_EQ(Set2.max_size() > 0, 1);
}

TEST(Set, Modifiers1) {
  Set<int> Set1{10, 7, 2, 3, 101, 99, 97, 7, 1000, -2};
  Set1.clear();
  EXPECT_EQ(Set1.size(), 0);

  Set<int> Set2;
  Set2.erase(Set2.begin());
  Set2.erase(Set2.end());

  Set<int> Set3{10, 7, 2, 3, 101, 99, 97, 7, 1000, -2};
  EXPECT_EQ(*(Set3.erase(Set3.begin())), 2);
  EXPECT_EQ(Set3.size(), 8);

  Set<int> Set4{10, 7, 2, 3, 101, 99, 97, 7, 1000, -2};
  auto it = Set4.begin();
  ++it;
  EXPECT_EQ(*(Set4.erase(it)), 3);
  EXPECT_EQ(Set4.size(), 8);

  Set<int> Set5{10, 7, 2, 3, 101, 99, 97, 7, 1000, -2};
  it = Set5.begin();
  ++it;
  ++it;
  EXPECT_EQ(*(Set5.erase(it)), 7);
  EXPECT_EQ(Set5.size(), 8);

  Set<int> Set6{10, 7, 2, 3, 101, 99, 97, 7, 1000, -2};
  it = Set6.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*(Set6.erase(it)), 10);
  EXPECT_EQ(Set6.size(), 8);

  Set<int> Set7{10, 7, 2, 3, 101, 99, 97, 7, 1000, -2};
  it = Set7.begin();
  ++it;
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*(Set7.erase(it)), 97);
  EXPECT_EQ(Set7.size(), 8);

  Set<int> Set71{10, 0, 3, 8};
  it = Set71.begin();
  ++it;
  EXPECT_EQ(*(Set71.erase(it)), 8);
  EXPECT_EQ(Set71.size(), 3);

  Set<int> Set72{10, 1, 3, 2};
  it = Set72.begin();
  ++it;
  ++it;
  EXPECT_EQ(*(Set72.erase(it)), 10);
  EXPECT_EQ(Set72.size(), 3);

  Set<int> Set8{10, 7, 2, 3, 101, 99, 97, 7, 1000, -2};
  Set<int> Set9{4, 1002, 0, 2, 101, 999};
  Set8.swap(Set9);
  EXPECT_EQ(Set8.size(), 6);
  EXPECT_EQ(Set9.size(), 9);
  EXPECT_EQ(*Set8.begin(), 0);
  EXPECT_EQ(*Set9.begin(), -2);

  Set<int> Set10{10, 7, 2, 3, 101, 99, 97, 7, 1000, -2};
  Set<int> Set11{4, 1002, 0, 2, 101, 999};
  Set10.merge(Set11);
  EXPECT_EQ(Set10.size(), 13);
  EXPECT_EQ(Set11.size(), 2);
  EXPECT_EQ(*Set10.begin(), -2);
  EXPECT_EQ(*Set11.begin(), 2);
}

TEST(Set, Lookup) {
  Set<int> Set1{4, 1002, 0, 2, 101, 999};
  EXPECT_EQ(Set1.contains(4), 1);
  EXPECT_EQ(Set1.contains(5), 0);

  EXPECT_EQ(*Set1.find(2), 2);
  EXPECT_EQ(*Set1.find(1001), 0);
}

TEST(Set, Modifiers12) {
  Vector<std::pair<Set<int>::iterator, bool>> tmp{};
  Set<int> Set1{4, 1002, 0, 2, 101, 999};
  tmp = Set1.insert_many(11, 2, 12);
  auto it = Set1.begin();
  EXPECT_EQ(*it, 0);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 11);
  ++it;
  EXPECT_EQ(*it, 12);
  ++it;
  EXPECT_EQ(*it, 101);
  EXPECT_EQ(*(tmp[0].first), 11);
  EXPECT_EQ(tmp[0].second, 1);
  EXPECT_EQ(*(tmp[1].first), 2);
  EXPECT_EQ(tmp[1].second, 0);
  EXPECT_EQ(*(tmp[2].first), 12);
  EXPECT_EQ(tmp[2].second, 1);
}