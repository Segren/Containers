#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_TREE_BINARY_TREE_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_TREE_BINARY_TREE_H_

#include <iostream>

template <typename K, typename V>
class TreeNode {
 public:
  K key;
  V value;
  TreeNode* left;
  TreeNode* right;

  TreeNode(const K& k, const V& v)
      : key(k), value(v), left(nullptr), right(nullptr) {}

  TreeNode(const TreeNode&) = delete;
  TreeNode& operator=(const TreeNode&) = delete;

  TreeNode(TreeNode&& other) noexcept
      : key(std::move(other.key)),
        value(std::move(other.value)),
        left(other.left),
        right(other.right) {
    other.left = nullptr;
    other.right = nullptr;
  }

  TreeNode& operator=(TreeNode&& other) noexcept {
    if (this != &other) {
      key = std::move(other.key);
      value = std::move(other.value);
      left = other.left;
      right = other.right;
      other.left = nullptr;
      other.right = nullptr;
    }
    return *this;
  }

  ~TreeNode() {
    delete left;
    delete right;
  }
};

template <typename K, typename V>
class BinaryTree {
 private:
  TreeNode<K, V>* root;

  TreeNode<K, V>* insert(TreeNode<K, V>& node, const K& key, const V& value);
  TreeNode<K, V>* find(TreeNode<K, V>& node, const K& key) const;
  TreeNode<K, V>* remove(TreeNode<K, V>& node, const K& key);
  void inorderTraversal(TreeNode<K, V>& node) const;

 public:
  BinaryTree();
  ~BinaryTree();

  bool empty() const;
  size_t size() const;
  size_t maxSize() const;
  void insert(const K& key, const V& value);
  V* find(const K& key) const;
  void remove(const K& key);
  void inorderTraversal() const;
  TreeNode<K, V>& getRoot() const;
  TreeNode<K, V>& minValueNode(TreeNode<K, V>& node) const;
  TreeNode<K, V>& maxValueNode(TreeNode<K, V>& node) const;

 private:
  size_t countNodes(TreeNode<K, V>& node) const;
  size_t calculateMaxSize(TreeNode<K, V>& node) const;
  size_t calculateDepth(TreeNode<K, V>& node) const;
};

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_TREE_BINARY_TREE_H_
