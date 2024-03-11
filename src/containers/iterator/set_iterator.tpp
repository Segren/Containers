#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_SET_ITERATOR_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_SET_ITERATOR_TPP_

#include "../tree/binary_tree.h"
#include "iterator.h"

namespace s21 {

template <typename T>
class SetIterator : public Iterator<T> {
 public:
  SetIterator();

  virtual void operator++();
  virtual void operator--() override;
  virtual T &operator*() const override;
  virtual T *operator->() const override;

  virtual bool operator!=(const Iterator<T> &other) const override;
  virtual bool operator==(const Iterator<T> &other) const override;

 private:
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_SET_ITERATOR_TPP_
