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
  using iterator = typename BinaryTree<key_type, mapped_type>::MapIterator;
  using const_iterator =
      typename BinaryTree<key_type, mapped_type>::ConstMapIterator;
  using size_type = size_t;

  map() : BinaryTree<key_type, mapped_type>(){};
  map(const std::initializer_list<value_type> &items);
  map(const map &other) : BinaryTree<key_type, mapped_type>(other){};
  map(map &&other) noexcept
      : BinaryTree<key_type, mapped_type>(std::move(other)){};
  map &operator=(map &&other) noexcept;
  map &operator=(const map &other);
  ~map() = default;

  iterator begin();
  iterator end();
  void merge(map &other);
  mapped_type &at(const key_type &key);
  mapped_type &operator[](const key_type &key);
  std::pair<iterator, bool> insert_or_assign(const key_type &key,
                                             const mapped_type &obj);
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MAP_S21_MAP_H_
