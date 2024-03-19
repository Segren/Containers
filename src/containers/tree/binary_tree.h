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
  set_iterator Find(const key_type& key);
  map_iterator Find_map(const key_type& key);
  bool empty();
  size_type size();
  size_type max_size();
  void clear();
  std::pair<set_iterator, bool> insert(const key_type& key);
  std::pair<map_iterator, bool> insert(const key_type& key, value_type value);
  std::pair<map_iterator, bool> insert(std::pair<const key_type&, value_type>);
  void erase(set_iterator pos);
  void erase(map_iterator pos);
  void swap(BinaryTree& other);
  bool contains(const key_type& key);

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
  TreeNode* CopyTree(TreeNode* node, TreeNode* parent);

  void swapValue(TreeNode* a, TreeNode* b);
  void rightRotateNode(TreeNode* node);
  void leftRotateNode(TreeNode* node);
  void balancing(TreeNode* node);
  int getBalance(TreeNode* node);
  int getHeight(TreeNode* node);
  void setHeight(TreeNode* node);

  static TreeNode* getMinNode(TreeNode* node);
  static TreeNode* getMaxNode(TreeNode* node);

  bool recursiveInsert(TreeNode* node, const key_type& key, value_type value);
  TreeNode* recursiveDelete(TreeNode* node, key_type key);
  size_type getSize(TreeNode* node);
  TreeNode* recursiveFind(TreeNode* node, const key_type& key);
};

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_TREE_BINARY_TREE_H_
