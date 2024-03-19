
#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MAP_S21_MAP_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MAP_S21_MAP_TPP_

#include "s21_map.h"

namespace s21 {

template <typename Key, typename T>
map<Key, T>::map(const std::initializer_list<value_type> &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    insert((*i).first, (*i).second);
  }
}

template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(map &&m) noexcept {
  if (this != &m) {
    BinaryTree<Key, T>::operator=(std::move(m));
  }
  return *this;
}

template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(const map &m) {
  if (this != &m) {
    BinaryTree<Key, T>::operator=(m);
  }
  return *this;
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const Key &key, const T &obj) {
  auto it = BinaryTree<Key, T>::FindInMap(key);
  if (it != this->end()) {
    erase(it);
    auto pr = insert(key, obj);
    pr.second = true;
    return pr;
  }
  return insert(key, obj);
}

template <typename Key, typename T>
template <class... Args>
std::vector<std::pair<typename map<Key, T>::iterator, bool>>
map<Key, T>::insert_many(Args &&...args) {
  std::vector<std::pair<typename map<Key, T>::iterator, bool>> vec;
  for (const auto &arg : {args...}) {
    vec.push_back(insert(arg));
  }
  return vec;
}

template <typename Key, typename T>
T &map<Key, T>::at(const Key &key) {
  iterator it = BinaryTree<Key, T>::FindInMap(key);
  if (it == nullptr)
    throw std::out_of_range(
        "Container does not have an element with the specified key");
  return it.return_value();
}

template <typename Key, typename T>
T &map<Key, T>::operator[](const Key &key) {
  iterator it = BinaryTree<Key, T>::FindInMap(key);
  if (it == nullptr) {
    it = insert({key, T()}).first;
  }
  return it.return_value();
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() {
  return
      typename BinaryTree<Key, T>::MapIterator(this->GetMinNode(this->root_));
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() {
  if (BinaryTree<Key, T>::root_ == nullptr) return begin();

  auto *last_node = BinaryTree<Key, T>::GetMaxNode(BinaryTree<Key, T>::root_);
  iterator last(nullptr, last_node);
  return last;
}

template <typename Key, typename T>
std::pair<typename BinaryTree<Key, T>::MapIterator, bool> map<Key, T>::insert(
    const Key &key, T value) {
  std::pair<iterator, bool> return_value;
  if (this->root_ == nullptr) {
    this->root_ = new typename BinaryTree<Key, T>::TreeNode(key, value);
    return_value.first = iterator(this->root_);
    return_value.second = true;
  } else {
    bool check_insert = this->RecursiveInsert(this->root_, key, value);
    return_value.first = this->FindInMap(key);
    return_value.second = check_insert;
  }
  return return_value;
}

template <typename Key, typename T>
std::pair<typename BinaryTree<Key, T>::MapIterator, bool> map<Key, T>::insert(
    std::pair<const Key &, T> pair) {
  std::pair<iterator, bool> return_value;
  if (this->root_ == nullptr) {
    this->root_ =
        new typename BinaryTree<Key, T>::TreeNode(pair.first, pair.second);
    return_value.first = iterator(this->root_);
    return_value.second = true;
  } else {
    bool check_insert =
        this->RecursiveInsert(this->root_, pair.first, pair.second);
    return_value.first = this->FindInMap(pair.first);
    return_value.second = check_insert;
  }
  return return_value;
}

template <typename Key, typename T>
void map<Key, T>::erase(iterator pos) {
  if (BinaryTree<Key, T>::root_ == nullptr || pos.curr_node_ == nullptr) return;
  BinaryTree<Key, T>::root_ = BinaryTree<Key, T>::RecursiveDelete(
      BinaryTree<Key, T>::root_, pos.return_key());
}

template <typename Key, typename T>
void map<Key, T>::merge(map &other) {
  map const_tree(other);
  iterator const_it = const_tree.begin();
  for (; const_it != const_tree.end(); ++const_it) {
    auto key = const_it.return_key();
    auto obj = const_it.return_value();
    std::pair<iterator, bool> pr = insert(key, obj);
    if (pr.second) other.erase(pr.first);
  }
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MAP_S21_MAP_TPP_
