
#include "array"
#include "test_runner.h"

TEST(ConstructorTest, DefaultConstructor) {
  s21::array<int, 5> arr;
  EXPECT_EQ(arr.size(), 5);
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 0);
  }
}

TEST(ConstructorTest, Initializer_list) {
  s21::array<int, 5> test_arr = {132, 6542, 453, 5344, 25};
  std::array<int, 5> arr = {132, 6542, 453, 5344, 25};
  EXPECT_EQ(arr.size(), 5);
  for (size_t i = 0; i < test_arr.size(); ++i) {
    EXPECT_EQ(arr[i], test_arr[i]);
  }
}
TEST(ConstructorTest, WrongInput) {
  EXPECT_ANY_THROW(({ s21::array<int, 1> arr{1, 2}; }));
}

TEST(ConstructorTest, CopyConstructor) {
  s21::array<int, 5> test_arr = {132, 6542, 453, 5344, 25};
  s21::array<int, 5> test_arr_{test_arr};
  for (int i = 0; i < 5; i++) {
    EXPECT_EQ(test_arr_[i], test_arr[i]);
  }
}

TEST(ConstructorTest, MoveConstructor) {
  s21::array<int, 5> test_arr = {1, 2, 3, 4, 5};
  s21::array<int, 5> test_arr_(std::move(test_arr));
  EXPECT_EQ(test_arr_.size(), 5);
  for (size_t i = 0; i < test_arr_.size(); ++i) {
    EXPECT_EQ(test_arr_[i], i + 1);
  }
  EXPECT_EQ(test_arr.size(), 0);
}

TEST(OperatorTest, CopyAssignmentOperator) {
  s21::array<int, 5> arr1;
  s21::array<int, 5> arr2 = {6, 7, 8, 9, 10};
  arr1 = arr2;
  for (size_t i = 0; i < arr1.size(); ++i) {
    EXPECT_EQ(arr1[i], arr2[i]);
  }
}

TEST(OperatorTest, MoveAssignmentOperator) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2 = {6, 7, 8, 9, 10};
  arr1 = std::move(arr2);
  for (size_t i = 0; i < arr1.size(); ++i) {
    EXPECT_EQ(arr1[i], i + 6);
  }
}

TEST(ArrayTest, OperatorBracket) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], i + 1);
  }
  arr[2] = 10;
  EXPECT_EQ(arr[2], 10);
}

TEST(ElementAccessTest, AtRightInput) {
  std::array<int, 2> arr{1, 2};
  s21::array<int, 2> test_arr{1, 2};
  EXPECT_EQ(arr.at(0), test_arr.at(0));
  EXPECT_EQ(arr.at(1), test_arr.at(1));
}

TEST(ElementAccessTest, AtRangeError) {
  s21::array<int, 2> test_arr{1, 2};
  EXPECT_THROW(test_arr.at(3), std::out_of_range);
  EXPECT_THROW(test_arr.at(-1), std::out_of_range);
  s21::array<int, 99> test_arr1{1, 2, 3, 325, 62, 234, 6435, 435};
  EXPECT_THROW(test_arr1.at(100), std::out_of_range);
}

TEST(ElementAccessTest, AtConstRightInput) {
  const std::array<int, 2> arr{1, 2};
  const s21::array<int, 2> test_arr{1, 2};
  EXPECT_EQ(arr.at(0), test_arr.at(0));
  EXPECT_EQ(arr.at(1), test_arr.at(1));
}

TEST(ElementAccessTest, AtConstRangeError) {
  const s21::array<int, 2> test_arr{1, 2};
  EXPECT_THROW(test_arr.at(3), std::out_of_range);
  EXPECT_THROW(test_arr.at(-1), std::out_of_range);
  const s21::array<int, 99> test_arr1{1, 2, 3, 325, 62, 234, 6435, 435};
  EXPECT_THROW(test_arr1.at(100), std::out_of_range);
}

TEST(ElementAccessTest, OperatorRightInput) {
  s21::array<int, 4> test_arr{1, 2, 1242, 2352};
  std::array<int, 4> arr{1, 2, 1242, 2352};
  for (std::size_t i = 0; i < 4; i++) EXPECT_EQ(test_arr[i], arr[i]);
}

