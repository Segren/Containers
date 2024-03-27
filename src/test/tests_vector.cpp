#include "test_runner.h"

TEST(VectorTest, Constructor_Empty) {
  s21::vector<int> v;
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0u);
}

TEST(VectorTest, Constructor_EmptyList) {
  s21::vector<int> vec = {};
  EXPECT_EQ(vec.size(), 0u);
  EXPECT_TRUE(vec.empty());
}

TEST(VectorTest, Constructor_NotEmptyList) {
  s21::vector<int> vec = {1, 2, 3, 4, 5};
  EXPECT_EQ(vec.size(), 5u);
  EXPECT_FALSE(vec.empty());
  EXPECT_EQ(vec[2], 3);
}

TEST(VectorTest, Constructor_SizeTen) {
  size_t size = 10;
  s21::vector<int> vec(size);
  EXPECT_EQ(vec.size(), size);
  for (size_t i = 0; i < size; ++i) {
    EXPECT_EQ(vec[i], 0);
  }
}

TEST(VectorTest, Constructor_SizeZero) {
  size_t size = 0;
  s21::vector<int> vec(size);
  EXPECT_EQ(vec.size(), size);
  for (size_t i = 0; i < size; ++i) {
    EXPECT_EQ(vec[i], 0);
  }
}

TEST(VectorTest, Copy_Empty) {
  s21::vector<int> v1;
  s21::vector<int> v2(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), 0u);
}

TEST(VectorTest, Copy_NotEmpty) {
  s21::vector<int> v1 = {1, 2, 3, 4, 5};
  s21::vector<int> v2(v1);
  EXPECT_EQ(v2.size(), v1.size());
  for (size_t i = 0; i < v1.size(); ++i) {
    EXPECT_EQ(v2[i], v1[i]);
  }
}

TEST(VectorTest, Move_Empty) {
  s21::vector<int> v1;
  s21::vector<int> v2(std::move(v1));
  EXPECT_TRUE(v2.empty());
}

TEST(VectorTest, Move_NotEmpty) {
  s21::vector<int> v1 = {1, 2, 3, 4, 5};
  s21::vector<int> v2(std::move(v1));
  EXPECT_EQ(v2.size(), 5u);
  EXPECT_TRUE(v1.empty());
}

TEST(VectorTest, Destructor_Empty) {
  auto *v = new s21::vector<int>();
  delete v;
}

TEST(VectorTest, Destructor_NotEmpty) {
  auto *v = new s21::vector<int>{1, 2, 3, 4, 5};
  delete v;
}

TEST(VectorTest, Move_NotEmptyToEmpty) {
  s21::vector<int> v1 = {1, 2, 3, 4, 5};
  s21::vector<int> v2;
  v2 = std::move(v1);
  EXPECT_EQ(v2.size(), 5u);
  EXPECT_TRUE(v1.empty());
}

TEST(VectorTest, Move_EmptyToNotEmpty) {
  s21::vector<int> v1;
  s21::vector<int> v2 = {1, 2, 3, 4, 5};
  v2 = std::move(v1);
  EXPECT_TRUE(v2.empty());
  EXPECT_EQ(v2.size(), 0u);
}

TEST(VectorTest, Move_NotEmptyToNotEmpty) {
  s21::vector<int> v1 = {1, 2, 3, 4, 5};
  s21::vector<int> v2 = {2, 3, 4};
  v2 = std::move(v1);
  EXPECT_EQ(v2.size(), 5u);
  EXPECT_TRUE(v1.empty());
}

TEST(VectorTest, At_InRange) {
  s21::vector<int> v1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(v1.at(0), 1);
  EXPECT_EQ(v1.at(3), 4);
  EXPECT_EQ(v1.at(4), 5);
}

TEST(VectorTest, At_OutOfRange) {
  s21::vector<int> v1 = {1, 2, 3, 4, 5};
  EXPECT_THROW(v1.at(5), std::out_of_range);
  EXPECT_THROW(v1.at(-1), std::out_of_range);
}

TEST(VectorTest, BracketOperator_InRange) {
  s21::vector<int> v1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(v1[0], 1);
  EXPECT_EQ(v1[3], 4);
  EXPECT_EQ(v1[4], 5);
}

TEST(VectorTest, BracketOperator_OutOfRange) {
  s21::vector<int> v1 = {1, 2, 3, 4, 5};
  EXPECT_ANY_THROW(v1[5]);
  EXPECT_ANY_THROW(v1[-1]);
}

TEST(VectorTest, ConstBracketOperator_InRange) {
  const s21::vector<int> v1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(v1[0], 1);
  EXPECT_EQ(v1[3], 4);
  EXPECT_EQ(v1[4], 5);
}

