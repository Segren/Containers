#include <set>

#include "test_runner.h"

TEST(Set, Constructor_Default) {
  s21::set<int> s21_set;
  std::set<int> std_set;
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(Set, Constructor_Initializer_list) {
  s21::set<int> s21_set = {1, 2, 3, 4};
  std::set<int> std_set = {1, 2, 3, 4};
  EXPECT_EQ(s21_set.size(), std_set.size());
  EXPECT_EQ(s21_set.empty(), std_set.empty());
}

TEST(Set, Constructor_Copy) {
  s21::set<char> s21_set_1 = {'a', 'b', 'c', 'd', 'a', 'b', 'f'};
  std::set<char> std_set_1 = {'a', 'b', 'c', 'd', 'a', 'b', 'f'};
  auto it1 = s21_set_1.begin();
  auto it2 = s21_set_1.begin();

  while (it1 != s21_set_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(Set, Constructor_Move) {
  s21::set<char> s21_set_1 = {'a', 'b', 'c', 'd'};
  std::set<char> std_set_1 = {'a', 'b', 'c', 'd'};
  s21::set<char> s21_set_2 = std::move(s21_set_1);
  std::set<char> std_set_2 = std::move(std_set_1);

  EXPECT_EQ(s21_set_2.size(), std_set_2.size());
  EXPECT_EQ(s21_set_1.size(), std_set_1.size());
  EXPECT_EQ(s21_set_1.empty(), std_set_1.empty());
  auto it1 = s21_set_2.begin();
  auto it2 = std_set_2.begin();
  while (it1 != s21_set_2.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(Set, Modifier_Insert_1) {
  s21::set<char> s21_set_1 = {'a', 'c', 'd'};
  s21::set<char> s21_set_2 = {'a', 'c', 'd', 'b'};

  auto it = s21_set_1.begin();
  ++it;
  s21_set_1.insert('b');
  s21_set_1.insert('a');
  auto it1 = s21_set_1.begin();
  auto it2 = s21_set_2.begin();
  while (it1 != s21_set_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_set_1.size(), s21_set_2.size());
}

TEST(Set, Modifier_Insert_2) {
  s21::set<char> s21_set;

  s21_set.insert('b');
  s21_set.insert('b');
  s21_set.insert('b');

  EXPECT_EQ(s21_set.size(), size_t(1));
}

TEST(Set, Modifier_Insert_3) {
  s21::set<float> s21_set;
  std::set<float> std_set;

  s21_set.insert(0.0000000000000000000000000000000000000000001);
  s21_set.insert(0.000000000000000000000000000000000000000000099);
  std_set.insert(0.0000000000000000000000000000000000000000001);
  std_set.insert(0.000000000000000000000000000000000000000000099);

  EXPECT_EQ(s21_set.size(), std_set.size());
}

TEST(Set, Modifier_Erase) {
  s21::set<char> s21_set_1 = {'a', 'c', 'd'};
  s21::set<char> s21_set_2 = {'a', 'b', 'c', 'd'};

  auto it = s21_set_2.begin();
  ++it;
  s21_set_2.erase(it);
  auto it1 = s21_set_1.begin();
  auto it2 = s21_set_2.begin();
  while (it1 != s21_set_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(s21_set_1.size(), s21_set_2.size());
}

TEST(Set, Modifier_Swap) {
  s21::set<char> s21_set_1 = {'a', 'b', 'o', 'b', 'a'};
  s21::set<char> s21_set_2 = {'s', 'h', 'l', 'e', 'p', 'p', 'a'};
  s21::set<char> s21_set_3 = {'a', 'b', 'o', 'b', 'a'};
  s21::set<char> s21_set_4 = {'s', 'h', 'l', 'e', 'p', 'p', 'a'};
  s21_set_1.swap(s21_set_2);
  auto it1 = s21_set_1.begin();
  auto it2 = s21_set_2.begin();
  auto it3 = s21_set_3.begin();
  auto it4 = s21_set_4.begin();
  while (it1 != s21_set_1.end()) {
    EXPECT_EQ(*it1, *it4);
    ++it1, ++it4;
  }
  while (it2 != s21_set_2.end()) {
    EXPECT_EQ(*it2, *it3);
    ++it2, ++it3;
  }
  EXPECT_EQ(s21_set_1.size(), s21_set_4.size());
  EXPECT_EQ(s21_set_2.size(), s21_set_3.size());
}

TEST(Set, Modifier_Merge) {
  s21::set<int> s21_set_1 = {1, 2, 3};
  s21::set<int> s21_set_2 = {3, 4, 5, 6};
  s21::set<int> s21_set_3 = {1, 2, 3, 4, 5, 6};
  s21_set_1.merge(s21_set_2);
  auto it1 = s21_set_1.begin();
  auto it3 = s21_set_3.begin();
  while (it1 != s21_set_1.end()) {
    EXPECT_EQ(*it1, *it3);
    ++it1, ++it3;
  }
  EXPECT_EQ(s21_set_1.size(), s21_set_3.size());
}

TEST(Set, Lookup_Contains) {
  s21::set<int> s21_set;
  s21_set.insert(1);
  s21_set.insert(2);
  s21_set.insert(3);
  s21_set.insert(4);
  EXPECT_EQ(s21_set.contains(1), true);
  EXPECT_EQ(s21_set.contains(2), true);
  EXPECT_EQ(s21_set.contains(3), true);
  EXPECT_EQ(s21_set.contains(4), true);
  EXPECT_EQ(s21_set.contains(7), false);
  EXPECT_EQ(s21_set.contains(-2), false);
  EXPECT_EQ(s21_set.contains(0), false);
}

TEST(set, ConstructorDefaultSet) {
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
}

TEST(set, ConstructorInitializerSet) {
  s21::set<char> my_set = {'x', 'b', 'z', 'y'};
  std::set<char> orig_set = {'x', 'b', 'z', 'y'};
  EXPECT_EQ(my_set.size(), orig_set.size());
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, ConstructorInitializer2Set) {
  s21::set<char> my_set = {};
  std::set<char> orig_set = {};
  EXPECT_EQ(my_set.size(), orig_set.size());
}

TEST(set, ConstructorCopySet) {
  s21::set<int> my_set = {1, 2, 3, 4, 5};
  std::set<int> orig_set = {1, 2, 3, 4, 5};
  s21::set<int> my_set_copy = my_set;
  std::set<int> orig_set_copy = orig_set;
  EXPECT_EQ(my_set_copy.size(), orig_set_copy.size());
  auto my_it = my_set_copy.begin();
  auto orig_it = orig_set_copy.begin();
  for (; my_it != my_set_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, ConstructorMoveSet) {
  s21::set<int> my_set = {1, 2, 3, 4, 5};
  std::set<int> orig_set = {1, 2, 3, 4, 5};
  s21::set<int> my_set_copy = std::move(my_set);
  std::set<int> orig_set_copy = std::move(orig_set);
  EXPECT_EQ(my_set.size(), orig_set.size());
  EXPECT_EQ(my_set_copy.size(), orig_set_copy.size());
  auto my_it = my_set_copy.begin();
  auto orig_it = orig_set_copy.begin();
  for (; my_it != my_set_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, SetIteratorsSet) {
  s21::set<std::string> my_set = {"This", "is", "my", "set"};
  std::set<std::string> orig_set = {"This", "is", "my", "set"};
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  EXPECT_TRUE(*orig_it == *my_it);
  my_it = my_set.end();
  orig_it = orig_set.end();
  --my_it;
  --orig_it;
  EXPECT_TRUE(*orig_it == *my_it);
}

TEST(set, CapacitySet) {
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.insert('b');
  orig_empty_set.insert('c');
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST(set, ClearSet) {
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  my_empty_set.clear();
  orig_empty_set.clear();
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.insert('a');
  orig_empty_set.insert('b');
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.clear();
  orig_empty_set.clear();
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST(set, InsertSet) {
  s21::set<std::string> my_set = {"This", "is", "my", "set"};
  std::set<std::string> orig_set = {"This", "is", "my", "set"};
  auto my_pr = my_set.insert("best");
  auto orig_pr = orig_set.insert("best");
  EXPECT_TRUE(my_pr.second == orig_pr.second);
  EXPECT_TRUE(*my_pr.first == *orig_pr.first);
  my_pr = my_set.insert("is");
  orig_pr = orig_set.insert("is");
  EXPECT_TRUE(my_pr.second == orig_pr.second);
  EXPECT_TRUE(*my_pr.first == *orig_pr.first);
}

TEST(set, EraseSet) {
  s21::set<int> my_set = {5, 4, 3, 2, 7, 8, 9};
  std::set<int> orig_set = {5, 4, 3, 2, 7, 8, 9};
  auto size = my_set.size();
  my_set.erase(my_set.end());
  auto new_size = my_set.size();
  EXPECT_EQ(size, new_size);
  my_set.erase(my_set.begin());
  orig_set.erase(orig_set.begin());
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, SwapSet) {
  s21::set<int> my_set = {1};
  s21::set<int> my_swap_set = {3, 4, 5};

  my_set.swap(my_swap_set);
  EXPECT_EQ(my_set.size(), 3UL);
  EXPECT_EQ(my_swap_set.size(), 1UL);
  EXPECT_EQ(*my_set.begin(), 3);
  EXPECT_EQ(*my_swap_set.begin(), 1);
}

TEST(set, MergeSet) {
  s21::set<int> my_set = {1};
  s21::set<int> my_merge_set = {3, 4, 5};
  my_set.merge(my_merge_set);

  std::set<int> orig_set = {1};
  std::set<int> orig_merge_set = {3, 4, 5};
  orig_set.merge(orig_merge_set);
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
  EXPECT_EQ(orig_set.size(), my_set.size());
  EXPECT_EQ(my_merge_set.size(), orig_merge_set.size());
}

TEST(set, FindSet) {
  s21::set<double> my_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  s21::set<double> orig_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  auto my_it = my_set.find(2.4);
  auto orig_it = orig_set.find(2.4);
  EXPECT_TRUE(*orig_it == *my_it);
}

TEST(set, ContainsSet) {
  s21::set<double> my_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  s21::set<double> orig_set = {2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  EXPECT_EQ(my_set.contains(2), orig_set.contains(2));
  EXPECT_EQ(my_set.contains(2.1), orig_set.contains(2.1));
}

TEST(set_constructor, case1) {
  s21::set<int> s21_set_int;
  s21::set<double> s21_set_double;
  s21::set<std::string> s21_set_string;

  EXPECT_EQ(s21_set_int.size(), 0U);
  EXPECT_EQ(s21_set_double.size(), 0U);
  EXPECT_EQ(s21_set_string.size(), 0U);
}

TEST(set_constructor, case2) {
  s21::set<int> s21_set_int{1, 2, 3, 4, 5};
  s21::set<double> s21_set_double{1.30359, 2847.4925, 923.39281};
  s21::set<std::string> s21_set_string{"Hello", ",", "world", "!"};

  EXPECT_EQ(s21_set_int.size(), 5U);
  EXPECT_EQ(s21_set_double.size(), 3U);
  EXPECT_EQ(s21_set_string.size(), 4U);
}

TEST(set_constructor, case3) {
  s21::set<int> s21_set_ref_int{1, 2, 3, 4, 5};
  s21::set<int> s21_set_res_int{s21_set_ref_int};

  s21::set<double> s21_set_ref_double{1.30359, 2847.4925, 923.39281};
  s21::set<double> s21_set_res_double{s21_set_ref_double};

  s21::set<std::string> s21_set_ref_string{"Hello", ",", "world", "!"};
  s21::set<std::string> s21_set_res_string{s21_set_ref_string};

  EXPECT_EQ(s21_set_ref_int.size(), s21_set_res_int.size());
  EXPECT_EQ(s21_set_ref_double.size(), s21_set_res_double.size());
  EXPECT_EQ(s21_set_ref_string.size(), s21_set_res_string.size());
}

TEST(set_constructor, case4) {
  s21::set<int> s21_set_ref_int{1, 2, 3, 4, 5};
  s21::set<int> s21_set_res_int = std::move(s21_set_ref_int);

  s21::set<double> s21_set_ref_double{1.30359, 2847.4925, 923.39281};
  s21::set<double> s21_set_res_double = std::move(s21_set_ref_double);

  s21::set<std::string> s21_set_ref_string{"Hello", ",", "world", "!"};
  s21::set<std::string> s21_set_res_string = std::move(s21_set_ref_string);

  EXPECT_EQ(s21_set_ref_int.size(), 0U);
  EXPECT_EQ(s21_set_res_int.size(), 5U);

  EXPECT_EQ(s21_set_ref_double.size(), 0U);
  EXPECT_EQ(s21_set_res_double.size(), 3U);

  EXPECT_EQ(s21_set_ref_string.size(), 0U);
  EXPECT_EQ(s21_set_res_string.size(), 4U);
}

TEST(set_constructor, case5) {
  s21::set<int> s21_set_ref_int{1, 2, 3, 4, 5};
  s21::set<int> s21_set_res_int;
  s21_set_res_int = std::move(s21_set_ref_int);

  s21::set<double> s21_set_ref_double{1.30359, 2847.4925, 923.39281};
  s21::set<double> s21_set_res_double;
  s21_set_res_double = std::move(s21_set_ref_double);

  s21::set<std::string> s21_set_ref_string{"Hello", ",", "world", "!"};
  s21::set<std::string> s21_set_res_string;
  s21_set_res_string = std::move(s21_set_ref_string);

  EXPECT_EQ(s21_set_ref_int.size(), 0U);
  EXPECT_EQ(s21_set_res_int.size(), 5U);

  EXPECT_EQ(s21_set_ref_double.size(), 0U);
  EXPECT_EQ(s21_set_res_double.size(), 3U);

  EXPECT_EQ(s21_set_ref_string.size(), 0U);
  EXPECT_EQ(s21_set_res_string.size(), 4U);
}

TEST(set_constructor, case7) {
  s21::set<int> s21_set_ref_int{1, 2, 3, 4};
  s21::set<int> s21_set_res_int{s21_set_ref_int};

  s21::set<double> s21_set_ref_double{1.30359, 2847.4925, 923.39281, 1.23};
  s21::set<double> s21_set_res_double{s21_set_ref_double};

  s21::set<std::string> s21_set_ref_string{"Hello", ",", "world", "!"};
  s21::set<std::string> s21_set_res_string{s21_set_ref_string};

  auto it_res_int = s21_set_res_int.begin();
  for (auto it_ref_int = s21_set_ref_int.begin();
       it_ref_int != s21_set_ref_int.end(); ++it_ref_int) {
    EXPECT_EQ(*it_res_int, *it_ref_int);
    it_res_int++;
  }

  auto it_res_double = s21_set_res_double.begin();
  for (auto it_ref_double = s21_set_ref_double.begin();
       it_ref_double != s21_set_ref_double.end(); ++it_ref_double) {
    EXPECT_EQ(*it_res_double, *it_ref_double);
    it_res_double++;
  }

  auto it_res_string = s21_set_res_string.begin();
  for (auto it_ref_string = s21_set_ref_string.begin();
       it_ref_string != s21_set_ref_string.end(); ++it_ref_string) {
    EXPECT_EQ(*it_res_string, *it_ref_string);
    it_res_string++;
  }
}

TEST(set_insert, case1) {
  s21::set<int> s21_set;

  std::pair<s21::set<int>::iterator, bool> insert1 = s21_set.insert(9);
  EXPECT_EQ(*insert1.first, 9);
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<int>::iterator, bool> insert2 = s21_set.insert(9);
  std::pair<s21::set<int>::iterator, bool> insert3 = s21_set.insert(9);
  EXPECT_EQ(insert2.second, 0);
  EXPECT_EQ(insert3.second, false);

  std::pair<s21::set<int>::iterator, bool> insert4 = s21_set.insert(23);
  EXPECT_EQ(*insert4.first, 23);
  EXPECT_EQ(insert4.second, true);

  std::pair<s21::set<int>::iterator, bool> insert5 = s21_set.insert(98);
  EXPECT_EQ(*insert5.first, 98);
  EXPECT_EQ(insert5.second, true);

  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_insert, case2) {
  s21::set<double> s21_set;

  std::pair<s21::set<double>::iterator, bool> insert1 = s21_set.insert(1.4);
  EXPECT_EQ(*insert1.first, 1.4);
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<double>::iterator, bool> insert2 = s21_set.insert(2.77);
  EXPECT_EQ(*insert2.first, 2.77);
  EXPECT_EQ(insert2.second, true);

  std::pair<s21::set<double>::iterator, bool> insert3 = s21_set.insert(3.9);
  EXPECT_EQ(*insert3.first, 3.9);
  EXPECT_EQ(insert3.second, true);

  std::pair<s21::set<double>::iterator, bool> insert4 = s21_set.insert(2.77);
  std::pair<s21::set<double>::iterator, bool> insert5 = s21_set.insert(3.9);
  EXPECT_EQ(insert4.second, false);
  EXPECT_EQ(insert5.second, false);

  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_insert, case3) {
  s21::set<std::string> s21_set;

  std::pair<s21::set<std::string>::iterator, bool> insert1 =
      s21_set.insert("hello");
  EXPECT_EQ(*insert1.first, "hello");
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<std::string>::iterator, bool> insert2 =
      s21_set.insert("hi");
  EXPECT_EQ(*insert2.first, "hi");
  EXPECT_EQ(insert2.second, true);

  std::pair<s21::set<std::string>::iterator, bool> insert3 =
      s21_set.insert("hi");
  EXPECT_EQ(insert3.second, false);

  std::pair<s21::set<std::string>::iterator, bool> insert4 =
      s21_set.insert("hola");
  EXPECT_EQ(*insert4.first, "hola");
  EXPECT_EQ(insert4.second, true);

  std::pair<s21::set<std::string>::iterator, bool> insert5 =
      s21_set.insert("hello");
  EXPECT_EQ(insert5.second, false);

  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_insert, case4) {
  s21::set<int> s21_set;

  std::pair<s21::set<int>::iterator, bool> insert1 = s21_set.insert(9);
  EXPECT_EQ(*insert1.first, 9);
  EXPECT_EQ(insert1.second, true);

  std::pair<s21::set<int>::iterator, bool> insert2 = s21_set.insert(9);
  std::pair<s21::set<int>::iterator, bool> insert3 = s21_set.insert(9);
  EXPECT_EQ(insert2.second, false);
  EXPECT_EQ(insert3.second, false);

  EXPECT_EQ(s21_set.size(), 1U);
}

TEST(set_insert, case5) {
  s21::set<double> s21_set = {21};

  std::pair<s21::set<double>::iterator, bool> insert1 = s21_set.insert(1.4);
  EXPECT_EQ(insert1.second, true);

  EXPECT_EQ(s21_set.size(), 2U);
}

TEST(set_insert, case6) {
  s21::set<std::string> s21_set = {"hello"};

  std::pair<s21::set<std::string>::iterator, bool> insert1 =
      s21_set.insert("hi");
  EXPECT_EQ(*insert1.first, "hi");
  EXPECT_EQ(insert1.second, true);

  EXPECT_EQ(s21_set.size(), 2U);
}

TEST(set_begin, case1) {
  s21::set<int> s21_set = {9, 15, 7, 23, 2};

  EXPECT_EQ(*s21_set.begin(), 2);
}

TEST(set_begin, case2) {
  s21::set<double> s21_set = {11.4, 2.770001, 3.901, 2.77, 3.9};

  EXPECT_EQ(*s21_set.begin(), 2.77);
}

TEST(set_begin, case3) {
  s21::set<std::string> s21_set = {"hello", "hi", "hi-hi", "hola",
                                   "hello, there"};

  EXPECT_EQ(*s21_set.begin(), "hello");
}

TEST(set_begin, case5) {
  s21::set<double> s21_set = {1.4, 1.4};

  EXPECT_EQ(*s21_set.begin(), 1.4);
}

TEST(set_begin, case6) {
  s21::set<std::string> s21_set = {"hello", "hello", "hello"};

  EXPECT_EQ(*s21_set.begin(), "hello");
}

TEST(set_balance, case1) {
  s21::set<int> s21_set = {1, 15, 5};

  EXPECT_EQ(*s21_set.end(), 15);
  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_balance, case2) {
  s21::set<double> s21_set = {11.4, 2.770001, 3.901};

  EXPECT_EQ(*(--s21_set.end()), 11.4);
  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_balance, case3) {
  s21::set<std::string> s21_set = {"hello", "hi", "hola-hola", "hola",
                                   "hello, there"};

  EXPECT_EQ(*(--s21_set.end()), "hola-hola");
  EXPECT_EQ(s21_set.size(), 5U);
}

TEST(set_balance, case4) {
  s21::set<int> s21_set = {10, 5, 20, 30, 1543};

  EXPECT_EQ(*(--s21_set.end()), 1543);
  EXPECT_EQ(*s21_set.begin(), 5);
  EXPECT_EQ(s21_set.size(), 5U);
}

TEST(set_balance, case5) {
  s21::set<int> s21_set = {30, 5, 43, 1, 20, 40, 60, 35, 32};

  EXPECT_EQ(*(--s21_set.end()), 60);
  EXPECT_EQ(*s21_set.begin(), 1);
  EXPECT_EQ(s21_set.size(), 9U);
}

TEST(set_erase, case1) {
  s21::set<int> s21_set = {10, 5, 15, 4, 18, 13, 16};

  auto it = s21_set.begin();
  it++;
  it++;
  it++;
  it++;
  s21_set.erase(it);
  EXPECT_EQ(*s21_set.begin(), 4);
  EXPECT_EQ(*(--s21_set.end()), 18);
  EXPECT_EQ(s21_set.size(), 6U);

  it = s21_set.begin();
  s21_set.erase(it);
  EXPECT_EQ(*s21_set.begin(), 5);
  EXPECT_EQ(*(--s21_set.end()), 18);
  EXPECT_EQ(s21_set.size(), 5U);

  it = s21_set.begin();
  it++;
  s21_set.erase(it);
  EXPECT_EQ(*s21_set.begin(), 5);
  EXPECT_EQ(*(--s21_set.end()), 18);
  EXPECT_EQ(s21_set.size(), 4U);

  it = s21_set.end();
  it--;
  s21_set.erase(it);
  EXPECT_EQ(*s21_set.begin(), 5);
  EXPECT_EQ(*(--s21_set.end()), 16);
  EXPECT_EQ(s21_set.size(), 3U);

  it = s21_set.begin();
  it++;
  s21_set.erase(it);

  it = s21_set.begin();
  it++;
  s21_set.erase(it);

  it = s21_set.begin();
  s21_set.erase(it);

  EXPECT_EQ(s21_set.size(), 0U);
}

TEST(set_erase, case2) {
  s21::set<int> s21_set = {30, 1543};

  auto it = s21_set.begin();
  it++;
  s21_set.erase(it);
  it = s21_set.begin();
  s21_set.erase(it);

  EXPECT_EQ(s21_set.size(), 0U);
}

TEST(set_erase, case3) {
  s21::set<std::string> s21_set = {"hello", "hi", "hola-hola", "hola",
                                   "hello, there"};

  auto it = s21_set.end();
  it--;
  s21_set.erase(it);
  EXPECT_EQ(*s21_set.end(), "hola");
  EXPECT_EQ(s21_set.size(), 4U);

  it = s21_set.end();
  it--;
  s21_set.erase(it);
  EXPECT_EQ(*s21_set.end(), "hi");
  EXPECT_EQ(s21_set.size(), 3U);

  s21_set.insert("hola-hola");
  s21_set.insert("hola");
  it = s21_set.end();
  it--;
  s21_set.erase(it);
  EXPECT_EQ(*s21_set.end(), "hola");
  EXPECT_EQ(s21_set.size(), 4U);
}

TEST(set_erase, case4) {
  s21::set<double> s21_set = {22.2, 12.4457, 56.84, 941.44, 44.48};

  auto it = s21_set.end();
  it--;
  it--;
  s21_set.erase(it);
  it = s21_set.end();
  it--;
  EXPECT_EQ(*it, 941.44);
  EXPECT_EQ(s21_set.size(), 4U);

  it = s21_set.begin();
  ++it;
  ++it;
  ++it;
  s21_set.erase(it);
  it = s21_set.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*s21_set.end(), 44.48);
  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_erase, case5) {
  s21::set<double> s21_set = {22.2, 44.48, 12.4457, 1.44};

  auto it = s21_set.begin();
  it--;
  s21_set.erase(it);
  it = s21_set.begin();
  ++it;
  ++it;
  EXPECT_EQ(*it, 44.48);
  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_erase, case6) {
  s21::set<double> s21_set = {22.2, 44.48, 12.4457, 6.84, 1.44};

  auto it = s21_set.begin();
  ++it;
  ++it;
  ++it;
  s21_set.erase(it);
  it = s21_set.begin();
  it++;
  it++;
  it++;
  EXPECT_EQ(*it, 44.48);
  EXPECT_EQ(s21_set.size(), 4U);
}

TEST(set_erase, case7) {
  s21::set<double> s21_set = {22.2, 12.4457, 56.84, 941.44, 44.48};

  auto it = s21_set.begin();
  ++it;
  s21_set.erase(it);
  it = s21_set.begin();
  ++it;
  EXPECT_EQ(*it, 44.48);
  EXPECT_EQ(s21_set.size(), 4U);
}

TEST(set_erase, case8) {
  s21::set<double> s21_set = {22.2, 44.48, 12.4457, 1.44};

  auto it = s21_set.begin();
  ++it;
  s21_set.erase(it);
  it = s21_set.begin();
  ++it;
  EXPECT_EQ(*it, 22.2);
  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_erase, case9) {
  s21::set<double> s21_set = {22.2,  44.48, 12.4457, 32.45,
                              65.12, 66.32, 40.54,   6.4};

  auto it = s21_set.end();
  it--;
  it--;
  it--;
  it--;
  it--;
  s21_set.erase(it);
  it = s21_set.begin();
  ++it;
  ++it;
  ++it;
  EXPECT_EQ(*it, 40.54);
  EXPECT_EQ(s21_set.size(), 7U);
}

TEST(set_erase, case10) {
  s21::set<double> s21_set = {22.2};

  auto it = s21_set.end();
  it--;
  it--;
  s21_set.erase(it);
  EXPECT_EQ(s21_set.size(), 0U);
}

TEST(set_empty, case1) {
  s21::set<double> s21_set = {22.2, 44.48, 12.4457, 1.44};

  EXPECT_EQ(s21_set.empty(), 0);
}

TEST(set_empty, case2) {
  s21::set<double> s21_set;

  EXPECT_EQ(s21_set.empty(), 1);
}

TEST(set_swap, case1) {
  s21::set<double> s21_set_ref = {22.2, 44.48};
  s21::set<double> s21_set_res = {12.4457, 1.44, 22.2};

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 3U);
  EXPECT_EQ(*s21_set_ref.begin(), 1.44);

  EXPECT_EQ(s21_set_res.size(), 2U);
  EXPECT_EQ(*s21_set_res.begin(), 22.2);
}

TEST(set_swap, case2) {
  s21::set<double> s21_set_ref = {22.2, 44.48};
  s21::set<double> s21_set_res;

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 0U);

  EXPECT_EQ(s21_set_res.size(), 2U);
  EXPECT_EQ(*s21_set_res.begin(), 22.2);
}

TEST(set_swap, case3) {
  s21::set<double> s21_set_ref;
  s21::set<double> s21_set_res = {12.4457, 1.44, 22.2};

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 3U);
  EXPECT_EQ(*s21_set_ref.begin(), 1.44);

  EXPECT_EQ(s21_set_res.size(), 0U);
}

TEST(set_swap, case4) {
  s21::set<double> s21_set_ref;
  s21::set<double> s21_set_res;

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 0U);
  EXPECT_EQ(s21_set_res.size(), 0U);
}

TEST(set_contains, case1) {
  s21::set<double> s21_set = {22.2, 44.48};

  EXPECT_EQ(s21_set.contains(22.2), true);
  EXPECT_EQ(s21_set.contains(44.48), true);
}

TEST(set_contains, case2) {
  s21::set<double> s21_set_ref = {22.2, 44.48};
  s21::set<double> s21_set_res;

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 0U);
  EXPECT_EQ(s21_set_ref.contains(22.2), false);
  EXPECT_EQ(s21_set_ref.contains(44.48), false);

  EXPECT_EQ(s21_set_res.size(), 2U);
  EXPECT_EQ(s21_set_res.contains(22.2), true);
  EXPECT_EQ(s21_set_res.contains(44.48), true);
}

TEST(set_contains, case3) {
  s21::set<double> s21_set_ref;
  s21::set<double> s21_set_res = {12.4457, 1.44, 22.2};

  s21_set_ref.swap(s21_set_res);

  EXPECT_EQ(s21_set_ref.size(), 3U);
  EXPECT_EQ(s21_set_ref.contains(12.4457), true);
  EXPECT_EQ(s21_set_ref.contains(1.44), true);
  EXPECT_EQ(s21_set_ref.contains(22.2), true);

  EXPECT_EQ(s21_set_res.size(), 0U);
  EXPECT_EQ(s21_set_res.contains(12.4457), false);
  EXPECT_EQ(s21_set_res.contains(1.44), false);
  EXPECT_EQ(s21_set_res.contains(22.2), false);
}

TEST(set_contains, case4) {
  s21::set<double> s21_set;

  EXPECT_EQ(s21_set.size(), 0U);
  EXPECT_EQ(s21_set.contains(12.4457), false);
}

TEST(set_find, case2) {
  s21::set<double> s21_set = {12.4457, 1.44, 22.2};

  auto it = s21_set.begin();
  ++it;
  EXPECT_EQ(*s21_set.find(12.4457), *it);

  it--;
  EXPECT_EQ(*s21_set.find(1.44), *it);

  it++;
  it++;
  EXPECT_EQ(*s21_set.find(22.2), *it);
}

TEST(set_insert_many, case1) {
  s21::set<int> s21_set;

  std::vector<std::pair<s21::set<int>::iterator, bool>> insert_many1 =
      s21_set.insert_many(9, 9, 9, 23, 98);

  EXPECT_EQ(*insert_many1[0].first, 9);
  EXPECT_EQ(insert_many1[0].second, true);
  EXPECT_EQ(*insert_many1[1].first, 9);
  EXPECT_EQ(insert_many1[1].second, false);
  EXPECT_EQ(*insert_many1[2].first, 9);
  EXPECT_EQ(insert_many1[2].second, false);
  EXPECT_EQ(*insert_many1[3].first, 23);
  EXPECT_EQ(insert_many1[3].second, true);
  EXPECT_EQ(*insert_many1[4].first, 98);
  EXPECT_EQ(insert_many1[4].second, true);
  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_insert_many, case2) {
  s21::set<double> s21_set;

  std::vector<std::pair<s21::set<double>::iterator, bool>> insert_many1 =
      s21_set.insert_many(1.4, 2.77, 3.9, 2.77, 3.9);

  EXPECT_EQ(*insert_many1[0].first, 1.4);
  EXPECT_EQ(insert_many1[0].second, true);
  EXPECT_EQ(*insert_many1[3].first, 2.77);
  EXPECT_EQ(insert_many1[3].second, false);
  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_insert_many, case3) {
  s21::set<std::string> s21_set;

  std::vector<std::pair<s21::set<std::string>::iterator, bool>> insert_many1 =
      s21_set.insert_many("hello", "hi", "hi", "hola", "hello");

  EXPECT_EQ(*insert_many1[0].first, "hello");
  EXPECT_EQ(insert_many1[0].second, true);
  EXPECT_EQ(*insert_many1[4].first, "hello");
  EXPECT_EQ(insert_many1[4].second, false);
  EXPECT_EQ(s21_set.size(), 3U);
}

TEST(set_insert_many, case4) {
  s21::set<int> s21_set;

  std::vector<std::pair<s21::set<int>::iterator, bool>> insert_many1 =
      s21_set.insert_many(9);

  EXPECT_EQ(*insert_many1[0].first, 9);
  EXPECT_EQ(insert_many1[0].second, true);
  EXPECT_EQ(s21_set.size(), 1U);
}

TEST(set_insert_many, case5) {
  s21::set<double> s21_set = {1.4};

  std::vector<std::pair<s21::set<double>::iterator, bool>> insert_many1 =
      s21_set.insert_many(1.4);

  EXPECT_EQ(insert_many1[0].second, false);
  EXPECT_EQ(s21_set.size(), 1U);
}

TEST(set_insert_many, case6) {
  s21::set<std::string> s21_set = {"hello"};

  std::vector<std::pair<s21::set<std::string>::iterator, bool>> insert_many1 =
      s21_set.insert_many("hi");

  EXPECT_EQ(*insert_many1[0].first, "hi");
  EXPECT_EQ(insert_many1[0].second, true);
  EXPECT_EQ(s21_set.size(), 2U);
}
