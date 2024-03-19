#include <map>

#include "test_runner.h"

TEST(map, ConstructorDefaultMap) {
  s21::map<int, char> s21_map;
  std::map<int, char> std_map;
  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(map, ConstructorWithOtherMap) {
  s21::map<int, char> s21_map_1 = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  s21::map<int, char> s21_map_2(s21_map_1);
  EXPECT_EQ(s21_map_2.size(), s21_map_1.size());
  auto s21_it = s21_map_2.begin();
  auto orig_it = s21_map_1.begin();
  for (; s21_it != s21_map_2.end(); ++s21_it, ++orig_it) {
    EXPECT_TRUE((*s21_it).first == (*orig_it).first);
    EXPECT_TRUE((*s21_it).second == (*orig_it).second);
  }
}

TEST(map, ConstructorInitializerMap) {
  s21::map<int, char> s21_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  std::map<int, char> std_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  EXPECT_EQ(s21_map.size(), std_map.size());
  auto s21_it = s21_map.begin();
  auto orig_it = std_map.begin();
  for (; s21_it != s21_map.end(); ++s21_it, ++orig_it) {
    EXPECT_TRUE((*s21_it).first == (*orig_it).first);
    EXPECT_TRUE((*s21_it).second == (*orig_it).second);
  }
}

TEST(map, ConstructorInitializer2Map) {
  s21::map<int, char> s21_map = {};
  std::map<int, char> std_map = {};
  EXPECT_EQ(s21_map.size(), std_map.size());
  auto s21_it = s21_map.begin();
  auto orig_it = std_map.begin();
  for (; s21_it != s21_map.end(); ++s21_it, ++orig_it) {
    EXPECT_TRUE((*s21_it).first == (*orig_it).first);
    EXPECT_TRUE((*s21_it).second == (*orig_it).second);
  }
}

TEST(map, ConstructorCopyMap) {
  s21::map<int, int> s21_map = {{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> std_map = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> s21_map_copy = s21_map;
  std::map<int, int> std_map_copy = std_map;
  EXPECT_EQ(s21_map_copy.size(), std_map_copy.size());
  auto s21_it = s21_map_copy.begin();
  auto orig_it = std_map_copy.begin();
  for (; s21_it != s21_map_copy.end(); ++s21_it, ++orig_it) {
    EXPECT_TRUE((*s21_it).first == (*orig_it).first);
    EXPECT_TRUE((*s21_it).second == (*orig_it).second);
  }
}

TEST(map, ConstructorMoveMap) {
  s21::map<int, int> s21_map = {{1, 2}, {3, 4}, {5, 6}};
  std::map<int, int> std_map = {{1, 2}, {3, 4}, {5, 6}};
  s21::map<int, int> s21_map_copy = std::move(s21_map);
  std::map<int, int> std_map_copy = std::move(std_map);
  EXPECT_EQ(s21_map.size(), std_map.size());
  EXPECT_EQ(s21_map_copy.size(), std_map_copy.size());
  auto s21_it = s21_map_copy.begin();
  auto orig_it = std_map_copy.begin();
  for (; s21_it != s21_map_copy.end(); ++s21_it, ++orig_it) {
    EXPECT_TRUE((*s21_it).first == (*orig_it).first);
    EXPECT_TRUE((*s21_it).second == (*orig_it).second);
  }
}

TEST(map, MapOperator) {
  s21::map<char, std::string> s21_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  std::map<char, std::string> std_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  s21_map['a'] = "Alisa";
  std_map['a'] = "Alisa";
  std_map['b'] = "Ben";
  EXPECT_TRUE(s21_map['a'] == std_map['a']);
  EXPECT_FALSE(s21_map['b'] == std_map['b']);
  EXPECT_TRUE(s21_map['c'] == std_map['c']);
}

TEST(map, MapAtOperatorException) {
  s21::map<char, std::string> s21_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  EXPECT_THROW(s21_map.at('g') = "Alisa", std::out_of_range);
}

TEST(map, MapAtOperator) {
  s21::map<char, std::string> s21_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  std::map<char, std::string> std_map = {
      {'a', "Alina"}, {'b', "Boris"}, {'c', "Chuck"}};
  s21_map.at('a') = "Alisa";
  std_map.at('a') = "Alisa";
  std_map.at('b') = "Ben";
  EXPECT_TRUE(s21_map['a'] == std_map['a']);
  EXPECT_FALSE(s21_map['b'] == std_map['b']);
  EXPECT_TRUE(s21_map['c'] == std_map['c']);
}

TEST(map, MapCapacity) {
  s21::map<char, std::string> s21_map;
  std::map<char, std::string> std_map;
  EXPECT_TRUE(s21_map.empty() == std_map.empty());
  s21_map.insert('z', "wow");
  EXPECT_FALSE(s21_map.empty() == std_map.empty());
  EXPECT_EQ(s21_map.size(), 1);
}

TEST(map, MapClear) {
  s21::map<int, int> s21_map;
  std::map<int, int> std_map;
  s21_map.clear();
  std_map.clear();
  EXPECT_EQ(s21_map.empty(), std_map.empty());
  s21_map.insert(std::make_pair(1, 1));
  std_map.insert(std::make_pair(1, 1));
  EXPECT_EQ(s21_map.empty(), std_map.empty());
  s21_map.clear();
  std_map.clear();
  EXPECT_EQ(s21_map.empty(), std_map.empty());
}

TEST(map, MapInsert1) {
  s21::map<int, char> s21_map;
  std::map<int, char> std_map;
  s21_map.insert(std::make_pair(1, 'a'));
  s21_map.insert(std::make_pair(2, 'a'));
  s21_map.insert(std::make_pair(3, 'a'));
  std_map.insert(std::make_pair(1, 'a'));
  std_map.insert(std::make_pair(2, 'a'));
  std_map.insert(std::make_pair(3, 'a'));

  auto s21_it = s21_map.begin();
  auto orig_it = std_map.begin();
  for (; s21_it != s21_map.end(); ++s21_it, ++orig_it) {
    EXPECT_TRUE((*s21_it).first == (*orig_it).first);
    EXPECT_TRUE((*s21_it).second == (*orig_it).second);
  }

  auto pr1 = s21_map.insert(std::make_pair(1, 'a'));
  auto pr2 = std_map.insert(std::make_pair(1, 'a'));
  EXPECT_TRUE(pr1.second == pr2.second);
}

TEST(map, MapInsert2) {
  s21::map<int, char> s21_map;
  std::map<int, char> std_map;
  s21_map.insert(1, 'a');
  s21_map.insert(2, 'a');
  s21_map.insert(3, 'a');
  std_map.insert(std::make_pair(1, 'a'));
  std_map.insert(std::make_pair(2, 'a'));
  std_map.insert(std::make_pair(3, 'a'));

  auto s21_it = s21_map.begin();
  auto orig_it = std_map.begin();
  for (; s21_it != s21_map.end(); ++s21_it, ++orig_it) {
    EXPECT_TRUE((*s21_it).first == (*orig_it).first);
    EXPECT_TRUE((*s21_it).second == (*orig_it).second);
  }

  auto pr1 = s21_map.insert(1, 'a');
  auto pr2 = std_map.insert(std::make_pair(1, 'a'));
  EXPECT_TRUE(pr1.second == pr2.second);
}

TEST(map, MapInsert3) {
  s21::map<int, char> s21_map;
  std::map<int, char> std_map;
  s21_map.insert(1, 'a');
  s21_map.insert(2, 'a');
  s21_map.insert(3, 'a');
  std_map.insert(std::make_pair(1, 'a'));
  std_map.insert(std::make_pair(2, 'a'));
  std_map.insert(std::make_pair(3, 'a'));

  auto s21_it = s21_map.begin();
  auto orig_it = std_map.begin();
  for (; s21_it != s21_map.end(); ++s21_it, ++orig_it) {
    EXPECT_TRUE((*s21_it).first == (*orig_it).first);
    EXPECT_TRUE((*s21_it).second == (*orig_it).second);
  }

  auto pr1 = s21_map.insert_or_assign(1, 'b');
  auto i = std_map.begin();
  EXPECT_TRUE((*pr1.first).first == (*i).first);
  EXPECT_FALSE((*pr1.first).second == (*i).second);
}

TEST(map, MapInsertMany) {
  s21::map<int, char> s21_map;

  std::vector<std::pair<s21::map<int, char>::iterator, bool>> insert_many1 =
      s21_map.insert_many(std::make_pair(1, 'x'), std::make_pair(2, 'b'),
                          std::make_pair(3, 'z'), std::make_pair(4, 'y'));

  EXPECT_EQ(s21_map.size(), 4U);
}

TEST(map, MapErase) {
  s21::map<int, char> s21_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  std::map<int, char> std_map = {{1, 'x'}, {2, 'b'}, {3, 'z'}, {4, 'y'}};
  EXPECT_EQ(s21_map.size(), std_map.size());
  s21_map.erase(s21_map.begin());
  std_map.erase(std_map.begin());
  EXPECT_EQ(s21_map.size(), std_map.size());
  auto s21_it = s21_map.begin();
  auto orig_it = std_map.begin();
  for (; s21_it != s21_map.end(); ++s21_it, ++orig_it) {
    EXPECT_TRUE((*s21_it).first == (*orig_it).first);
    EXPECT_TRUE((*s21_it).second == (*orig_it).second);
  }
}

TEST(map, SwapMap) {
  s21::map<int, int> s21_map = {{1, 1}};
  s21::map<int, int> std_map = {{3, 3}, {4, 4}};

  s21_map.swap(std_map);
  EXPECT_EQ(s21_map.size(), 2);
  EXPECT_EQ(std_map.size(), 1);
  auto x = (*(s21_map.begin())).first;
  auto y = (*(std_map.begin())).first;
  EXPECT_EQ(x, 3);
  EXPECT_EQ(y, 1);
}

TEST(map, MergeMap) {
  s21::map<int, int> s21_map = {{1, 1}, {4, 4}, {2, 2}};
  s21::map<int, int> map_for_merge = {{3, 3}, {4, 4}};

  std::map<int, int> std_map = {{1, 1}, {4, 4}, {2, 2}};
  std::map<int, int> std_map_for_merge = {{3, 3}, {4, 4}};

  s21_map.merge(map_for_merge);
  std_map.merge(std_map_for_merge);

  auto s21_it = s21_map.begin();
  auto orig_it = std_map.begin();
  for (; s21_it != s21_map.end(); ++s21_it, ++orig_it) {
    EXPECT_TRUE((*s21_it).first == (*orig_it).first);
    EXPECT_TRUE((*s21_it).second == (*orig_it).second);
  }
  EXPECT_EQ(map_for_merge.contains(4), std_map_for_merge[4] == 4);
  EXPECT_EQ(map_for_merge.contains(3), std_map_for_merge[3] == 3);
}