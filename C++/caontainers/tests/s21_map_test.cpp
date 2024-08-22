//#include "../s21_map.h"

#include "s21_containers_test.h"

TEST(Map, Functions) {
  Map<int, double> Map1;
  EXPECT_EQ(Map1.size(), 0);

  Map<int, double> Map2{{10, 10.1},     {7, 7.1},  {2, 2.1},   {3, 3.1},
                        {101, 100.1},   {2, 2.1},  {99, 99.1}, {7, 7.1},
                        {1000, 1000.1}, {-2, -2.1}};
  EXPECT_EQ(Map2.size(), 8);
  EXPECT_EQ((*(Map2.begin())).first, -2);
  ASSERT_NEAR((*(Map2.begin())).second, -2.1, 0);

  Map<int, double> Map3(Map2);
  EXPECT_EQ(Map3.size(), 8);
  EXPECT_EQ((*(Map3.begin())).first, -2);
  ASSERT_NEAR((*(Map3.begin())).second, -2.1, 0);
  EXPECT_EQ((*(Map2.begin())).first, -2);
  ASSERT_NEAR((*(Map2.begin())).second, -2.1, 0);

  Map<int, double> Map4(std::move(Map3));
  EXPECT_EQ(Map3.size(), 0);
  EXPECT_EQ(Map4.size(), 8);
  EXPECT_EQ((*(Map4.begin())).first, -2);
  ASSERT_NEAR((*(Map4.begin())).second, -2.1, 0);

  Map<int, double> Map5{{10, 10.1},     {7, 7.1},  {2, 2.1},   {3, 3.1},
                        {101, 100.1},   {2, 2.1},  {99, 99.1}, {7, 7.1},
                        {1000, 1000.1}, {-2, -2.1}};
  Map5 = Map5;
  EXPECT_EQ((*(Map5.begin())).first, -2);
  ASSERT_NEAR((*(Map5.begin())).second, -2.1, 0);
  Map5 = std::move(Map5);
  EXPECT_EQ((*(Map5.begin())).first, -2);
  ASSERT_NEAR((*(Map5.begin())).second, -2.1, 0);

  Map<int, double> Map6{{3, 3.1}, {5, 5.1}, {9, 9.1}};
  Map6 = Map5;
  EXPECT_EQ(Map5.size(), 8);
  EXPECT_EQ(Map6.size(), 8);
  EXPECT_EQ((*(Map5.begin())).first, -2);
  ASSERT_NEAR((*(Map5.begin())).second, -2.1, 0);
  EXPECT_EQ((*(Map6.begin())).first, -2);
  ASSERT_NEAR((*(Map6.begin())).second, -2.1, 0);
  Map6 = std::move(Map5);
  EXPECT_EQ(Map5.size(), 0);
  EXPECT_EQ(Map6.size(), 8);
  EXPECT_EQ((*(Map6.begin())).first, -2);
  ASSERT_NEAR((*(Map6.begin())).second, -2.1, 0);

  Map<int, double> Map7 = Map6;
  EXPECT_EQ(Map6.size(), 8);
  EXPECT_EQ(Map7.size(), 8);
  EXPECT_EQ((*(Map6.begin())).first, -2);
  ASSERT_NEAR((*(Map6.begin())).second, -2.1, 0);
  EXPECT_EQ((*(Map7.begin())).first, -2);
  ASSERT_NEAR((*(Map7.begin())).second, -2.1, 0);

  Map<int, double> Map8 = std::move(Map7);
  EXPECT_EQ(Map7.size(), 0);
  EXPECT_EQ(Map8.size(), 8);
  EXPECT_EQ((*(Map8.begin())).first, -2);
  ASSERT_NEAR((*(Map8.begin())).second, -2.1, 0);
  Map<int, double>::iterator it;
  it = it;
}

