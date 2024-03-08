#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_S21_SET_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_S21_SET_H_

namespace s21 {

template <typename T>
class set {
 public:
  using key_type = T;
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = SetIterator<T>;
  using const_iterator = SetConstIterator<T>;
  using size_type = size_t;

  set();
  set(std::initializer_list<value_type> const &items);
  set(const set &s);
  set(set &&s);
  ~set();
  set &operator=(set &&s);
  set &operator=(set &s);

  iterator begin();
  iterator end();
  const_iterator begin();
  const_iterator end();

  bool empty();
  size_type size();
  size_type max_size();

  void clear();
  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void swap(set &other);
  void merge(set &other);

  iterator find(const_reference &key);
  bool contains(const_reference &key);
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_S21_SET_H_
