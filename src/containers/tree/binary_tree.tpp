#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_TREE_BINARY_TREE_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_TREE_BINARY_TREE_TPP_

#include "binary_tree.h"

template <typename Key, typename T>
BinaryTree<Key, T>::BinaryTree() : root_(nullptr) {}

template <typename Key, typename T>
BinaryTree<Key, T>::BinaryTree(const BinaryTree &other) {
  root_ = CopyTreeNode(other.root_, nullptr);
}

template <typename Key, typename T>
BinaryTree<Key, T>::BinaryTree(BinaryTree &&other) noexcept {
  root_ = other.root_;
  other.root_ = nullptr;
}

template <typename Key, typename T>
BinaryTree<Key, T>::~BinaryTree() {
  Clear();
}

template <typename Key, typename T>
BinaryTree<Key, T> &BinaryTree<Key, T>::operator=(BinaryTree &&other) noexcept {
  if (this != &other) {
    root_ = other.root_;
    other.root_ = nullptr;
  }
  return *this;
}

template <typename Key, typename T>
BinaryTree<Key, T> &BinaryTree<Key, T>::operator=(const BinaryTree &other) {
  if (this != &other) {
    BinaryTree temp(other);
    FreeNode(root_);
    *this = std::move(temp);
  }
  return *this;
}

template <typename Key, typename T>
size_t BinaryTree<Key, T>::GetMaxSize() {
  return std::numeric_limits<size_type>::max() /
         sizeof(typename BinaryTree<Key, T>::TreeNode);
}

template <typename Key, typename T>
void BinaryTree<Key, T>::Clear() {
  if (root_ != nullptr) FreeNode(root_);
  root_ = nullptr;
}

template <typename Key, typename T>
bool BinaryTree<Key, T>::Empty() {
  return root_ == nullptr;
}

template <typename Key, typename T>
size_t BinaryTree<Key, T>::Size() {
  return GetSize(root_);
}

template <typename Key, typename T>
void BinaryTree<Key, T>::Swap(BinaryTree &other) {
  std::swap(root_, other.root_);
}

template <typename Key, typename T>
typename BinaryTree<Key, T>::set_iterator BinaryTree<Key, T>::FindInSet(
    const Key &key) {
  TreeNode *exact_node = RecursiveFind(root_, key);
  return SetIterator(exact_node);
}

template <typename Key, typename T>
typename BinaryTree<Key, T>::map_iterator BinaryTree<Key, T>::FindInMap(
    const Key &key) {
  TreeNode *exact_node = RecursiveFind(root_, key);
  return MapIterator(exact_node);
}

template <typename Key, typename T>
bool BinaryTree<Key, T>::Contains(const Key &key) {
  TreeNode *contain_node = RecursiveFind(root_, key);
  return contain_node != nullptr;
}

template <typename Key, typename T>
BinaryTree<Key, T>::TreeNode::TreeNode(Key key, T value)
    : key_(key), value_(value) {}

template <typename Key, typename T>
BinaryTree<Key, T>::TreeNode::TreeNode(Key key, T value, TreeNode *node)
    : key_(key), value_(value), parent_(node) {}

template <typename Key, typename T>
typename BinaryTree<Key, T>::TreeNode *BinaryTree<Key, T>::CopyTreeNode(
    TreeNode *node, TreeNode *parent) {
  if (node == nullptr) return nullptr;
  auto *new_node = new TreeNode(node->key_, node->value_, parent);
  new_node->left_ = CopyTreeNode(node->left_, new_node);
  new_node->right_ = CopyTreeNode(node->right_, new_node);
  return new_node;
}

template <typename Key, typename T>
void BinaryTree<Key, T>::FreeNode(TreeNode *node) {
  if (node == nullptr) return;
  FreeNode(node->left_);
  FreeNode(node->right_);
  delete node;
}

