#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_TREE_BINARY_TREE_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_TREE_BINARY_TREE_H_

#include <iostream>

template <typename Key, typename Value>
class BinaryTree {
 protected:
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

  class Iterator {
   public:
    Iterator();
    Iterator(TreeNode* node, TreeNode* past_node = nullptr);
    iterator& operator++();
    iterator operator++(int);
    iterator& operator--();
    iterator operator--(int);
    reference operator*();
    bool operator==(const iterator& it);
    friend class BinaryTree<Key, Value>;
    bool operator!=(const iterator& it);

   protected:
    TreeNode* iter_node_;
    TreeNode* iter_past_node_;
    TreeNode* MoveForward(TreeNode* node);
    TreeNode* MoveBack(TreeNode* node);
  };
  class ConstIterator : public Iterator {
   public:
    ConstIterator() : Iterator(){};
    const_reference operator*() const { return Iterator::operator*(); };
  };

  BinaryTree();
  BinaryTree(const BinaryTree& other);
  BinaryTree(BinaryTree&& other) noexcept;
  ~BinaryTree();
  BinaryTree& operator=(BinaryTree&& other) noexcept;
  BinaryTree& operator=(const BinaryTree& other);
  iterator begin();
  iterator end();
  bool empty();
  size_type size();
  size_type max_size();
  void clear();
  std::pair<iterator, bool> insert(const Key& key);
  void erase(iterator pos);
  void swap(BinaryTree& other);
  void merge(BinaryTree& other);
  bool contains(const Key& key);

 protected:
  iterator Find(const Key& key);
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
  // SUPPORT FOR CONSTRUCTORS
  void FreeNode(TreeNode* node);
  TreeNode* CopyTree(TreeNode* node, TreeNode* parent);
  // AVL BALANCE
  void SwapValue(TreeNode* a, TreeNode* b);
  void RightRotate(TreeNode* node);
  void LeftRotate(TreeNode* node);
  void Balance(TreeNode* node);
  int GetBalance(TreeNode* node);
  int GetHeight(TreeNode* node);
  void SetHeight(TreeNode* node);
  // MIN && MAX
  static TreeNode* GetMin(TreeNode* node);
  static TreeNode* GetMax(TreeNode* node);
  // RECURSIVE SUPPORT FUNCTIONS
  bool RecursiveInsert(TreeNode* node, const Key& key, Value value);
  TreeNode* RecursiveDelete(TreeNode* node, Key key);
  size_t RecursiveSize(TreeNode* node);
  TreeNode* RecursiveFind(TreeNode* node, const Key& key);
};

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_TREE_BINARY_TREE_H_
