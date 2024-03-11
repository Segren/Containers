#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_ITERATOR_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_ITERATOR_H_

#include "const_iterator.h"

namespace s21 {

template <typename T>
class Iterator : public ConstIterator<T> {
 public:
  virtual ~Iterator() = default;

  using ConstIterator<T>::operator++;
  using ConstIterator<T>::operator--;

  virtual Iterator<T>& operator=(const Iterator<T>& other);
  virtual T& operator*() const override;
  virtual T* operator->() const override;

  virtual bool operator!=(const Iterator<T>& other) const override;
  virtual bool operator==(const Iterator<T>& other) const override;

  virtual Iterator<T> begin() const override;
  virtual Iterator<T> end() const override;

  void operator++() override { ConstIterator<T>::operator++(); }
  void operator--() override { ConstIterator<T>::operator--(); }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_ITERATOR_H_
