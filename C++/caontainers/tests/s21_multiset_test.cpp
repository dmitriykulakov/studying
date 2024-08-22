#include "s21_containers_test.h"

TEST(Multiset, Functions) {
  Multiset<int> Multiset1;
  EXPECT_EQ(Multiset1.size(), 0);

  Multiset<int> Multiset2{3, 1, 5, 7, 5, 9};
  EXPECT_EQ(Multiset2.size(), 6);
  EXPECT_EQ(*(Multiset2.begin()), 1);

  Multiset<int> Multiset3(Multiset2);
  EXPECT_EQ(Multiset3.size(), 6);
  EXPECT_EQ(*(Multiset3.begin()), 1);
  EXPECT_EQ(*(Multiset2.begin()), 1);
  EXPECT_EQ(Multiset2.size(), 6);

  Multiset<int> Multiset4(std::move(Multiset3));
  EXPECT_EQ(Multiset3.size(), 0);
  EXPECT_EQ(Multiset4.size(), 6);
  EXPECT_EQ(*(Multiset4.begin()), 1);

  Multiset<int> Multiset5{3, 1, 5, 7, 5, 9};
  Multiset5 = Multiset5;
  EXPECT_EQ(*(Multiset5.begin()), 1);
  Multiset5 = std::move(Multiset5);
  EXPECT_EQ(*(Multiset5.begin()), 1);

  Multiset<int> Multiset6{3, 5, 9};
  Multiset6 = Multiset5;
  EXPECT_EQ(Multiset5.size(), 6);
  EXPECT_EQ(Multiset6.size(), 6);
  EXPECT_EQ(*(Multiset6.begin()), 1);
  EXPECT_EQ(*(Multiset5.begin()), 1);
  Multiset6 = std::move(Multiset5);
  EXPECT_EQ(Multiset5.size(), 0);
  EXPECT_EQ(Multiset6.size(), 6);
  EXPECT_EQ(*(Multiset6.begin()), 1);

  Multiset<int> Multiset7 = Multiset6;
  EXPECT_EQ(Multiset7.size(), 6);
  EXPECT_EQ(*(Multiset7.begin()), 1);

  Multiset<int> Multiset8 = std::move(Multiset7);
  EXPECT_EQ(Multiset8.size(), 6);
  EXPECT_EQ(*(Multiset8.begin()), 1);
  Multiset<int>::iterator it;
  it = it;
}

TEST(Multiset, Iterators) {
  Multiset<int> Multiset1{10, 7, 2, 3, 101, 99, 97, 7, 1000, -2};
  EXPECT_EQ(*(Multiset1.begin()), -2);
  EXPECT_EQ(*(Multiset1.end()), 0);
  EXPECT_EQ(*(--(Multiset1.end())), 1000);
  auto it = --(Multiset1.end());
  --it;
  EXPECT_EQ(*it, 101);
  --it;
  EXPECT_EQ(*it, 99);
  --it;
  EXPECT_EQ(*it, 97);
  --it;
  EXPECT_EQ(*it, 10);
  --it;
  EXPECT_EQ(*it, 7);
  --it;
  EXPECT_EQ(*it, 7);
  --it;
  EXPECT_EQ(*it, 3);
  auto it1 = Multiset1.begin();
  EXPECT_EQ(*it1, -2);
  ++it1;
  EXPECT_EQ(*it1, 2);
  ++it1;
  EXPECT_EQ(*it1, 3);
  ++it1;
  EXPECT_EQ(*it1, 7);
  ++it1;
  EXPECT_EQ(*it1, 7);
  ++it1;
  EXPECT_EQ(*it1, 10);
  EXPECT_EQ(Multiset1.begin() == Multiset1.end(), 0);
  EXPECT_EQ(Multiset1.begin() != Multiset1.end(), 1);
}

TEST(Multiset, Capacity) {
  Multiset<int> Multiset1{10, 7, 2, 3, 101, 99, 97, 7, 1000, -2};
  EXPECT_EQ(Multiset1.size(), 10);
  EXPECT_EQ(Multiset1.empty(), false);

  Multiset<int> Multiset2;
  EXPECT_EQ(Multiset2.empty(), true);

  EXPECT_EQ(Multiset2.max_size() > 0, 1);
}

