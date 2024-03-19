#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_TREE_BINARY_TREE_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_TREE_BINARY_TREE_TPP_

#include "binary_tree.h"

template <typename Key, typename Value>
BinaryTree<Key, Value>::BinaryTree() : root_(nullptr) {}

template <typename Key, typename Value>
BinaryTree<Key, Value>::BinaryTree(const BinaryTree &other) {
  root_ = CopyTree(other.root_, nullptr);
}

template <typename Key, typename Value>
BinaryTree<Key, Value>::BinaryTree(BinaryTree &&other) noexcept {
  root_ = other.root_;
  other.root_ = nullptr;
}

template <typename Key, typename Value>
BinaryTree<Key, Value>::~BinaryTree() {
  clear();
}

template <typename Key, typename Value>
BinaryTree<Key, Value> &BinaryTree<Key, Value>::operator=(
    BinaryTree &&other) noexcept {
  if (this != &other) {
    root_ = other.root_;
    other.root_ = nullptr;
  }
  return *this;
}

template <typename Key, typename Value>
BinaryTree<Key, Value> &BinaryTree<Key, Value>::operator=(
    const BinaryTree &other) {
  if (this != &other) {
    BinaryTree temp(other);
    FreeNode(root_);
    *this = std::move(temp);
  }
  return *this;
}

template <typename Key, typename Value>
bool BinaryTree<Key, Value>::empty() {
  return root_ == nullptr;
}

template <typename Key, typename Value>
size_t BinaryTree<Key, Value>::size() {
  return RecursiveSize(root_);
}

