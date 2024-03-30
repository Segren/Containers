#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_BINARY_TREE_SET_ITERATOR_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_BINARY_TREE_SET_ITERATOR_H_

#include "../tree/binary_tree.h"

template <typename Key, typename Value>
class BinaryTree<Key, Value>::SetIterator {
 public:
  SetIterator();
  SetIterator(TreeNode* node, TreeNode* prev_node = nullptr);
  reference operator*();
  set_iterator& operator++();
  set_iterator operator++(int);
  set_iterator& operator--();
  set_iterator operator--(int);
  bool operator==(const set_iterator& it);
  bool operator!=(const set_iterator& it);

  friend class BinaryTree<key_type, value_type>;

  TreeNode* curr_node_;
  TreeNode* prev_node_;
  TreeNode* MoveToNext(TreeNode* node);
  TreeNode* MoveToPrev(TreeNode* node);
};

template <typename key_type, typename value_type>
class BinaryTree<key_type, value_type>::ConstSetIterator : public SetIterator {
 public:
  ConstSetIterator() : SetIterator(){};
  const_reference operator*() const { return SetIterator::operator*(); };
};

#include "binary_tree_set_iterator.tpp"

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_BINARY_TREE_SET_ITERATOR_H_