TEST(Map, Iterators) {
  Map<int, double> Map1{{10, 10.1},     {7, 7.1},  {2, 2.1},   {3, 3.1},
                        {101, 101.1},   {2, 2.1},  {99, 99.1}, {7, 7.1},
                        {1000, 1000.1}, {-2, -2.1}};
  EXPECT_EQ((*(Map1.begin())).first, -2);
  ASSERT_NEAR((*(Map1.begin())).second, -2.1, 0);
  EXPECT_EQ((*(Map1.end())).first, 0);
  ASSERT_NEAR((*(Map1.end())).second, 0, 0);
  EXPECT_EQ((*(--(Map1.end()))).first, 1000);
  ASSERT_NEAR((*(--(Map1.end()))).second, 1000.1, 0);
  auto it = --(Map1.end());
  --it;
  EXPECT_EQ((*it).first, 101);
  ASSERT_NEAR((*it).second, 101.1, 0);
  --it;
  EXPECT_EQ((*it).first, 99);
  ASSERT_NEAR((*it).second, 99.1, 0);
  --it;
  EXPECT_EQ((*it).first, 10);
  ASSERT_NEAR((*it).second, 10.1, 0);
  --it;
  EXPECT_EQ((*it).first, 7);
  ASSERT_NEAR((*it).second, 7.1, 0);

  auto it1 = Map1.begin();
  EXPECT_EQ((*it1).first, -2);
  ASSERT_NEAR((*it1).second, -2.1, 0);
  ++it1;
  EXPECT_EQ((*it1).first, 2);
  ASSERT_NEAR((*it1).second, 2.1, 0);
  ++it1;
  EXPECT_EQ((*it1).first, 3);
  ASSERT_NEAR((*it1).second, 3.1, 0);
  ++it1;
  EXPECT_EQ((*it1).first, 7);
  ASSERT_NEAR((*it1).second, 7.1, 0);
  ++it1;
  EXPECT_EQ((*it1).first, 10);
  ASSERT_NEAR((*it1).second, 10.1, 0);

  EXPECT_EQ(Map1.begin() == Map1.end(), 0);
  EXPECT_EQ(Map1.begin() != Map1.end(), 1);

  it1 = Map1.begin();
  EXPECT_EQ(it1 == Map1.begin(), 1);

  Map<int, double> Map2;
  EXPECT_EQ(Map2.begin() == Map2.end(), 1);
}

TEST(Map, Element_access) {
  Map<int, double> Map1{{10, 10.1},     {7, 7.1},  {2, 2.1},   {3, 3.1},
                        {101, 101.1},   {2, 2.1},  {99, 99.1}, {7, 7.1},
                        {1000, 1000.1}, {-2, -2.1}};
  ASSERT_NEAR(Map1.at(101), 101.1, 0);
  Map1.at(101) = 102.1;
  ASSERT_NEAR(Map1.at(101), 102.1, 0);
  EXPECT_THROW(Map1.at(102), std::out_of_range);
  Map<int, double> Map2;
  EXPECT_THROW(Map2.at(101), std::out_of_range);

  ASSERT_NEAR(Map1[101], 102.1, 0);
  Map1[101] = 103.1;
  ASSERT_NEAR(Map1[101], 103.1, 0);
  Map1[100] = 100.1;
  ASSERT_NEAR(Map1[100], 100.1, 0);
}

TEST(Map, Capacity) {
  Map<int, double> Map1{{10, 10.1},     {7, 7.1},  {2, 2.1},   {3, 3.1},
                        {101, 101.1},   {2, 2.1},  {99, 99.1}, {7, 7.1},
                        {1000, 1000.1}, {-2, -2.1}};
  EXPECT_EQ(Map1.size(), 8);
  EXPECT_EQ(Map1.empty(), false);

  Map<int, double> Map2;
  EXPECT_EQ(Map2.empty(), true);

  EXPECT_EQ(Map1.max_size() > 0, 1);
}

