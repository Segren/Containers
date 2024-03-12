#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_BINARY_TREE_ITERATOR_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_BINARY_TREE_ITERATOR_TPP_

#include "binary_tree_iterator.h"

template <typename Key, typename Value>
void BinaryTree<Key, Value>::erase(iterator pos) {
  if (root_ == nullptr || pos.iter_node_ == nullptr) return;
  root_ = RecursiveDelete(root_, *pos);
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::TreeNode *
BinaryTree<Key, Value>::Iterator::MoveForward(BinaryTree::TreeNode *node) {
  if (node->right_ != nullptr) {
    return GetMin(node->right_);
  }
  TreeNode *parent = node->parent_;
  while (parent != nullptr && node == parent->right_) {
    node = parent;
    parent = parent->parent_;
  }
  return parent;
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::TreeNode *
BinaryTree<Key, Value>::Iterator::MoveBack(BinaryTree::TreeNode *node) {
  if (node->left_ != nullptr) {
    return GetMax(node->left_);
  }
  TreeNode *parent = node->parent_;
  while (parent != nullptr && node == parent->left_) {
    node = parent;
    parent = node->parent_;
  }
  return parent;
}

template <typename Key, typename Value>
BinaryTree<Key, Value>::Iterator::Iterator()
    : iter_node_(nullptr), iter_past_node_(nullptr) {}

template <typename Key, typename Value>
BinaryTree<Key, Value>::Iterator::Iterator(BinaryTree::TreeNode *node,
                                           BinaryTree::TreeNode *past_node)
    : iter_node_(node), iter_past_node_(past_node) {}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::Iterator &
BinaryTree<Key, Value>::Iterator::operator++() {
  TreeNode *tmp;
  if (iter_node_ != nullptr) {
    tmp = GetMax(iter_node_);
  }
  iter_node_ = MoveForward(iter_node_);
  if (iter_node_ == nullptr) {
    iter_past_node_ = tmp;
  }
  return *this;
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::Iterator
BinaryTree<Key, Value>::Iterator::operator++(int) {
  Iterator temp = *this;
  operator++();
  return temp;
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::Iterator &
BinaryTree<Key, Value>::Iterator::operator--() {
  if (iter_node_ == nullptr && iter_past_node_ != nullptr) {
    *this = iter_past_node_;
    return *this;
  }
  iter_node_ = MoveBack(iter_node_);
  return *this;
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::Iterator
BinaryTree<Key, Value>::Iterator::operator--(int) {
  Iterator temp = *this;
  operator--();
  return temp;
}

template <typename Key, typename Value>
Value &BinaryTree<Key, Value>::Iterator::operator*() {
  if (iter_node_ == nullptr) {
    static Value fake_value{};
    return fake_value;
  }
  return iter_node_->key_;
}

template <typename Key, typename Value>
bool BinaryTree<Key, Value>::Iterator::operator==(
    const BinaryTree::Iterator &it) {
  return iter_node_ == it.iter_node_;
}

template <typename Key, typename Value>
bool BinaryTree<Key, Value>::Iterator::operator!=(
    const BinaryTree::Iterator &it) {
  return iter_node_ != it.iter_node_;
}

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_BINARY_TREE_ITERATOR_TPP_
