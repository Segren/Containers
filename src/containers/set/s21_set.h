#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_S21_SET_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_S21_SET_H_

namespace s21 {

template <typename T>
class set {
 public:
  using key_type = T;
  using value_type = T;
  using reference = value_type&;
  using const_reference = const value_type&;
  //using iterator = SetIterator<T>;
  //using const_iterator = SetConstIterator<T>;
  using size_type = size_t;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_S21_SET_H_