TEST(Map, Modifiers1) {
  Map<int, double> Map1{{10, 10.1},   {7, 7.1},       {2, 2.1},   {3, 3.1},
                        {101, 101.1}, {2, 2.1},       {99, 99.1}, {97, 97.1},
                        {7, 7.1},     {1000, 1000.1}, {-2, -2.1}};
  Map1.clear();
  EXPECT_EQ(Map1.size(), 0);

  Map<int, double> Map2;
  Map2.erase(Map2.begin());
  Map2.erase(Map2.end());

  Map<int, double> Map3{{10, 10.1},   {7, 7.1},       {2, 2.1},   {3, 3.1},
                        {101, 101.1}, {2, 2.1},       {99, 99.1}, {97, 97.1},
                        {7, 7.1},     {1000, 1000.1}, {-2, -2.1}};
  auto it = Map3.begin();
  EXPECT_EQ((*(Map3.erase(it))).first, 2);
  EXPECT_EQ(Map3.size(), 8);

  Map<int, double> Map4{{10, 10.1},   {7, 7.1},       {2, 2.1},   {3, 3.1},
                        {101, 101.1}, {2, 2.1},       {99, 99.1}, {97, 97.1},
                        {7, 7.1},     {1000, 1000.1}, {-2, -2.1}};
  it = Map4.begin();
  ++it;
  EXPECT_EQ((*(Map4.erase(it))).first, 3);
  EXPECT_EQ(Map4.size(), 8);

  Map<int, double> Map5{{10, 10.1},   {7, 7.1},       {2, 2.1},   {3, 3.1},
                        {101, 101.1}, {2, 2.1},       {99, 99.1}, {97, 97.1},
                        {7, 7.1},     {1000, 1000.1}, {-2, -2.1}};
  it = Map5.begin();
  ++it;
  ++it;
  EXPECT_EQ((*(Map5.erase(it))).first, 7);
  EXPECT_EQ(Map5.size(), 8);

  Map<int, double> Map6{{10, 10.1},   {7, 7.1},       {2, 2.1},   {3, 3.1},
                        {101, 101.1}, {2, 2.1},       {99, 99.1}, {97, 97.1},
                        {7, 7.1},     {1000, 1000.1}, {-2, -2.1}};
  it = Map6.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ((*(Map6.erase(it))).first, 10);
  EXPECT_EQ(Map6.size(), 8);

  Map<int, double> Map7{{10, 10.1},   {7, 7.1},       {2, 2.1},   {3, 3.1},
                        {101, 101.1}, {2, 2.1},       {99, 99.1}, {97, 97.1},
                        {7, 7.1},     {1000, 1000.1}, {-2, -2.1}};
  it = Map7.begin();
  ++it;
  ++it;
  ++it;
  ++it;
  EXPECT_EQ((*(Map7.erase(it))).first, 97);
  EXPECT_EQ(Map7.size(), 8);

  Map<int, double> Map70{{10, 10.1},   {7, 7.1},       {2, 2.1},   {3, 3.1},
                         {101, 101.1}, {2, 2.1},       {99, 99.1}, {97, 97.1},
                         {7, 7.1},     {1000, 1000.1}, {-2, -2.1}};
  it = Map70.begin();
  ++it;
  ++it;
  ++it;
  ++it;
  ++it;
  EXPECT_EQ((*(Map70.erase(it))).first, 99);
  EXPECT_EQ(Map70.size(), 8);

  Map<int, double> Map71{{10, 10.1}, {1, 1.1}, {3, 3.1}, {8, 8.1}};
  it = Map71.begin();
  ++it;
  EXPECT_EQ((*(Map71.erase(it))).first, 8);
  EXPECT_EQ(Map71.size(), 3);

  Map<int, double> Map72{{10, 10.1}, {1, 1.1}, {3, 3.1}, {2, 2.1}};
  it = Map72.begin();
  ++it;
  ++it;
  EXPECT_EQ((*(Map72.erase(it))).first, 10);
  EXPECT_EQ(Map72.size(), 3);

  Map<int, double> Map8{{10, 10.1},     {7, 7.1},  {2, 2.1},   {3, 3.1},
                        {101, 101.1},   {2, 2.1},  {99, 99.1}, {7, 7.1},
                        {1000, 1000.1}, {-2, -2.1}};
  Map<int, double> Map9{{4, 4.101}, {1002, 1002.1}, {1, 1.1},
                        {2, 2.1},   {101, 100.1},   {999, 999.1}};
  Map8.swap(Map9);
  EXPECT_EQ(Map8.size(), 6);
  EXPECT_EQ(Map9.size(), 8);
  EXPECT_EQ((*Map8.begin()).first, 1);
  EXPECT_EQ((*Map9.begin()).first, -2);

  Map<int, double> Map10{{10, 10.1},     {7, 7.1},  {2, 2.1},   {3, 3.1},
                         {101, 101.1},   {2, 2.1},  {99, 99.1}, {7, 7.1},
                         {1000, 1000.1}, {-2, -2.1}};
  Map<int, double> Map11{{4, 4.101}, {1002, 1002.1}, {1, 1.1},
                         {2, 2.1},   {101, 100.1},   {999, 999.1}};
  Map10.merge(Map11);
  EXPECT_EQ(Map10.size(), 12);
  EXPECT_EQ(Map11.size(), 2);
  EXPECT_EQ((*Map10.begin()).first, -2);
  EXPECT_EQ((*Map11.begin()).first, 2);

  Map<int, double> Map12{{4, 4.101}, {1002, 1002.1}, {1, 1.1},
                         {2, 2.1},   {101, 101.1},   {999, 999.1}};
  std::pair<Map<int, double>::iterator, bool> pair_1 =
      Map12.insert({101, 101.1});
  EXPECT_EQ(Map12.size(), 6);
  EXPECT_EQ((*(pair_1.first)).first, 101);
  EXPECT_EQ(pair_1.second, 0);

  pair_1 = Map12.insert({102, 102.1});
  EXPECT_EQ(Map12.size(), 7);
  EXPECT_EQ((*(pair_1.first)).first, 102);
  EXPECT_EQ(pair_1.second, 1);

  pair_1 = Map12.insert(103, 103.1);
  EXPECT_EQ(Map12.size(), 8);
  EXPECT_EQ((*(pair_1.first)).first, 103);
  EXPECT_EQ(pair_1.second, 1);

  pair_1 = Map12.insert(103, 103.1);
  EXPECT_EQ(Map12.size(), 8);
  EXPECT_EQ((*(pair_1.first)).first, 103);
  EXPECT_EQ(pair_1.second, 0);

  pair_1 = Map12.insert_or_assign(103, 104.1);
  EXPECT_EQ(Map12.size(), 8);
  EXPECT_EQ((*(pair_1.first)).first, 103);
  ASSERT_NEAR((*(pair_1.first)).second, 104.1, 0);
  EXPECT_EQ(pair_1.second, 1);

  pair_1 = Map12.insert_or_assign(103, 104.1);
  EXPECT_EQ(Map12.size(), 8);
  EXPECT_EQ((*(pair_1.first)).first, 103);
  ASSERT_NEAR((*(pair_1.first)).second, 104.1, 0);
  EXPECT_EQ(pair_1.second, 0);

  pair_1 = Map12.insert_or_assign(104, 104.1);
  EXPECT_EQ(Map12.size(), 9);
  EXPECT_EQ((*(pair_1.first)).first, 104);
  ASSERT_NEAR((*(pair_1.first)).second, 104.1, 0);
  EXPECT_EQ(pair_1.second, 1);
}

