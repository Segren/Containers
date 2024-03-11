#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_TREE_BINARY_TREE_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_TREE_BINARY_TREE_TPP_

#include "binary_tree.h"

template <typename K, typename V>
BinaryTree<K, V>::BinaryTree() : root(nullptr) {}

template <typename K, typename V>
BinaryTree<K, V>::~BinaryTree() {
  if (root != nullptr) {
    delete root;
  }
}

template <typename K, typename V>
TreeNode<K, V>::~TreeNode() {
  if (left != nullptr) {
    delete left;
  }
  if (right != nullptr) {
    delete right;
  }
}

template <typename K, typename V>
TreeNode<K, V>* BinaryTree<K, V>::insert(TreeNode<K, V>* node, const K& key,
                                         const V& value) {
  if (node == nullptr) {
    return new TreeNode<K, V>(key, value);
  }

  if (key < node->key) {
    node->left = insert(node->left, key, value);
  } else if (key > node->key) {
    node->right = insert(node->right, key, value);
  }

  return node;
}

template <typename K, typename V>
TreeNode<K, V>* BinaryTree<K, V>::find(TreeNode<K, V>* node,
                                       const K& key) const {
  if (node == nullptr || node->key == key) {
    return node;
  }

  if (key < node->key) {
    return find(node->left, key);
  } else {
    return find(node->right, key);
  }
}

template <typename K, typename V>
TreeNode<K, V>* BinaryTree<K, V>::remove(TreeNode<K, V>* node, const K& key) {
  if (node == nullptr) {
    return node;
  }

  if (key < node->key) {
    node->left = remove(node->left, key);
  } else if (key > node->key) {
    node->right = remove(node->right, key);
  } else {
    if (node->left == nullptr) {
      TreeNode<K, V>* temp = node->right;
      delete node;
      return temp;
    } else if (node->right == nullptr) {
      TreeNode<K, V>* temp = node->left;
      delete node;
      return temp;
    }

    // У узла есть два потомка
    TreeNode<K, V>* temp = minValueNode(node->right);
    node->key = temp->key;
    node->value = temp->value;
    node->right = remove(node->right, temp->key);
  }

  return node;
}

template <typename K, typename V>
TreeNode<K, V>* BinaryTree<K, V>::minValueNode(TreeNode<K, V>* node) const {
  TreeNode<K, V>* current = node;

  while (current != nullptr && current->left != nullptr) {
    current = current->left;
  }

  return current;
}

template <typename K, typename V>
void BinaryTree<K, V>::inorderTraversal(TreeNode<K, V>* node) const {
  if (node != nullptr) {
    inorderTraversal(node->left);
    std::cout << node->key << ": " << node->value << " ";
    inorderTraversal(node->right);
  }
}

template <typename K, typename V>
void BinaryTree<K, V>::insert(const K& key, const V& value) {
  root = insert(root, key, value);
}

template <typename K, typename V>
V* BinaryTree<K, V>::find(const K& key) const {
  TreeNode<K, V>* node = find(root, key);
  return (node != nullptr) ? &(node->value) : nullptr;
}

template <typename K, typename V>
void BinaryTree<K, V>::remove(const K& key) {
  root = remove(root, key);
}

template <typename K, typename V>
void BinaryTree<K, V>::inorderTraversal() const {
  inorderTraversal(root);
  std::cout << std::endl;
}

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_TREE_BINARY_TREE_TPP_