TEST(VectorTest, ConstBracketOperator_OutOfRange) {
  const s21::vector<int> v1 = {1, 2, 3, 4, 5};
  EXPECT_ANY_THROW(v1[5]);
  EXPECT_ANY_THROW(v1[-1]);
}

TEST(VectorTest, FrontConst_InRange) {
  const s21::vector<int> v1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(v1.front(), 1);
}

TEST(VectorTest, Front_InRange) {
  s21::vector<int> v1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(v1.front(), 1);
}

TEST(VectorTest, FrontConst_OutOfRange) {
  const s21::vector<int> v1;
  EXPECT_THROW(v1.front(), std::out_of_range);
}

TEST(VectorTest, Front_OutOfRange) {
  s21::vector<int> v1;
  EXPECT_THROW(v1.front(), std::out_of_range);
}

TEST(VectorTest, ConstBack_InRange) {
  const s21::vector<int> v1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(v1.back(), 5);
}

TEST(VectorTest, Back_InRange) {
  s21::vector<int> v1 = {1, 2, 3, 4, 5};
  EXPECT_EQ(v1.back(), 5);
}

TEST(VectorTest, ConstBack_OutOfRange) {
  const s21::vector<int> v1;
  EXPECT_THROW(v1.back(), std::out_of_range);
}

TEST(VectorTest, Back_OutOfRange) {
  s21::vector<int> v1;
  EXPECT_THROW(v1.back(), std::out_of_range);
}

TEST(VectorTest, Back_OutOfRangeSizeZero) {
  s21::vector<int> v1{1};
  v1.pop_back();
  EXPECT_THROW(v1.back(), std::out_of_range);
}

TEST(VectorTest, Data_Valid) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  int *data = v.data();
  EXPECT_EQ(*data, 1);

  *data = 7;
  EXPECT_EQ(v[0], 7);
}

TEST(VectorTest, Data_Empty) {
  s21::vector<int> v;
  int *data = v.data();
  // Data pointer of an empty vector can be anything
  EXPECT_EQ(data, nullptr);
}

TEST(VectorTest, Begin_Valid) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.begin();
  EXPECT_EQ(*it, 1);
  // Modify the data through the iterator and check if the vector is updated
  *it = 7;
  EXPECT_EQ(v[0], 7);
}

TEST(VectorTest, Begin_Empty) {
  s21::vector<int> v;
  auto it = v.begin();
  EXPECT_EQ(it, v.end());
}

TEST(VectorTest, End_Valid) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.end();
  EXPECT_EQ(*(it - 1), 5);
}

TEST(VectorTest, End_Empty) {
  s21::vector<int> v;
  auto it = v.end();
  EXPECT_EQ(it, v.begin());
}

TEST(VectorTest, CBegin_Valid) {
  const s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.begin();
  EXPECT_EQ(*it, 1);
  // error if uncommented
  //*it = 7;
}

TEST(VectorTest, CBegin_Empty) {
  const s21::vector<int> v;
  auto it = v.begin();
  EXPECT_EQ(it, v.end());
}

TEST(VectorTest, CEnd_Valid) {
  const s21::vector<int> v = {1, 2, 3, 4, 5};
  auto it = v.end();
  EXPECT_EQ(*(it - 1), 5);
}

TEST(VectorTest, CEnd_Empty) {
  const s21::vector<int> v;
  auto it = v.end();
  EXPECT_EQ(it, v.begin());
}

TEST(VectorTest, Empty_Empty) {
  const s21::vector<int> v;
  EXPECT_TRUE(v.empty());
}

TEST(VectorTest, Empty_NotEmpty) {
  const s21::vector<int> v = {1, 2, 3};
  EXPECT_FALSE(v.empty());
}

TEST(VectorTest, Size_Empty) {
  const s21::vector<int> v;
  EXPECT_EQ(v.size(), 0u);
}

TEST(VectorTest, Size_NonEmptyVector) {
  const s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.size(), 5u);
}

TEST(VectorTest, Size_MaxSize) {
  const s21::vector<int> v;
  EXPECT_GT(v.max_size(), 0u);
}

TEST(VectorTest, Reserve_IncreaseCapacity) {
  s21::vector<int> v;
  size_t initialCap = v.capacity();
  size_t newCap = initialCap + 5;
  v.reserve(newCap);
  EXPECT_EQ(v.capacity(), newCap);
}

TEST(VectorTest, Capacity_Empty) {
  const s21::vector<int> v;
  EXPECT_EQ(v.capacity(), 0u);
}

TEST(VectorTest, Capacity_NotEmpty) {
  const s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_EQ(v.capacity(), v.size());
}

TEST(VectorTest, ShrinkToFit_EmptyVector) {
  s21::vector<int> v;
  v.shrink_to_fit();
  EXPECT_GE(v.capacity(), 0u);
}