TEST(Map, Lookup) {
  Map<int, double> Map1{{4, 4.101}, {1002, 1002.1}, {1, 1.1},
                        {2, 2.1},   {101, 101.1},   {999, 999.1}};
  EXPECT_EQ(Map1.contains(4), 1);
  EXPECT_EQ(Map1.contains(5), 0);
}

TEST(Map, Modifiers12) {
  Vector<std::pair<Map<int, double>::iterator, bool>> tmp{};
  Map<int, double> Map1{{4, 4.1}, {1002, 1002.1}, {1, 1.1},
                        {2, 2.1}, {101, 101.1},   {999, 999.1}};
  std::pair<int, double> p1{11, 11.1};
  std::pair<int, double> p2{2, 2.1};
  std::pair<int, double> p3{12, 12.1};
  tmp = Map1.insert_many(p1, p2, p3);
  auto it = Map1.begin();
  EXPECT_EQ((*it).first, 1);
  ++it;
  EXPECT_EQ((*it).first, 2);
  ++it;
  EXPECT_EQ((*it).first, 4);
  ++it;
  EXPECT_EQ((*it).first, 11);
  ++it;
  EXPECT_EQ((*it).first, 12);
  ++it;
  EXPECT_EQ((*it).first, 101);
  EXPECT_EQ((*(tmp[0].first)).first, 11);
  EXPECT_EQ(tmp[0].second, 1);
  EXPECT_EQ((*(tmp[1].first)).first, 2);
  EXPECT_EQ(tmp[1].second, 0);
  EXPECT_EQ((*(tmp[2].first)).first, 12);
  EXPECT_EQ(tmp[2].second, 1);
}
