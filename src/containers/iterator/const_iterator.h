#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_CONST_ITERATOR_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_CONST_ITERATOR_H_

namespace s21 {

template <typename T>
class ConstIterator {
 public:
  virtual ~ConstIterator() = default;

  virtual void operator++() = 0;
  virtual void operator--() = 0;

  virtual ConstIterator<T>& operator=(const ConstIterator<T>& other) = 0;
  virtual T& operator*() const = 0;
  virtual T* operator->() const = 0;

  virtual bool operator!=(const ConstIterator<T>& other) const = 0;
  virtual bool operator==(const ConstIterator<T>& other) const = 0;

  virtual ConstIterator<T> begin() const = 0;
  virtual ConstIterator<T> end() const = 0;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_CONST_ITERATOR_H_
