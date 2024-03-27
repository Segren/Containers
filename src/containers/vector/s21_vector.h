#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_VECTOR_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_VECTOR_S21_VECTOR_H_

#include <algorithm>         // Для std::copy
#include <cstddef>           // Для size_t
#include <initializer_list>  // Для std::initializer_list
#include <limits>
#include <stdexcept>  // Для std::out_of_range

namespace s21 {

template <typename T>
class vector {
 public:
  // member types
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // functions;
  vector();
  explicit vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v) noexcept;
  ~vector();
  vector &operator=(vector &&v) noexcept;
  vector &operator=(const vector &v);

  // element access;
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  const_reference front() const;
  const_reference back() const;
  iterator data();

  // iterators
  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  // capacity
  bool empty() const;
  size_type size() const;
  size_type max_size() const;
  void reserve(size_type size);
  size_type capacity() const;
  void shrink_to_fit();

  // modifiers
  void clear();
  iterator insert(const_iterator pos, const_reference value);
  void erase(const_iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  // insert_many
  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  size_t _size;
  size_t _capacity;
  T *elements;
};
#include "s21_vector.tpp"

}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_VECTOR_S21_VECTOR_H_
