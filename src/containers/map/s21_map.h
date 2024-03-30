#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MAP_S21_MAP_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MAP_S21_MAP_H_

#include "../iterator/binary_tree_map_iterator.h"
#include "../tree/binary_tree.h"

namespace s21 {

template <typename Key, typename T>
class map : public BinaryTree<Key, T> {
  // Member type
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename BinaryTree<key_type, mapped_type>::MapIterator;
  using const_iterator =
      typename BinaryTree<key_type, mapped_type>::ConstMapIterator;
  using size_type = size_t;

  // Member functions
  map() : BinaryTree<key_type, mapped_type>(){};
  map(std::initializer_list<value_type> const &items);
  map(const map &m) : BinaryTree<key_type, mapped_type>(m){};
  map(map &&m) noexcept : BinaryTree<key_type, mapped_type>(std::move(m)){};
  ~map() = default;
  map &operator=(map &&m) noexcept;
  map &operator=(const map &m);

  // Element access
  mapped_type &at(const key_type &key);
  mapped_type &operator[](const key_type &key);

  // Iterators
  iterator begin();
  iterator end();

  // Capacity
  bool empty() { return this->Empty(); }
  size_type size() { return this->Size(); };
  size_type max_size() { return this->GetMaxSize(); }

  // Modifiers
  void clear() { BinaryTree<key_type, mapped_type>::Clear(); }
  std::pair<iterator, bool> insert(const key_type &key, mapped_type value);
  std::pair<iterator, bool> insert(std::pair<const key_type &, mapped_type>);
  void erase(iterator pos);
  void swap(map &other) { this->Swap(other); };
  void merge(map &other);
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj);
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);

  // Lookup
  bool contains(const Key &key) { return this->Contains(key); }
};

}  // namespace s21

#include "s21_map.tpp"

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MAP_S21_MAP_H_
