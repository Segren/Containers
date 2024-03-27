#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MULTISET_S21_MULTISET_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MULTISET_S21_MULTISET_H_

#include "../iterator/binary_tree_set_iterator.h"
#include "../tree/binary_tree.h"

namespace s21 {

template <typename Key>
class multiset : public BinaryTree<Key, Key> {
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
  multiset() : BinaryTree<key_type, key_type>(){};
  multiset(std::initializer_list<key_type> const &items);
  multiset(const multiset &ms) : BinaryTree<key_type, key_type>(ms){};
  multiset(multiset &&ms) noexcept
      : BinaryTree<key_type, key_type>(std::move(ms)){};
  ~multiset() = default;
  multiset &operator=(multiset &&ms) noexcept;
  multiset &operator=(const multiset &ms);

  // Iterators
  iterator begin();
  iterator end();

  // Capacity
  bool empty() { return this->Empty(); }
  size_type size() { return this->Size(); };
  size_type max_size() { return this->GetMaxSize(); }

  // Modifiers
  void clear() { BinaryTree<key_type, key_type>::Clear(); }
  std::pair<iterator, bool> insert(const key_type &key);
  void erase(iterator pos);
  void swap(multiset &other) { this->Swap(other); }
  void merge(multiset &other);
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

  // Lookup
  size_type count(const key_type &key);
  iterator find(const key_type &key) { return this->FindInSet(key); };
  bool contains(const key_type &key) { return this->Contains(key); }
  std::pair<iterator, iterator> equal_range(const Key &key);
  iterator lower_bound(const key_type &key);
  iterator upper_bound(const key_type &key);

 private:
  typename BinaryTree<Key, Key>::TreeNode *erase_helper(
      typename BinaryTree<Key, Key>::TreeNode *node, const Key &key);
  void count_helper(typename BinaryTree<Key, Key>::TreeNode *node,
                    const Key &key, size_type &count);
};

}  // namespace s21

#include "s21_multiset.tpp"

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MULTISET_S21_MULTISET_H_
