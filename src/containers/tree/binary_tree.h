#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_TREE_BINARY_TREE_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_TREE_BINARY_TREE_H_

#include <iostream>

template <typename Key, typename Value>
class BinaryTree {
 private:
  struct TreeNode;

 public:
  class Iterator;
  class ConstIterator;

  using key_type = Key;
  using value_type = Value;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using size_type = size_t;

  BinaryTree();
  BinaryTree(const BinaryTree& other);
  BinaryTree(BinaryTree&& other) noexcept;
  ~BinaryTree();
  BinaryTree& operator=(BinaryTree&& other) noexcept;
  BinaryTree& operator=(const BinaryTree& other);
  iterator begin();
  iterator end();
  iterator Find(const Key& key);
  bool empty();
  size_type size();
  size_type max_size();
  void clear();
  std::pair<iterator, bool> insert(const Key& key);
  void erase(iterator pos);
  void swap(BinaryTree& other);
  void merge(BinaryTree& other);
  bool contains(const Key& key);
  void print(TreeNode* node);
  void print();

 private:
  struct TreeNode {
    TreeNode(Key key, value_type value);
    TreeNode(Key key, value_type value, TreeNode* parent);
    Key key_;
    value_type value_;
    TreeNode* left_ = nullptr;
    TreeNode* right_ = nullptr;
    TreeNode* parent_ = nullptr;
    int height_ = 0;
    friend class BinaryTree<Key, Value>;
  };
  TreeNode* root_;

  void FreeNode(TreeNode* node);
  TreeNode* CopyTree(TreeNode* node, TreeNode* parent);

  void SwapValue(TreeNode* a, TreeNode* b);
  void RightRotate(TreeNode* node);
  void LeftRotate(TreeNode* node);
  void Balance(TreeNode* node);
  int GetBalance(TreeNode* node);
  int GetHeight(TreeNode* node);
  void SetHeight(TreeNode* node);

  static TreeNode* GetMin(TreeNode* node);
  static TreeNode* GetMax(TreeNode* node);

  bool RecursiveInsert(TreeNode* node, const Key& key, Value value);
  TreeNode* RecursiveDelete(TreeNode* node, Key key);
  size_t RecursiveSize(TreeNode* node);
  TreeNode* RecursiveFind(TreeNode* node, const Key& key);
};

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_TREE_BINARY_TREE_H_
