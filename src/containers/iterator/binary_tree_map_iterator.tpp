#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_BINARY_TREE_MAP_ITERATOR_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_BINARY_TREE_MAP_ITERATOR_TPP_

#include "binary_tree_map_iterator.h"

template <typename Key, typename T>
void BinaryTree<Key, T>::erase(map_iterator pos) {
  if (BinaryTree<Key, T>::root_ == nullptr || pos.curr_node_ == nullptr) return;
  BinaryTree<Key, T>::root_ = BinaryTree<Key, T>::RecursiveDelete(
      BinaryTree<Key, T>::root_, pos.return_key());
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::TreeNode *
BinaryTree<Key, Value>::MapIterator::MoveForward(BinaryTree::TreeNode *node) {
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

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::TreeNode *
BinaryTree<Key, Value>::MapIterator::MoveBack(BinaryTree::TreeNode *node) {
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

template <typename Key, typename Value>
BinaryTree<Key, Value>::MapIterator::MapIterator()
    : curr_node_(nullptr), prev_node_(nullptr) {}

template <typename Key, typename Value>
BinaryTree<Key, Value>::MapIterator::MapIterator(
    BinaryTree::TreeNode *node, BinaryTree::TreeNode *prev_node)
    : curr_node_(node), prev_node_(prev_node) {}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::MapIterator &
BinaryTree<Key, Value>::MapIterator::operator++() {
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

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::MapIterator
BinaryTree<Key, Value>::MapIterator::operator++(int) {
  SetIterator temp = *this;
  operator++();
  return temp;
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::MapIterator &
BinaryTree<Key, Value>::MapIterator::operator--() {
  if (curr_node_ == nullptr && prev_node_ != nullptr) {
    *this = prev_node_;
    return *this;
  }
  curr_node_ = MoveBack(curr_node_);
  return *this;
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::MapIterator
BinaryTree<Key, Value>::MapIterator::operator--(int) {
  SetIterator temp = *this;
  operator--();
  return temp;
}

template <typename Key, typename Value>
std::pair<const Key, Value> BinaryTree<Key, Value>::MapIterator::operator*() {
  if (curr_node_ == nullptr) {
    return std::make_pair(Key(), Value());
  }
  return std::make_pair(curr_node_->key_, curr_node_->value_);
}

template <typename Key, typename Value>
bool BinaryTree<Key, Value>::MapIterator::operator==(
    const BinaryTree::MapIterator &it) {
  return curr_node_ == it.curr_node_;
}

template <typename Key, typename Value>
bool BinaryTree<Key, Value>::MapIterator::operator!=(
    const BinaryTree::MapIterator &it) {
  return curr_node_ != it.curr_node_;
}

template <typename Key, typename T>
T &BinaryTree<Key, T>::MapIterator::return_value() {
  if (BinaryTree<Key, T>::MapIterator::curr_node_ == nullptr) {
    static T end_value{};
    return end_value;
  }
  return BinaryTree<Key, T>::MapIterator::curr_node_->value_;
}

template <typename Key, typename T>
Key &BinaryTree<Key, T>::MapIterator::return_key() {
  if (BinaryTree<Key, T>::MapIterator::curr_node_ == nullptr) {
    static Key end_key{};
    return end_key;
  }
  return BinaryTree<Key, T>::MapIterator::curr_node_->key_;
}

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_BINARY_TREE_MAP_ITERATOR_TPP_
