#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_S21_SET_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_S21_SET_H_

#include "../iterator/binary_tree_set_iterator.tpp"
#include "../tree/binary_tree.tpp"

namespace s21 {

template <typename Key>
class set : public BinaryTree<Key, Key> {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const Key &;
  using iterator = typename BinaryTree<key_type, key_type>::SetIterator;
  using const_iterator =
      typename BinaryTree<key_type, key_type>::ConstSetIterator;
  using size_type = size_t;

  set() : BinaryTree<key_type, key_type>(){};
  set(std::initializer_list<key_type> const &items);
  set(const set &other) : BinaryTree<key_type, key_type>(other){};
  set(set &&other) noexcept
      : BinaryTree<key_type, key_type>(std::move(other)){};
  set &operator=(set &&other) noexcept;
  set &operator=(const set &other);
  ~set() = default;

  iterator begin();
  iterator end();
  void merge(BinaryTree<key_type, key_type> &other);
  iterator find(const key_type &key) {
    return BinaryTree<key_type, key_type>::FindInSet(key);
  };
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_S21_SET_H_
