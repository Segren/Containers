#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_BINARY_TREE_SET_ITERATOR_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_BINARY_TREE_SET_ITERATOR_H_

#include "../tree/binary_tree.h"

template <typename Key, typename Value>
class BinaryTree<Key, Value>::SetIterator {
 public:
  SetIterator();
  SetIterator(TreeNode* node, TreeNode* prev_node = nullptr);
  set_iterator& operator++();
  set_iterator operator++(int);
  set_iterator& operator--();
  set_iterator operator--(int);
  reference operator*();
  bool operator==(const set_iterator& it);
  bool operator!=(const set_iterator& it);

  friend class BinaryTree<Key, Value>;

 protected:
  TreeNode* curr_node_;
  TreeNode* prev_node_;
  TreeNode* MoveForward(TreeNode* node);
  TreeNode* MoveBack(TreeNode* node);
};

template <typename Key, typename Value>
class BinaryTree<Key, Value>::ConstSetIterator : public SetIterator {
 public:
  ConstSetIterator() : SetIterator(){};
  const_reference operator*() const { return SetIterator::operator*(); };
};

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_BINARY_TREE_SET_ITERATOR_H_