template <typename Key, typename T>
int BinaryTree<Key, T>::GetHeight(TreeNode *node) {
  return node == nullptr ? -1 : node->height_;
}

template <typename Key, typename T>
int BinaryTree<Key, T>::GetBalance(TreeNode *node) {
  return node == nullptr ? 0 : GetHeight(node->right_) - GetHeight(node->left_);
}

template <typename Key, typename T>
void BinaryTree<Key, T>::SetHeight(TreeNode *node) {
  node->height_ = std::max(GetHeight(node->left_), GetHeight(node->right_)) + 1;
}

template <typename Key, typename T>
void BinaryTree<Key, T>::SwapValueBetweenNodes(TreeNode *a, TreeNode *b) {
  std::swap(a->key_, b->key_);
  std::swap(a->value_, b->value_);
}

template <typename Key, typename T>
void BinaryTree<Key, T>::RightRotateNode(TreeNode *node) {
  TreeNode *new_left = node->left_->left_;
  TreeNode *new_right_right = node->right_;
  TreeNode *new_right_left = node->left_->right_;

  SwapValueBetweenNodes(node, node->left_);
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

template <typename Key, typename T>
void BinaryTree<Key, T>::LeftRotateNode(TreeNode *node) {
  TreeNode *new_right = node->right_->right_;
  TreeNode *new_left_left = node->left_;
  TreeNode *new_left_right = node->right_->left_;

  SwapValueBetweenNodes(node, node->right_);
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

template <typename Key, typename T>
void BinaryTree<Key, T>::Balancing(TreeNode *node) {
  int balance = GetBalance(node);
  if (balance == -2) {
    if (GetBalance(node->left_) == 1) LeftRotateNode(node->left_);
    RightRotateNode(node);
  } else if (balance == 2) {
    if (GetBalance(node->right_) == -1) RightRotateNode(node->right_);
    LeftRotateNode(node);
  }
}

template <typename Key, typename T>
typename BinaryTree<Key, T>::TreeNode *BinaryTree<Key, T>::GetMinNode(
    TreeNode *node) {
  if (node == nullptr) return nullptr;
  if (node->left_ == nullptr) return node;
  return GetMinNode(node->left_);
}

template <typename Key, typename T>
typename BinaryTree<Key, T>::TreeNode *BinaryTree<Key, T>::GetMaxNode(
    TreeNode *node) {
  if (node == nullptr) return nullptr;
  if (node->right_ == nullptr) return node;
  return GetMaxNode(node->right_);
}

template <typename Key, typename T>
size_t BinaryTree<Key, T>::GetSize(TreeNode *node) {
  if (node == nullptr) return 0;
  size_t left_size = GetSize(node->left_);
  size_t right_size = GetSize(node->right_);
  return 1 + left_size + right_size;
}

template <typename Key, typename T>
bool BinaryTree<Key, T>::RecursiveInsert(TreeNode *node, const Key &key,
                                         T value) {
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
  Balancing(node);
  return check_insert;
}

template <typename Key, typename T>
typename BinaryTree<Key, T>::TreeNode *BinaryTree<Key, T>::RecursiveDelete(
    TreeNode *node, Key key) {
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
      TreeNode *min_in_right = GetMinNode(node->right_);
      node->key_ = min_in_right->key_;
      node->value_ = min_in_right->value_;
      node->right_ = RecursiveDelete(node->right_, min_in_right->key_);
    }
  }
  if (node != nullptr) {
    SetHeight(node);
    Balancing(node);
  }
  return node;
}

template <typename Key, typename T>
typename BinaryTree<Key, T>::TreeNode *BinaryTree<Key, T>::RecursiveFind(
    TreeNode *node, const Key &key) {
  if (node == nullptr || node->key_ == key) return node;
  if (key > node->key_) {
    return RecursiveFind(node->right_, key);
  } else {
    return RecursiveFind(node->left_, key);
  }
}

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_TREE_BINARY_TREE_TPP_