TEST(Multiset, Modifiers1) {
  Multiset<int> Multiset1{10, 7, 2, 3, 101, 99, 97, 7, 1000, -2};
  Multiset1.clear();
  EXPECT_EQ(Multiset1.size(), 0);

  Multiset<int> Multiset2;
  Multiset2.erase(Multiset2.begin());
  Multiset2.erase(Multiset2.end());

  Multiset<int> Multiset3{10, 7, 2, 3, 101, 99, 97, 7, 1000, -2};
  EXPECT_EQ(*(Multiset3.erase(Multiset3.begin())), 2);
  EXPECT_EQ(Multiset3.size(), 9);

  Multiset<int> Multiset4{10, 7, 2, 3, 101, 99, 97, 7, 1000, -2};
  auto it = Multiset4.begin();
  ++it;
  EXPECT_EQ(*(Multiset4.erase(it)), 3);
  EXPECT_EQ(Multiset4.size(), 9);

  Multiset<int> Multiset5{10, 7, 2, 3, 101, 99, 97, 7, 1000, -2};
  it = Multiset5.begin();
  ++it;
  ++it;
  EXPECT_EQ(*(Multiset5.erase(it)), 7);
  EXPECT_EQ(Multiset5.size(), 9);

  Multiset<int> Multiset6{10, 7, 2, 3, 101, 99, 97, 7, 1000, -2};
  it = Multiset6.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*(Multiset6.erase(it)), 7);
  EXPECT_EQ(Multiset6.size(), 9);

  Multiset<int> Multiset7{10, 7, 2, 3, 101, 99, 97, 7, 1000, -2};
  it = Multiset7.begin();
  ++it;
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*(Multiset7.erase(it)), 10);
  EXPECT_EQ(Multiset7.size(), 9);

  Multiset<int> Multiset70{10, 7, 2, 3, 101, 99, 97, 7, 1000, -2};
  it = Multiset70.begin();
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*(Multiset70.erase(it)), 97);
  EXPECT_EQ(Multiset70.size(), 9);

  Multiset<int> Multiset701{10, 7, 2, 3, 101, 99, 97, 7, 1000, -2};
  it = Multiset701.begin();
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*(Multiset701.erase(it)), 99);
  EXPECT_EQ(Multiset701.size(), 9);

  Multiset<int> Multiset702{10, 7, 2, 3, 101, 99, 97, 7, 1000, -2};
  it = Multiset702.begin();
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*(Multiset702.erase(it)), 101);
  EXPECT_EQ(Multiset702.size(), 9);

  Multiset<int> Multiset71{10, 0, 3, 8};
  it = Multiset71.begin();
  ++it;
  EXPECT_EQ(*(Multiset71.erase(it)), 8);
  EXPECT_EQ(Multiset71.size(), 3);

  Multiset<int> Multiset72{10, 1, 3, 2};
  it = Multiset72.begin();
  ++it;
  ++it;
  EXPECT_EQ(*(Multiset72.erase(it)), 10);
  EXPECT_EQ(Multiset72.size(), 3);

  Multiset<int> Multiset73{10, 1, 3, 2, 3};
  it = Multiset73.begin();
  ++it;
  ++it;
  EXPECT_EQ(*(Multiset73.erase(it)), 3);
  EXPECT_EQ(Multiset73.size(), 4);

  Multiset<int> Multiset8{10, 7, 2, 3, 101, 99, 97, 7, 1000, -2};
  Multiset<int> Multiset9{4, 1002, 0, 2, 101, 999};
  Multiset8.swap(Multiset9);
  EXPECT_EQ(Multiset8.size(), 6);
  EXPECT_EQ(Multiset9.size(), 10);
  EXPECT_EQ(*Multiset8.begin(), 0);
  EXPECT_EQ(*Multiset9.begin(), -2);

  Multiset<int> Multiset10{10, 7, 2, 3, 101, 99, 97, 7, 1000, -2};
  Multiset<int> Multiset11{4, 1002, 1, 2, 101, 999};

  Multiset10.merge(Multiset11);
  EXPECT_EQ(Multiset10.size(), 16);
  EXPECT_EQ(Multiset11.size(), 0);
  EXPECT_EQ(*Multiset10.begin(), -2);
  EXPECT_EQ(*Multiset11.begin(), 0);
}

TEST(Multiset, Lookup) {
  Multiset<int> Multiset1{4, 1002, 0, 2, 101, 2, 999};
  EXPECT_EQ(Multiset1.contains(4), 1);
  EXPECT_EQ(Multiset1.contains(5), 0);

  EXPECT_EQ(*Multiset1.find(2), 2);
  EXPECT_EQ(*Multiset1.find(1001), 0);

  EXPECT_EQ(Multiset1.count(1002), 1);
  EXPECT_EQ(Multiset1.count(2), 2);
  EXPECT_EQ(Multiset1.count(-2), 0);

  std::pair<Multiset<int>::iterator, Multiset<int>::iterator> m1 =
      Multiset1.equal_range(-2);
  EXPECT_EQ(*(m1.first), 0);
  EXPECT_EQ(*(m1.second), 0);
  m1 = Multiset1.equal_range(2);
  EXPECT_EQ(*(m1.first), 2);
  EXPECT_EQ(*(m1.second), 4);
  m1 = Multiset1.equal_range(1010);
  EXPECT_EQ(m1.first == Multiset1.end(), 1);
  EXPECT_EQ(m1.second == Multiset1.end(), 1);

  EXPECT_EQ(*(Multiset1.lower_bound(-2)), 0);
  EXPECT_EQ(*(Multiset1.lower_bound(101)), 101);
  EXPECT_EQ(Multiset1.lower_bound(1010) == Multiset1.end(), 1);

  EXPECT_EQ(*(Multiset1.upper_bound(-2)), 0);
  EXPECT_EQ(*(Multiset1.upper_bound(101)), 999);
  EXPECT_EQ(Multiset1.upper_bound(1010) == Multiset1.end(), 1);
}

TEST(Multiset, Modifiers12) {
  Vector<std::pair<Multiset<int>::iterator, bool>> tmp{};
  Multiset<int> Multiset1{4, 1002, 0, 2, 101, 999};
  tmp = Multiset1.insert_many(11, 2, 12);
  auto it = Multiset1.begin();
  EXPECT_EQ(*it, 0);
  ++it;
  EXPECT_EQ(*it, 2);
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
  EXPECT_EQ(tmp[1].second, 1);
  EXPECT_EQ(*(tmp[2].first), 12);
  EXPECT_EQ(tmp[2].second, 1);
}