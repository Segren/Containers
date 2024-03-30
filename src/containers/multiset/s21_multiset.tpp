#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MULTISET_S21_MULTISET_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MULTISET_S21_MULTISET_TPP_

#include "s21_multiset.h"

namespace s21 {

template <typename Key>
multiset<Key>::multiset(std::initializer_list<key_type> const& items) {
  for (const auto& item : items) {
    insert(item);
  }
}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(multiset&& ms) noexcept {
  if (this != &ms) {
    BinaryTree<Key, Key>::operator=(std::move(ms));
  }
  return *this;
}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(const multiset& ms) {
  if (this != &ms) {
    BinaryTree<Key, Key>::operator=(ms);
  }
  return *this;
}

template <typename Key>
typename BinaryTree<Key, Key>::SetIterator multiset<Key>::begin() {
  return
      typename BinaryTree<Key, Key>::SetIterator(this->GetMinNode(this->root_));
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::end() {
  if (this->root_ == nullptr) return begin();

  auto* last_node = this->GetMaxNode(this->root_);
  iterator last(nullptr, last_node);
  return last;
}

template <typename Key>
void multiset<Key>::merge(multiset<Key>& other) {
  if (&other == this) {
    return;
  }

  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(*it);
  }
  other.clear();
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::count(const key_type& key) {
  size_type count = 0;
  count_helper(this->root_, key, count);

  return count;
}

template <typename Key>
void multiset<Key>::count_helper(typename BinaryTree<Key, Key>::TreeNode* node,
                                 const Key& key, size_type& count) {
  if (node == nullptr) {
    return;
  }

  if (node->key_ == key) {
    ++count;
  }

  count_helper(node->left_, key, count);
  count_helper(node->right_, key, count);
}

template <typename Key>
template <class... Args>
std::vector<std::pair<typename multiset<Key>::iterator, bool>>
multiset<Key>::insert_many(Args&&... args) {
  std::vector<std::pair<iterator, bool>> results;
  (results.push_back(insert(std::forward<Args>(args))), ...);
  return results;
}

template <typename Key>
std::pair<typename BinaryTree<Key, Key>::SetIterator, bool>
multiset<Key>::insert(const Key& key) {
  typename BinaryTree<Key, Key>::TreeNode* current = this->root_;
  typename BinaryTree<Key, Key>::TreeNode* parent = nullptr;
  while (current != nullptr) {
    parent = current;
    if (key <= current->key_) {
      current = current->left_;
    } else {
      current = current->right_;
    }
  }

  auto* new_node = new typename BinaryTree<Key, Key>::TreeNode(key, key);
  if (parent == nullptr) {
    this->root_ = new_node;
  } else if (key <= parent->key_) {
    parent->left_ = new_node;
  } else {
    parent->right_ = new_node;
  }

  return std::make_pair(iterator(new_node), true);
}

template <typename Key>
void multiset<Key>::erase(iterator pos) {
  if (pos.curr_node_ == nullptr) {
    return;
  }

  Key key = *pos;
  erase_helper(this->root_, key);
}

template <typename Key>
typename BinaryTree<Key, Key>::TreeNode* multiset<Key>::erase_helper(
    typename BinaryTree<Key, Key>::TreeNode* node, const Key& key) {
  if (key < node->key_) {
    node->left_ = erase_helper(node->left_, key);
  } else if (key > node->key_) {
    node->right_ = erase_helper(node->right_, key);
  } else {
    //    if (node->left_ == nullptr && node->right_ == nullptr) {
    //      delete node;
    //      return nullptr;
    //    } else if (node->left_ == nullptr) {
    //      typename BinaryTree<Key, Key>::TreeNode* temp = node->right_;
    //      delete node;
    //      return temp;
    //    } else if (node->right_ == nullptr) {
    if (node->right_ == nullptr) {
      typename BinaryTree<Key, Key>::TreeNode* temp = node->left_;
      delete node;
      return temp;
    } else {
      typename BinaryTree<Key, Key>::TreeNode* min_right =
          this->GetMinNode(node->right_);
      node->key_ = min_right->key_;
      node->right_ = erase_helper(node->right_, min_right->key_);
    }
  }
  return node;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key& key) {
  typename BinaryTree<Key, Key>::TreeNode* curr_node = this->root_;
  typename multiset<Key>::iterator res(nullptr);

  while (curr_node != nullptr) {
    if (curr_node->key_ >= key) {
      res = iterator(curr_node);
      curr_node = curr_node->left_;
    } else {
      curr_node = curr_node->right_;
    }
  }
  return res;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key& key) {
  typename BinaryTree<Key, Key>::TreeNode* curr_node = this->root_;
  typename multiset<Key>::iterator res(nullptr);

  while (curr_node != nullptr) {
    if (curr_node->key_ > key) {
      res = iterator(curr_node);
      curr_node = curr_node->left_;
    } else {
      curr_node = curr_node->right_;
    }
  }
  return res;
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key& key) {
  typename multiset<Key>::iterator lower = lower_bound(key);
  typename multiset<Key>::iterator upper = upper_bound(key);

  return std::make_pair(lower, upper);
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MULTISET_S21_MULTISET_TPP_
