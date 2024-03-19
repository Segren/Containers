#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_TREE_BINARY_TREE_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_TREE_BINARY_TREE_H_

#include <iostream>

template <typename Key, typename Value>
class BinaryTree {
 private:
  // struct TreeNode;

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
  //  set_iterator begin();
  //  set_iterator end();
  set_iterator Find(const Key& key);
  map_iterator Find_map(const Key& key);
  bool empty();
  size_type size();
  size_type max_size();
  void clear();
  std::pair<set_iterator, bool> insert(const Key& key);
  std::pair<map_iterator, bool> insert(const Key& key, Value value);
  std::pair<map_iterator, bool> insert(std::pair<const key_type&, value_type>);
  void erase(set_iterator pos);
  void erase(map_iterator pos);
  void swap(BinaryTree& other);
  // void merge(BinaryTree& other);
  bool contains(const Key& key);
  void print(TreeNode* node);
  void print();

  // private:
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
