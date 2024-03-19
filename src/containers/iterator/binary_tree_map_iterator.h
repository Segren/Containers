#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_BINARY_TREE_MAP_ITERATOR_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_BINARY_TREE_MAP_ITERATOR_H_

#include "../tree/binary_tree.h"

template <typename Key, typename Value>
class BinaryTree<Key, Value>::MapIterator {
 public:
  MapIterator();
  MapIterator(TreeNode* node, TreeNode* prev_node = nullptr);
  map_iterator& operator++();
  map_iterator operator++(int);
  map_iterator& operator--();
  map_iterator operator--(int);
  std::pair<const key_type, value_type> operator*();
  bool operator==(const map_iterator& it);
  bool operator!=(const map_iterator& it);
  value_type& return_value();
  key_type& return_key();

  friend class BinaryTree<key_type, value_type>;

  TreeNode* curr_node_;
  TreeNode* prev_node_;
  TreeNode* MoveForward(TreeNode* node);
  TreeNode* MoveBack(TreeNode* node);
};

template <typename key_type, typename value_type>
class BinaryTree<key_type, value_type>::ConstMapIterator : public MapIterator {
 public:
  ConstMapIterator() : MapIterator(){};
  const_map_reference operator*() const { return MapIterator::operator*(); };
};

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_BINARY_TREE_MAP_ITERATOR_H_