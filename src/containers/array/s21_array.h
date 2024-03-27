#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ARRAY_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ARRAY_S21_ARRAY_H_

#include <iostream>

namespace s21 {
template <typename T, std::size_t amount>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const value_type &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a) noexcept;
  ~array();

  // Операторы перегрузки
  array &operator=(array &&a) noexcept;  // Перемещение
  array &operator=(const array &a);      // Копирование

  // Доступ к элементам массива
  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  const_reference front();
  const_reference back();

  T *data();
  iterator begin() noexcept;
  iterator end() noexcept;

  const T *data() const;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  bool empty();
  size_type size();
  size_type max_size();

  void swap(array &other);
  void fill(const_reference value);

 private:
  size_type amount_;
  value_type *array_;
};

}  // namespace s21
#include "s21_array.tpp"
#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ARRAY_S21_ARRAY_H_
