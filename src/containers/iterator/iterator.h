#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_ITERATOR_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_ITERATOR_H_

#include "const_iterator.h"

namespace s21 {

template <typename T>
class Iterator {
 public:
  virtual ~Iterator() = default;

  virtual void operator++() = 0;
  virtual void operator--() = 0;

  virtual Iterator<T>& operator=(const Iterator<T>& other) = 0;
  virtual T& operator*() const = 0;
  virtual T* operator->() const = 0;

  virtual bool operator!=(const Iterator<T>& other) const = 0;
  virtual bool operator==(const Iterator<T>& other) const = 0;

  virtual Iterator<T> begin() const = 0;
  virtual Iterator<T> end() const = 0;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_ITERATOR_H_
