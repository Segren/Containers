#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_TREE_BINARY_TREE_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_TREE_BINARY_TREE_H_

#include <iostream>

template <typename Key, typename Value>
class BinaryTree {
 public:
  class SetIterator;
  class MapIterator;
  class ConstSetIterator;
  class ConstMapIterator;
  struct TreeNode;

  using key_type = Key;
  using value_type = Value;
  using reference = value_type&;
  using map_reference = std::pair<const key_type, value_type>&;
  using const_reference = const value_type&;
  using const_map_reference = map_reference&;
  using set_iterator = SetIterator;
  using map_iterator = MapIterator;
  using const_set_iterator = ConstSetIterator;
  using const_map_iterator = ConstMapIterator;
  using size_type = size_t;

  BinaryTree();
  BinaryTree(const BinaryTree& other);
  BinaryTree(BinaryTree&& other) noexcept;
  ~BinaryTree();
  BinaryTree& operator=(BinaryTree&& other) noexcept;
  BinaryTree& operator=(const BinaryTree& other);
  set_iterator FindInSet(const key_type& key);
  map_iterator FindInMap(const key_type& key);
  size_type GetMaxSize();

  void Clear();
  bool Empty();
  size_type Size();

  void Swap(BinaryTree& other);
  bool Contains(const key_type& key);

  struct TreeNode {
    TreeNode(key_type key, value_type value);
    TreeNode(key_type key, value_type value, TreeNode* parent);
    key_type key_;
    value_type value_;
    TreeNode* left_ = nullptr;
    TreeNode* right_ = nullptr;
    TreeNode* parent_ = nullptr;
    int height_ = 0;
    friend class BinaryTree<key_type, value_type>;
  };
  TreeNode* root_;

  void FreeNode(TreeNode* node);
  TreeNode* CopyTreeNode(TreeNode* node, TreeNode* parent);

  void SwapValueBetweenNodes(TreeNode* a, TreeNode* b);
  void RightRotateNode(TreeNode* node);
  void LeftRotateNode(TreeNode* node);
  void Balancing(TreeNode* node);
  int GetBalance(TreeNode* node);
  int GetHeight(TreeNode* node);
  void SetHeight(TreeNode* node);

  static TreeNode* GetMinNode(TreeNode* node);
  static TreeNode* GetMaxNode(TreeNode* node);

  bool RecursiveInsert(TreeNode* node, const key_type& key, value_type value);
  TreeNode* RecursiveDelete(TreeNode* node, key_type key);
  size_type GetSize(TreeNode* node);
  TreeNode* RecursiveFind(TreeNode* node, const key_type& key);
};

#include "binary_tree.tpp"

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_TREE_BINARY_TREE_H_
