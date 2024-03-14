#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_BINARY_TREE_ITERATOR_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_BINARY_TREE_ITERATOR_H_

#include "../tree/binary_tree.h"

template <typename Key, typename Value>
class BinaryTree<Key, Value>::Iterator {
 public:
  Iterator();
  Iterator(TreeNode* node, TreeNode* prev_node = nullptr);
  iterator& operator++();
  iterator operator++(int);
  iterator& operator--();
  iterator operator--(int);
  reference operator*();
  bool operator==(const iterator& it);
  friend class BinaryTree<Key, Value>;
  bool operator!=(const iterator& it);

 protected:
  TreeNode* curr_node_;
  TreeNode* prev_node_;
  TreeNode* MoveForward(TreeNode* node);
  TreeNode* MoveBack(TreeNode* node);
};

template <typename Key, typename Value>
class BinaryTree<Key, Value>::ConstIterator : public Iterator {
 public:
  ConstIterator() : Iterator(){};
  const_reference operator*() const { return Iterator::operator*(); };
};

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_BINARY_TREE_ITERATOR_H_