TEST(ElementAccessTest, OperatorConstRightInput) {
  const s21::array<int, 4> test_arr{1, 2, 1242, 2352};
  const std::array<int, 4> arr{1, 2, 1242, 2352};
  for (std::size_t i = 0; i < 4; i++) EXPECT_EQ(test_arr[i], arr[i]);
}

TEST(ElementAccessTest, FrontRightInput) {
  s21::array<int, 4> test_arr{1, 2, 1242, 2352};
  std::array<int, 4> arr{1, 2, 1242, 2352};
  EXPECT_EQ(test_arr.front(), arr.front());
}

TEST(ElementAccessTest, BackRightInput) {
  s21::array<int, 4> test_arr1{1, 2, 1242, 2352};
  std::array<int, 4> arr1{1, 2, 1242, 2352};
  EXPECT_EQ(test_arr1.back(), arr1.back());
  s21::array<int, 10> test_arr2{1, 2, 1242, 2352};
  std::array<int, 10> arr2{1, 2, 1242, 2352};
  EXPECT_EQ(test_arr2.back(), arr2.back());
}

TEST(ElementAccessTest, DataRightInput) {
  s21::array<double, 10> test_arr{23.23, 4.123, 234.4564, 23.136652};
  std::array<double, 10> arr{23.23, 4.123, 234.4564, 23.136652};
  double* test_x;
  double* x;
  test_x = test_arr.data();
  x = arr.data();
  for (int i = 0; i < 10; i++) EXPECT_DOUBLE_EQ(test_x[i], x[i]);
}

TEST(ElementAccessTest, DataConstRightInput) {
  const s21::array<double, 10> test_arr{23.23, 4.123, 234.4564, 23.136652};
  const std::array<double, 10> arr{23.23, 4.123, 234.4564, 23.136652};
  const double* test_x;
  const double* x;
  test_x = test_arr.data();
  x = arr.data();
  for (int i = 0; i < 10; i++) EXPECT_DOUBLE_EQ(test_x[i], x[i]);
}

TEST(ElementAccessTest, DataZeroElem) {
  s21::array<double, 0> test_arr;
  double* test_x;
  test_x = test_arr.data();
  EXPECT_EQ(test_x, nullptr);
}

TEST(IteratorTest, BeginRightInput) {
  s21::array<double, 10> test_arr{23.23, 4.123, 234.4564, 23.136652};
  std::array<double, 10> arr{23.23, 4.123, 234.4564, 23.136652};
  double* test_x;
  double* x;
  test_x = test_arr.begin();
  x = arr.begin();
  for (int i = 0; i < 10; i++) EXPECT_DOUBLE_EQ(test_x[i], x[i]);
}

TEST(IteratorTest, BeginConstRightInput) {
  const s21::array<double, 10> test_arr{23.23, 4.123, 234.4564, 23.136652};
  const std::array<double, 10> arr{23.23, 4.123, 234.4564, 23.136652};
  const double* test_x;
  const double* x;
  test_x = test_arr.cbegin();
  x = arr.cbegin();
  for (int i = 0; i < 10; i++) EXPECT_DOUBLE_EQ(test_x[i], x[i]);
}

TEST(IteratorTest, BeginZeroElem) {
  s21::array<double, 0> test_arr;
  double* test_x;
  test_x = test_arr.begin();
  EXPECT_EQ(test_x, nullptr);
}

TEST(IteratorTest, EndRightInput) {
  s21::array<double, 10> test_arr{23.23, 4.123, 234.4564, 23.136652};
  double* test_x;
  double* x;
  test_x = test_arr.end();
  x = test_arr.begin();
  EXPECT_EQ(test_x, x + 10);
}

TEST(IteratorTest, EndConstRightInput) {
  const s21::array<double, 9> test_arr{23.23, 4.123, 234.4564, 23.136652};
  const double* test_x;
  const double* x;
  test_x = test_arr.cend();
  x = test_arr.cbegin();
  EXPECT_EQ(test_x, x + 9);
}

TEST(IteratorTest, EndZeroElem) {
  s21::array<double, 0> test_arr;
  double* test_x;
  double* x;
  test_x = test_arr.end();
  x = test_arr.begin();
  EXPECT_EQ(test_x, x);
}

