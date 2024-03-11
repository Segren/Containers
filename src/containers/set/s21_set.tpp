#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_S21_SET_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_S21_SET_TPP_

#include "s21_set.h"

namespace s21 {

template <typename T>
set<T>::set() : tree() {}

template <typename T>
set<T>::set(std::initializer_list<value_type> const &items) : tree() {
  for (const auto &item : items) {
    tree.insert(item, nullptr);
  }
}

template <typename T>
set<T>::set(const set &s) : tree(s.tree) {}

template <typename T>
set<T>::set(set &&s) : tree(std::move(s.tree)) {}

template <typename T>
set<T>::~set() {}

template <typename T>
set<T> &set<T>::operator=(set &&s) {
  if (this != &s) {
    tree = std::move(s.tree);
  }
  return *this;
}

template <typename T>
set<T> &set<T>::operator=(set &s) {
  if (this != &s) {
    tree = s.tree;
  }
  return *this;
}

template <typename T>
typename set<T>::iterator set<T>::begin() {
  return iterator(tree.minValueNode(tree.getRoot()));
}

template <typename T>
typename set<T>::iterator set<T>::end() {
  return iterator(nullptr);
}

template <typename T>
typename set<T>::const_iterator set<T>::cbegin() {
  return const_iterator(tree.minValueNode(tree.getRoot()));
}

template <typename T>
typename set<T>::const_iterator set<T>::cend() {
  return const_iterator(nullptr);
}

template <typename T>
bool set<T>::empty() {
  return tree.empty();
}

template <typename T>
typename set<T>::size_type set<T>::size() {
  return tree.size();
}

template <typename T>
typename set<T>::size_type set<T>::max_size() {
  return tree.maxSize();
}

template <typename T>
void set<T>::clear() {
  tree.clear();
}

template <typename T>
std::pair<typename set<T>::iterator, bool> set<T>::insert(
    const value_type &value) {
  TreeNode<key_type, nullptr_t> *insertedNode = tree.insert(value, nullptr);
  return std::make_pair(iterator(insertedNode), insertedNode != nullptr);
}

template <typename T>
void set<T>::erase(iterator pos) {
  tree.remove(pos.getCurrentNode());
}

template <typename T>
void set<T>::swap(set &other) {
  tree.swap(other.tree);
}

template <typename T>
void set<T>::merge(set &other) {
  // todo realize it
}

template <typename T>
typename set<T>::iterator set<T>::find(const_reference &key) {
  TreeNode<key_type, nullptr_t> *node = tree.find(key);
  return iterator(node);
}

template <typename T>
bool set<T>::contains(const_reference &key) {
  return tree.find(key) != nullptr;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_S21_SET_TPP_
