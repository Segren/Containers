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
      : key(k), value(v), left(nullptr), right(nullptr){};
  ~TreeNode();
};

template <typename K, typename V>
class BinaryTree {
 private:
  TreeNode<K, V>* root;

  TreeNode<K, V>* insert(TreeNode<K, V>* node, const K& key, const V& value);
  TreeNode<K, V>* find(TreeNode<K, V>* node, const K& key) const;
  TreeNode<K, V>* remove(TreeNode<K, V>* node, const K& key);
  TreeNode<K, V>* minValueNode(TreeNode<K, V>* node) const;
  TreeNode<K, V>* maxValueNode(TreeNode<K, V>* node) const;
  void inorderTraversal(TreeNode<K, V>* node) const;

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

 private:
  size_t countNodes(TreeNode<K, V>* node) const;
  size_t calculateMaxSize(TreeNode<K, V>* node) const;
  size_t calculateDepth(TreeNode<K, V>* node) const;
};

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_TREE_BINARY_TREE_H_
