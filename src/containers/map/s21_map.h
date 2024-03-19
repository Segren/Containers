#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MAP_S21_MAP_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MAP_S21_MAP_H_

#include "../iterator/binary_tree_map_iterator.tpp"
#include "../tree/binary_tree.tpp"

namespace s21 {

template <typename Key, typename T>
class map : public BinaryTree<Key, T> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename BinaryTree<Key, T>::MapIterator;
  using const_iterator = typename BinaryTree<Key, T>::ConstMapIterator;
  using size_type = size_t;

  map() : BinaryTree<Key, T>(){};
  map(const std::initializer_list<value_type> &items);
  map(const map &other) : BinaryTree<Key, T>(other){};
  map(map &&other) noexcept : BinaryTree<Key, T>(std::move(other)){};
  map &operator=(map &&other) noexcept;
  map &operator=(const map &other);
  ~map() = default;

  iterator begin();
  iterator end();
  void merge(map &other);
  T &at(const Key &key);
  T &operator[](const Key &key);
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj);
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MAP_S21_MAP_H_
