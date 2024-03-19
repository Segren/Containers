#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_S21_SET_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_S21_SET_H_

#include "../iterator/binary_tree_set_iterator.tpp"
#include "../tree/binary_tree.tpp"

namespace s21 {

template <typename Key>
class set : public BinaryTree<Key, Key> {
  // Member type
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename BinaryTree<key_type, key_type>::SetIterator;
  using const_iterator =
      typename BinaryTree<key_type, key_type>::ConstSetIterator;
  using size_type = size_t;

  // Member functions
  set() : BinaryTree<key_type, key_type>(){};
  set(std::initializer_list<key_type> const &items);
  set(const set &s) : BinaryTree<key_type, key_type>(s){};
  set(set &&s) noexcept : BinaryTree<key_type, key_type>(std::move(s)){};
  ~set() = default;
  set &operator=(set &&s) noexcept;
  set &operator=(const set &s);

  // Iterators
  iterator begin();
  iterator end();

  // Capacity
  bool empty() { return BinaryTree<key_type, key_type>::Empty(); }
  size_type size() { return BinaryTree<key_type, key_type>::Size(); };
  size_type max_size() { return BinaryTree<key_type, key_type>::GetMaxSize(); }

  // Modifiers
  void clear() { BinaryTree<key_type, key_type>::Clear(); }
  std::pair<iterator, bool> insert(const key_type &key);
  void erase(iterator pos);
  void swap(set &other) { BinaryTree<key_type, key_type>::Swap(other); }
  void merge(set &other);
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

  // Lookup
  iterator find(const key_type &key) {
    return BinaryTree<key_type, key_type>::FindInSet(key);
  };
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_S21_SET_H_