TEST(CapacityTest, EmptyArray) {
  s21::array<double, 0> test_arr;
  EXPECT_EQ(test_arr.empty(), true);
}

TEST(CapacityTest, NoEmptyArray) {
  s21::array<double, 10> test_arr{1, 543, 2, 3};
  EXPECT_EQ(test_arr.empty(), false);
}

TEST(CapacityTest, SizeTest) {
  std::array<double, 10> arr{1, 543325, 22342, 2323};
  s21::array<double, 10> test_arr{1, 543, 2, 31231};
  EXPECT_EQ(test_arr.size(), arr.size());
}

TEST(CapacityTest, ZeroSizeTest) {
  std::array<double, 0> arr;
  s21::array<double, 0> test_arr;
  EXPECT_EQ(test_arr.size(), arr.size());
}

TEST(CapacityTest, MaxSizeTest) {
  std::array<double, 10> arr{1, 543325, 22342, 2323};
  s21::array<double, 10> test_arr{1, 543, 2, 31231};
  EXPECT_EQ(test_arr.max_size(), arr.max_size());
}

TEST(CapacityTest, ZeroMaxSizeTest) {
  std::array<double, 0> arr;
  s21::array<double, 0> test_arr;
  EXPECT_EQ(test_arr.max_size(), arr.max_size());
}

TEST(ModifiersTest, FillTest) {
  std::array<double, 10> arr{1, 2, 3, 24, 45};
  s21::array<double, 10> test_arr{435, 34};
  arr.fill(-1);
  test_arr.fill(-1);
  for (int i = 0; i < 10; i++) EXPECT_EQ(test_arr.at(i), arr.at(i));
}

TEST(ModifiersTest, FillTest1) {
  s21::array<double, 10> test_arr{435, 34};
  test_arr.fill(2436342.2435);
  for (int i = 0; i < 10; i++) EXPECT_EQ(test_arr.at(i), 2436342.2435);
}

TEST(ModifiersTest, FillTest2) {
  std::array<double, 0> arr;
  s21::array<double, 0> test_arr;
  arr.fill(-1);
  test_arr.fill(-1);
  for (int i = 0; i < 0; i++) EXPECT_EQ(test_arr.at(i), arr.at(i));
}

TEST(ModifiersTest, DiffFillTest) {
  std::array<double, 10> arr{1, 2, 3, 24, 45};
  s21::array<double, 10> test_arr{435, 34};
  arr.fill(-1);
  test_arr.fill(32542);
  for (int i = 0; i < 10; i++) EXPECT_NE(test_arr.at(i), arr.at(i));
}

TEST(ModifiersTest, SwapTest1) {
  s21::array<double, 10> arr;
  s21::array<double, 10> test_arr;
  arr.fill(-1);
  test_arr.fill(32542);
  for (int i = 0; i < 10; i++) EXPECT_EQ(test_arr.at(i), 32542);
  for (int i = 0; i < 10; i++) EXPECT_EQ(arr.at(i), -1);
  test_arr.swap(arr);
  for (int i = 0; i < 10; i++) EXPECT_EQ(arr.at(i), 32542);
  for (int i = 0; i < 10; i++) EXPECT_EQ(test_arr.at(i), -1);
}

TEST(ModifiersTest, SwapTest2) {
  s21::array<double, 10> test_arr1{21354, 23, 123.1223, 342.123};
  s21::array<double, 10> test_arr2{7.354, 346.434, 6765433, 543};
  std::array<double, 10> arr1{21354, 23, 123.1223, 342.123};
  std::array<double, 10> arr2{7.354, 346.434, 6765433, 543};
  for (int i = 0; i < 10; i++) EXPECT_EQ(test_arr1.at(i), arr1.at(i));
  for (int i = 0; i < 10; i++) EXPECT_EQ(test_arr2.at(i), arr2.at(i));
  test_arr1.swap(test_arr2);
  arr1.swap(arr2);
  for (int i = 0; i < 10; i++) EXPECT_EQ(test_arr1.at(i), arr1.at(i));
  for (int i = 0; i < 10; i++) EXPECT_EQ(test_arr2.at(i), arr2.at(i));
}
