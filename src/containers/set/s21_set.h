#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_S21_SET_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_S21_SET_H_

#include "../iterator/binary_tree_iterator.tpp"
#include "../tree/binary_tree.tpp"

namespace s21 {

template <typename Key>
class set : public BinaryTree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const Key &;
  using iterator = typename BinaryTree<Key, Key>::Iterator;
  using const_iterator = typename BinaryTree<Key, Key>::ConstIterator;
  using size_type = size_t;

  set() : BinaryTree<Key, Key>(){};
  set(std::initializer_list<value_type> const &items);
  set(const set &other) : BinaryTree<Key, Key>(other){};
  set(set &&other) noexcept : BinaryTree<Key, Key>(std::move(other)){};
  set &operator=(set &&other) noexcept;
  set &operator=(const set &other);
  ~set() = default;

  iterator find(const Key &key) { return BinaryTree<Key, Key>::Find(key); };
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_S21_SET_H_
