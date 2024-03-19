#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_S21_SET_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_S21_SET_TPP_

#include "s21_set.h"

namespace s21 {

template <typename Key>
set<Key>::set(const std::initializer_list<key_type> &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    insert(*i);
  }
}

template <typename Key>
set<Key> &set<Key>::operator=(set &&s) noexcept {
  if (this != &s) {
    BinaryTree<Key, Key>::operator=(std::move(s));
  }
  return *this;
}

template <typename Key>
set<Key> &set<Key>::operator=(const set &s) {
  if (this != &s) {
    BinaryTree<Key, Key>::operator=(s);
  }
  return *this;
}

template <typename Key>
template <class... Args>
std::vector<std::pair<typename set<Key>::iterator, bool>> set<Key>::insert_many(
    Args &&...args) {
  std::vector<std::pair<typename set<Key>::iterator, bool>> vec;
  for (const auto &arg : {args...}) {
    vec.push_back(insert(arg));
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
  if (this->root_ == nullptr) return begin();

  auto *last_node = this->GetMaxNode(this->root_);
  iterator last(nullptr, last_node);
  return last;
}

template <typename Key>
std::pair<typename BinaryTree<Key, Key>::SetIterator, bool> set<Key>::insert(
    const Key &key) {
  std::pair<iterator, bool> return_value;
  if (this->root_ == nullptr) {
    this->root_ = new typename BinaryTree<Key, Key>::TreeNode(key, key);
    return_value.first = iterator(this->root_);
    return_value.second = true;
  } else {
    bool check_insert = this->RecursiveInsert(this->root_, key, key);
    return_value.first = this->FindInSet(key);
    return_value.second = check_insert;
  }
  return return_value;
}

template <typename Key>
void set<Key>::erase(iterator pos) {
  if (this->root_ == nullptr || pos.curr_node_ == nullptr) return;
  this->root_ = this->RecursiveDelete(this->root_, *pos);
}

template <typename Key>
void set<Key>::merge(set &other) {
  BinaryTree const_tree(other);
  iterator it(this->GetMinNode(const_tree.root_));
  auto *last_node = this->GetMaxNode(const_tree.root_);
  iterator end(nullptr, last_node);

  for (; it != end; ++it) {
    std::pair<set<Key>::iterator, bool> pr = insert(*it);
    if (pr.second) {
      other.erase(pr.first);
    }
  }
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_SET_S21_SET_TPP_
