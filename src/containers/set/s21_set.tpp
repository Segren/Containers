#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_S21_SET_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_S21_SET_TPP_

#include "s21_set.h"

namespace s21 {

template <typename Key>
set<Key>::set(const std::initializer_list<value_type> &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    BinaryTree<Key, Key>::insert(*i);
  }
}

template <typename Key>
set<Key> &set<Key>::operator=(set &&other) noexcept {
  if (this != &other) {
    BinaryTree<Key, Key>::operator=(std::move(other));
  }
  return *this;
}

template <typename Key>
set<Key> &set<Key>::operator=(const set &other) {
  if (this != &other) {
    BinaryTree<Key, Key>::operator=(other);
  }
  return *this;
}

template <typename Key>
template <class... Args>
std::vector<std::pair<typename set<Key>::iterator, bool>> set<Key>::insert_many(
    Args &&...args) {
  std::vector<std::pair<typename set<Key>::iterator, bool>> vec;
  for (const auto &arg : {args...}) {
    vec.push_back(BinaryTree<Key, Key>::insert(arg));
  }
  return vec;
}

template <typename Key>
typename BinaryTree<Key, Key>::SetIterator set<Key>::begin() {
  return
      typename BinaryTree<Key, Key>::SetIterator(this->GetMinNode(this->root_));
}

template <typename Key>
typename set<Key>::iterator set<Key>::end() {
  if (BinaryTree<Key, Key>::root_ == nullptr) return begin();

  auto *last_node =
      BinaryTree<Key, Key>::GetMaxNode(BinaryTree<Key, Key>::root_);
  iterator last(nullptr, last_node);
  return last;
}

template <typename Key>
void set<Key>::merge(BinaryTree<Key, Key> &other) {
  BinaryTree const_tree(other);
  iterator it(BinaryTree<Key, Key>::GetMinNode(const_tree.root_));
  auto *last_node = BinaryTree<Key, Key>::GetMaxNode(const_tree.root_);
  iterator end(nullptr, last_node);

  for (; it != end; ++it) {
    std::pair<set<Key>::iterator, bool> pr = BinaryTree<Key, Key>::insert(*it);
    if (pr.second) other.erase(pr.first);
  }
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_S21_SET_TPP_