TEST(VectorTest, ShrinkToFit_EmptyVectorSizeZero) {
  s21::vector<int> v = {1};
  v.pop_back();
  v.shrink_to_fit();
  EXPECT_GE(v.capacity(), 0u);
}

TEST(VectorTest, ShrinkToFit_NonEmptyVector) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  size_t initialCap = v.capacity();
  v.pop_back();
  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), v.size());
  EXPECT_LE(v.capacity(), initialCap);
}

TEST(VectorTest, Clear_Empty) {
  s21::vector<int> v;
  v.clear();
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0u);
}

TEST(VectorTest, Clear_NotEmpty) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  v.clear();
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0u);
}

TEST(VectorTest, Insert_Beginning) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  v.insert(v.begin(), 7);
  EXPECT_EQ(v[0], 7);
  EXPECT_EQ(v.size(), 6u);
}

TEST(VectorTest, Insert_Middle) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  v.insert(v.begin() + 2, 7);
  EXPECT_EQ(v[2], 7);
  EXPECT_EQ(v.size(), 6u);
}

TEST(VectorTest, Insert_End) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  v.insert(v.end(), 7);
  auto it = v.end();
  EXPECT_EQ(*(it - 1), 7);
  EXPECT_EQ(v.size(), 6u);
}

TEST(VectorTest, Insert_Out_Of_Range) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_ANY_THROW(v.insert(v.end() + 1, 7));
}

TEST(VectorTest, Erase_Out_Of_Range) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  EXPECT_ANY_THROW(v.erase(v.end() + 1));
}

TEST(VectorTest, Erase_Beginning) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  v.erase(v.begin());
  EXPECT_EQ(v.size(), 4u);
  EXPECT_EQ(v[0], 2);
}

TEST(VectorTest, Erase_Middle) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  v.erase(v.begin() + 1);
  EXPECT_EQ(v.size(), 4u);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 3);
}

TEST(VectorTest, Erase_End) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  v.erase(v.end() - 1);
  auto it = v.end();
  EXPECT_EQ(*(it - 1), 4);
  EXPECT_EQ(v.size(), 4u);
}

TEST(VectorTest, PushBack_Empty) {
  s21::vector<int> v;
  v.push_back(1);
  EXPECT_EQ(v.size(), 1u);
  EXPECT_EQ(v[0], 1);
}

TEST(VectorTest, PushBack_NotEmpty) {
  s21::vector<int> v = {1, 2, 3, 4};
  v.push_back(5);
  EXPECT_EQ(v.size(), 5u);
  EXPECT_EQ(v[4], 5);
}

TEST(VectorTest, PopBack_Empty) {
  s21::vector<int> v;
  EXPECT_ANY_THROW(v.pop_back());
}

TEST(VectorTest, PopBack_NotEmpty) {
  s21::vector<int> v = {1, 2, 3, 4, 5};
  v.pop_back();
  EXPECT_EQ(v.size(), 4u);
}

TEST(VectorTest, Swap_NotEmpty) {
  s21::vector<int> v1 = {1, 2, 3};
  s21::vector<int> v2 = {4, 5, 6};

  v1.swap(v2);

  EXPECT_EQ(v1.size(), 3u);
  EXPECT_EQ(v2.size(), 3u);

  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v1[2], 6);

  EXPECT_EQ(v2[0], 1);
  EXPECT_EQ(v2[2], 3);
}

TEST(VectorTest, Swap_EmptyAndNotEmpty) {
  s21::vector<int> v1;
  s21::vector<int> v2 = {4, 5, 6};

  v1.swap(v2);

  EXPECT_EQ(v1.size(), 3u);
  EXPECT_EQ(v2.size(), 0u);

  EXPECT_EQ(v1[0], 4);
  EXPECT_EQ(v1[2], 6);
}

TEST(VectorTest, InsertMany) {
  s21::vector<int> vec = {1, 2, 3, 7, 8};
  s21::vector<int>::const_iterator pos = vec.begin() + 3;

  vec.insert_many(pos, 4, 5, 6);

  EXPECT_EQ(vec.size(), 8u);

  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
  EXPECT_EQ(vec[5], 6);
  EXPECT_EQ(vec[6], 7);
  EXPECT_EQ(vec[7], 8);
}

TEST(VectorTest, InsertManyBack) {
  s21::vector<int> vec = {1, 2, 3};

  vec.insert_many_back(4, 5, 6);

  EXPECT_EQ(vec.size(), 6u);

  EXPECT_EQ(vec[0], 1);
  EXPECT_EQ(vec[1], 2);
  EXPECT_EQ(vec[2], 3);
  EXPECT_EQ(vec[3], 4);
  EXPECT_EQ(vec[4], 5);
  EXPECT_EQ(vec[5], 6);
}