template <typename Key, typename Value>
size_t BinaryTree<Key, Value>::max_size() {
  return std::numeric_limits<size_type>::max() /
         sizeof(typename BinaryTree<Key, Value>::TreeNode);
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::clear() {
  if (root_ != nullptr) FreeNode(root_);
  root_ = nullptr;
}

template <typename Key, typename Value>
std::pair<typename BinaryTree<Key, Value>::SetIterator, bool>
BinaryTree<Key, Value>::insert(const Key &key) {
  std::pair<SetIterator, bool> return_value;
  if (root_ == nullptr) {
    root_ = new TreeNode(key, key);
    return_value.first = SetIterator(root_);
    return_value.second = true;
  } else {
    bool check_insert = RecursiveInsert(root_, key, key);
    return_value.first = Find(key);
    return_value.second = check_insert;
  }
  return return_value;
}

template <typename Key, typename Value>
std::pair<typename BinaryTree<Key, Value>::MapIterator, bool>
BinaryTree<Key, Value>::insert(const Key &key, const Value value) {
  std::pair<MapIterator, bool> return_value;
  if (root_ == nullptr) {
    root_ = new TreeNode(key, value);
    return_value.first = MapIterator(root_);
    return_value.second = true;
  } else {
    bool check_insert = RecursiveInsert(root_, key, value);
    return_value.first = Find_map(key);
    return_value.second = check_insert;
  }
  return return_value;
}

template <typename Key, typename Value>
std::pair<typename BinaryTree<Key, Value>::MapIterator, bool>
BinaryTree<Key, Value>::insert(std::pair<const Key &, Value> pair) {
  std::pair<MapIterator, bool> return_value;
  if (root_ == nullptr) {
    root_ = new TreeNode(pair.first, pair.second);
    return_value.first = MapIterator(root_);
    return_value.second = true;
  } else {
    bool check_insert = RecursiveInsert(root_, pair.first, pair.second);
    return_value.first = Find_map(pair.first);
    return_value.second = check_insert;
  }
  return return_value;
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::swap(BinaryTree &other) {
  std::swap(root_, other.root_);
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::set_iterator BinaryTree<Key, Value>::Find(
    const Key &key) {
  TreeNode *exact_node = RecursiveFind(root_, key);
  return SetIterator(exact_node);
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::map_iterator BinaryTree<Key, Value>::Find_map(
    const Key &key) {
  TreeNode *exact_node = RecursiveFind(root_, key);
  return MapIterator(exact_node);
}

template <typename Key, typename Value>
bool BinaryTree<Key, Value>::contains(const Key &key) {
  TreeNode *contain_node = RecursiveFind(root_, key);
  return contain_node != nullptr;
}

template <typename Key, typename Value>
BinaryTree<Key, Value>::TreeNode::TreeNode(Key key, value_type value)
    : key_(key), value_(value) {}

template <typename Key, typename Value>
BinaryTree<Key, Value>::TreeNode::TreeNode(Key key, value_type value,
                                           TreeNode *node)
    : key_(key), value_(value), parent_(node) {}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::TreeNode *BinaryTree<Key, Value>::CopyTree(
    BinaryTree::TreeNode *node, BinaryTree::TreeNode *parent) {
  if (node == nullptr) return nullptr;
  auto *new_node = new TreeNode(node->key_, node->value_, parent);
  new_node->left_ = CopyTree(node->left_, new_node);
  new_node->right_ = CopyTree(node->right_, new_node);
  return new_node;
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::FreeNode(TreeNode *node) {
  if (node == nullptr) return;
  FreeNode(node->left_);
  FreeNode(node->right_);
  delete node;
}

template <typename Key, typename Value>
int BinaryTree<Key, Value>::GetHeight(BinaryTree::TreeNode *node) {
  return node == nullptr ? -1 : node->height_;
}

template <typename Key, typename Value>
int BinaryTree<Key, Value>::GetBalance(BinaryTree::TreeNode *node) {
  return node == nullptr ? 0 : GetHeight(node->right_) - GetHeight(node->left_);
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::SetHeight(BinaryTree::TreeNode *node) {
  node->height_ = std::max(GetHeight(node->left_), GetHeight(node->right_)) + 1;
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::SwapValue(BinaryTree::TreeNode *a,
                                       BinaryTree::TreeNode *b) {
  std::swap(a->key_, b->key_);
  std::swap(a->value_, b->value_);
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::RightRotate(BinaryTree::TreeNode *node) {
  TreeNode *new_left = node->left_->left_;
  TreeNode *new_right_right = node->right_;
  TreeNode *new_right_left = node->left_->right_;

  SwapValue(node, node->left_);
  node->right_ = node->left_;

  node->left_ = new_left;
  if (node->left_) {
    node->left_->parent_ = node;
  }

  node->right_->left_ = new_right_left;
  if (node->right_->left_) {
    node->right_->left_->parent_ = node->right_;
  }

  node->right_->right_ = new_right_right;
  if (node->right_->right_) {
    node->right_->right_->parent_ = node->right_;
  }

  SetHeight(node->right_);
  SetHeight(node);
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::LeftRotate(BinaryTree::TreeNode *node) {
  TreeNode *new_right = node->right_->right_;
  TreeNode *new_left_left = node->left_;
  TreeNode *new_left_right = node->right_->left_;

  SwapValue(node, node->right_);
  node->left_ = node->right_;

  node->right_ = new_right;
  if (node->right_) {
    node->right_->parent_ = node;
  }

  node->left_->right_ = new_left_right;
  if (node->left_->right_) {
    node->left_->right_->parent_ = node->left_;
  }

  node->left_->left_ = new_left_left;
  if (node->left_->left_) {
    node->left_->left_->parent_ = node->left_;
  }

  SetHeight(node->left_);
  SetHeight(node);
}

template <typename Key, typename Value>
void BinaryTree<Key, Value>::Balance(TreeNode *node) {
  int balance = GetBalance(node);
  if (balance == -2) {
    if (GetBalance(node->left_) == 1) LeftRotate(node->left_);
    RightRotate(node);
  } else if (balance == 2) {
    if (GetBalance(node->right_) == -1) RightRotate(node->right_);
    LeftRotate(node);
  }
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::TreeNode *BinaryTree<Key, Value>::GetMin(
    BinaryTree::TreeNode *node) {
  if (node == nullptr) return nullptr;
  if (node->left_ == nullptr) return node;
  return GetMin(node->left_);
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::TreeNode *BinaryTree<Key, Value>::GetMax(
    BinaryTree::TreeNode *node) {
  if (node == nullptr) return nullptr;
  if (node->right_ == nullptr) return node;
  return GetMax(node->right_);
}

template <typename Key, typename Value>
size_t BinaryTree<Key, Value>::RecursiveSize(BinaryTree::TreeNode *node) {
  if (node == nullptr) return 0;
  size_t left_size = RecursiveSize(node->left_);
  size_t right_size = RecursiveSize(node->right_);
  return 1 + left_size + right_size;
}

template <typename Key, typename Value>
bool BinaryTree<Key, Value>::RecursiveInsert(BinaryTree::TreeNode *node,
                                             const Key &key, Value value) {
  bool check_insert = false;
  if (key < node->key_) {
    if (node->left_ == nullptr) {
      node->left_ = new TreeNode(key, value, node);
      check_insert = true;
    } else {
      check_insert = RecursiveInsert(node->left_, key, value);
    }
  } else if (key > node->key_) {
    if (node->right_ == nullptr) {
      node->right_ = new TreeNode(key, value, node);
      check_insert = true;
    } else {
      check_insert = RecursiveInsert(node->right_, key, value);
    }
  } else if (key == node->key_) {
    return check_insert;
  }
  SetHeight(node);
  Balance(node);
  return check_insert;
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::TreeNode *
BinaryTree<Key, Value>::RecursiveDelete(BinaryTree::TreeNode *node, Key key) {
  if (node == nullptr) return nullptr;
  if (key < node->key_) {
    node->left_ = RecursiveDelete(node->left_, key);
  } else if (key > node->key_) {
    node->right_ = RecursiveDelete(node->right_, key);
  } else {
    if (node->left_ == nullptr || node->right_ == nullptr) {
      TreeNode *node_right = node->right_;
      TreeNode *node_left = node->left_;
      TreeNode *node_parent = node->parent_;
      delete node;
      if (node_left == nullptr) {
        node = node_right;
      } else {
        node = node_left;
      }
      if (node != nullptr) node->parent_ = node_parent;
    } else {
      TreeNode *min_in_right = GetMin(node->right_);
      node->key_ = min_in_right->key_;
      node->value_ = min_in_right->value_;
      node->right_ = RecursiveDelete(node->right_, min_in_right->key_);
    }
  }
  if (node != nullptr) {
    SetHeight(node);
    Balance(node);
  }
  return node;
}

template <typename Key, typename Value>
typename BinaryTree<Key, Value>::TreeNode *
BinaryTree<Key, Value>::RecursiveFind(BinaryTree::TreeNode *node,
                                      const Key &key) {
  if (node == nullptr || node->key_ == key) return node;
  if (key > node->key_) {
    return RecursiveFind(node->right_, key);
  } else {
    return RecursiveFind(node->left_, key);
  }
}

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_TREE_BINARY_TREE_TPP_
