#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_BINARY_TREE_SET_ITERATOR_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_BINARY_TREE_SET_ITERATOR_TPP_

#include "binary_tree_set_iterator.h"

template <typename Key, typename Value>
void BinaryTree<Key, Value>::erase(set_iterator pos) {
  if (root_ == nullptr || pos.curr_node_ == nullptr) return;
  root_ = recursiveDelete(root_, *pos);
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::TreeNode *
BinaryTree<Key, Value>::SetIterator::MoveForward(BinaryTree::TreeNode *node) {
  if (node->right_ != nullptr) {
    return getMinNode(node->right_);
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
BinaryTree<Key, Value>::SetIterator::MoveBack(BinaryTree::TreeNode *node) {
  if (node->left_ != nullptr) {
    return getMaxNode(node->left_);
  }
  TreeNode *parent = node->parent_;
  while (parent != nullptr && node == parent->left_) {
    node = parent;
    parent = node->parent_;
  }
  return parent;
}

template <typename Key, typename Value>
BinaryTree<Key, Value>::SetIterator::SetIterator()
    : curr_node_(nullptr), prev_node_(nullptr) {}

template <typename Key, typename Value>
BinaryTree<Key, Value>::SetIterator::SetIterator(
    BinaryTree::TreeNode *node, BinaryTree::TreeNode *prev_node)
    : curr_node_(node), prev_node_(prev_node) {}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::SetIterator &
BinaryTree<Key, Value>::SetIterator::operator++() {
  TreeNode *tmp;
  if (curr_node_ != nullptr) {
    tmp = getMaxNode(curr_node_);
  }
  curr_node_ = MoveForward(curr_node_);
  if (curr_node_ == nullptr) {
    prev_node_ = tmp;
  }
  return *this;
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::SetIterator
BinaryTree<Key, Value>::SetIterator::operator++(int) {
  SetIterator temp = *this;
  operator++();
  return temp;
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::SetIterator &
BinaryTree<Key, Value>::SetIterator::operator--() {
  if (curr_node_ == nullptr && prev_node_ != nullptr) {
    *this = prev_node_;
    return *this;
  }
  curr_node_ = MoveBack(curr_node_);
  return *this;
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::SetIterator
BinaryTree<Key, Value>::SetIterator::operator--(int) {
  SetIterator temp = *this;
  operator--();
  return temp;
}

template <typename Key, typename Value>
Value &BinaryTree<Key, Value>::SetIterator::operator*() {
  if (curr_node_ == nullptr) {
    static Value end_value{};
    return end_value;
  }
  return curr_node_->key_;
}

template <typename Key, typename Value>
bool BinaryTree<Key, Value>::SetIterator::operator==(
    const BinaryTree::SetIterator &it) {
  return curr_node_ == it.curr_node_;
}

template <typename Key, typename Value>
bool BinaryTree<Key, Value>::SetIterator::operator!=(
    const BinaryTree::SetIterator &it) {
  return curr_node_ != it.curr_node_;
}

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_BINARY_TREE_SET_ITERATOR_TPP_
