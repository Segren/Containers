#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_BINARY_TREE_SET_ITERATOR_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_BINARY_TREE_SET_ITERATOR_TPP_

#include "binary_tree_set_iterator.h"

template <typename Key, typename T>
void BinaryTree<Key, T>::erase(set_iterator pos) {
  if (root_ == nullptr || pos.curr_node_ == nullptr) return;
  root_ = RecursiveDelete(root_, *pos);
}

template <typename Key, typename T>
typename BinaryTree<Key, T>::TreeNode *
BinaryTree<Key, T>::SetIterator::MoveForward(BinaryTree::TreeNode *node) {
  if (node->right_ != nullptr) {
    return GetMinNode(node->right_);
  }
  TreeNode *parent = node->parent_;
  while (parent != nullptr && node == parent->right_) {
    node = parent;
    parent = parent->parent_;
  }
  return parent;
}

template <typename Key, typename T>
typename BinaryTree<Key, T>::TreeNode *
BinaryTree<Key, T>::SetIterator::MoveBack(BinaryTree::TreeNode *node) {
  if (node->left_ != nullptr) {
    return GetMaxNode(node->left_);
  }
  TreeNode *parent = node->parent_;
  while (parent != nullptr && node == parent->left_) {
    node = parent;
    parent = node->parent_;
  }
  return parent;
}

template <typename Key, typename T>
BinaryTree<Key, T>::SetIterator::SetIterator()
    : curr_node_(nullptr), prev_node_(nullptr) {}

template <typename Key, typename T>
BinaryTree<Key, T>::SetIterator::SetIterator(BinaryTree::TreeNode *node,
                                             BinaryTree::TreeNode *prev_node)
    : curr_node_(node), prev_node_(prev_node) {}

template <typename Key, typename T>
typename BinaryTree<Key, T>::SetIterator &
BinaryTree<Key, T>::SetIterator::operator++() {
  TreeNode *tmp;
  if (curr_node_ != nullptr) {
    tmp = GetMaxNode(curr_node_);
  }
  curr_node_ = MoveForward(curr_node_);
  if (curr_node_ == nullptr) {
    prev_node_ = tmp;
  }
  return *this;
}

template <typename Key, typename T>
typename BinaryTree<Key, T>::SetIterator
BinaryTree<Key, T>::SetIterator::operator++(int) {
  SetIterator temp = *this;
  operator++();
  return temp;
}

template <typename Key, typename T>
typename BinaryTree<Key, T>::SetIterator &
BinaryTree<Key, T>::SetIterator::operator--() {
  if (curr_node_ == nullptr && prev_node_ != nullptr) {
    *this = prev_node_;
    return *this;
  }
  curr_node_ = MoveBack(curr_node_);
  return *this;
}

template <typename Key, typename T>
typename BinaryTree<Key, T>::SetIterator
BinaryTree<Key, T>::SetIterator::operator--(int) {
  SetIterator temp = *this;
  operator--();
  return temp;
}

template <typename Key, typename T>
T &BinaryTree<Key, T>::SetIterator::operator*() {
  if (curr_node_ == nullptr) {
    static T end_value{};
    return end_value;
  }
  return curr_node_->key_;
}

template <typename Key, typename T>
bool BinaryTree<Key, T>::SetIterator::operator==(
    const BinaryTree::SetIterator &it) {
  return curr_node_ == it.curr_node_;
}

template <typename Key, typename T>
bool BinaryTree<Key, T>::SetIterator::operator!=(
    const BinaryTree::SetIterator &it) {
  return curr_node_ != it.curr_node_;
}

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_BINARY_TREE_SET_ITERATOR_TPP_
