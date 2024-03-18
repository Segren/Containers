
#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MAP_S21_MAP_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MAP_S21_MAP_TPP_

#include "s21_map.h"

namespace s21 {

template <typename Key, typename T>
map<Key, T>::map(const std::initializer_list<value_type> &items) {
  for (auto i = items.begin(); i != items.end(); ++i) {
    BinaryTree<Key, T>::insert((*i).first, (*i).second);
  }
}

template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(map &&other) noexcept {
  if (this != &other) {
    BinaryTree<Key, T>::operator=(std::move(other));
  }
  return *this;
}

template <typename Key, typename T>
map<Key, T> &map<Key, T>::operator=(const map &other) {
  if (this != &other) {
    BinaryTree<Key, T>::operator=(other);
  }
  return *this;
}

// template <typename Key, typename T>
// std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
//     const value_type &value) {
//   return insert(value.first, value.second);
// }

// template <typename Key, typename T>
// std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
//     const Key &key, const T &obj) {
//   std::pair<iterator, bool> return_value;
//   if (BinaryTree<Key, T>::root_ == nullptr) {
//     BinaryTree<Key, T>::root_ =
//         new typename BinaryTree<Key, T>::TreeNode(key, obj);
//     return_value.first = iterator(BinaryTree<Key, T>::root_);
//     return_value.second = true;
//   } else {
//     bool check_insert = BinaryTree<Key, T>::RecursiveInsert(
//         BinaryTree<Key, T>::root_, key, obj);
//     return_value.first = find(key);
//     return_value.second = check_insert;
//   }
//   return return_value;
// }

// template <typename Key, typename T>
// typename map<Key, T>::value_type &map<Key, T>::MapIterator::operator*() {
//   if (BinaryTree<Key, T>::SetIterator::curr_node_ == nullptr) {
//     static value_type end_value{};
//     return end_value;
//   }
//   std::pair<const key_type, mapped_type> pr =
//       std::make_pair(BinaryTree<Key, T>::SetIterator::curr_node_->key_,
//                      BinaryTree<Key, T>::SetIterator::curr_node_->value_);
//   std::pair<const key_type, mapped_type> &ref = pr;
//   return ref;
// }
//
// template <typename Key, typename T>
// T &map<Key, T>::set_iterator::return_value() {
//   if (BinaryTree<Key, T>::MapIterator::curr_node_ == nullptr) {
//     static T end_value{};
//     return end_value;
//   }
//   return BinaryTree<Key, T>::MapIterator::curr_node_->value_;
// }

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const Key &key, const T &obj) {
  auto it = find(key);
  if (it != this->end()) {
    erase(it);
    auto pr = insert(key, obj);
    pr.second = false;
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
  auto it = find(key);
  if (it == nullptr)
    throw std::out_of_range(
        "Container does not have an element with the specified key");
  return it.return_value();
}

template <typename Key, typename T>
T &map<Key, T>::operator[](const Key &key) {
  auto it = find(key);
  if (it == nullptr) {
    auto pr = insert(std::make_pair(key, T()));
    it = pr.first;
  }
  return it.return_value();
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() {
  return typename BinaryTree<Key, T>::MapIterator(this->GetMin(this->root_));
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() {
  if (BinaryTree<Key, T>::root_ == nullptr) return begin();

  auto *last_node = BinaryTree<Key, T>::GetMax(BinaryTree<Key, T>::root_);
  iterator last(nullptr, last_node);
  return last;
}
//
// template <typename Key, typename T>
// typename map<Key, T>::const_set_iterator map<Key, T>::cbegin() const {
//   return map<Key, T>::ConstMapIterator(
//       BinaryTree<Key, T>::GetMin(BinaryTree<Key, T>::root_));
// }
//
// template <typename Key, typename T>
// typename map<Key, T>::const_set_iterator map<Key, T>::cend() const {
//   if (BinaryTree<Key, T>::root_ == nullptr) return cbegin();
//
//   const_set_iterator test(nullptr);
//   return test;
// }

template <typename Key, typename T>
void map<Key, T>::merge(map &other) {
  map const_tree(other);
  iterator const_it = const_tree.begin();
  for (; const_it != const_tree.end(); ++const_it) {
    auto key = (*const_it).first;
    auto obj = (*const_it).second;
    std::pair<iterator, bool> pr = insert(key, obj);
    if (pr.second) other.erase(pr.first);
  }
}

// template <typename Key, typename T>
// void map<Key, T>::erase(map::iterator pos) {
//   if (BinaryTree<Key, T>::root_ == nullptr || pos.curr_node_ == nullptr)
//   return; BinaryTree<Key, T>::root_ = BinaryTree<Key, T>::RecursiveDelete(
//       BinaryTree<Key, T>::root_, (*pos).first);
// }

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MAP_S21_MAP_TPP_
