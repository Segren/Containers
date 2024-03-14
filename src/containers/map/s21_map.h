#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MAP_S21_MAP_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MAP_S21_MAP_H_

#include "../tree/binary_tree.h"

namespace s21 {

template <typename Key, typename T>
class map : public BinaryTree<Key, T> {
 public:
  class MapIterator;
  class ConstMapIterator;

  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = MapIterator;
  using const_iterator = ConstMapIterator;
  using size_type = size_t;

  map() : BinaryTree<Key, T>(){};
  map(std::initializer_list<value_type> const &items);
  map(const map &other) : BinaryTree<Key, T>(other){};
  map(map &&other) noexcept : BinaryTree<Key, T>(std::move(other)){};
  map &operator=(map &&other) noexcept;
  map &operator=(const map &other);
  ~map() = default;

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;
  void merge(map &other);

  class MapIterator : public BinaryTree<Key, T>::Iterator {
   public:
    friend class map;
    MapIterator() : BinaryTree<Key, T>::Iterator(){};
    MapIterator(typename BinaryTree<Key, T>::TreeNode *node,
                typename BinaryTree<Key, T>::TreeNode *past_node = nullptr)
        : BinaryTree<Key, T>::Iterator(node, past_node = nullptr){};
    value_type &operator*();

   protected:
    T &return_value();
  };

  class ConstMapIterator : public MapIterator {
   public:
    friend class map;
    ConstMapIterator() : MapIterator(){};
    ConstMapIterator(typename BinaryTree<Key, T>::TreeNode *node,
                     typename BinaryTree<Key, T>::TreeNode *past_node = nullptr)
        : MapIterator(node, past_node = nullptr){};
    const_reference operator*() const { return MapIterator::operator*(); };
  };

  T &at(const Key &key);
  T &operator[](const Key &key);
  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const Key &key, const T &obj);
  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj);
  template <class... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args);
  void erase(iterator pos);

 private:
  iterator find(const Key &key);
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MAP_S21_MAP_H_
