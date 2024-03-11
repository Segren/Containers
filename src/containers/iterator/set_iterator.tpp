#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_SET_ITERATOR_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_SET_ITERATOR_TPP_

#include "../tree/binary_tree.h"
#include "iterator.h"

namespace s21 {

template <typename T>
class SetIterator : public Iterator<T> {
  using Key = T;
  using tree_only_key = BinaryTree<Key, nullptr_t>;
  using node_only_key = TreeNode<Key, nullptr_t>;

 private:
  tree_only_key& set;
  node_only_key* current;

 public:
  SetIterator(tree_only_key& set, node_only_key* start_node = nullptr)
      : set(set), current(start_node) {}

  virtual void operator++() override {
    if (current == nullptr) {
      return;
    }

    if (current->right != nullptr) {
      current = set.minValueNode(current->right);
    } else {
      node_only_key* parent = nullptr;
      node_only_key* temp = set.root;

      while (temp != nullptr && current == temp->right) {
        parent = temp;
        temp = temp->right;
      }

      current = parent;
    }
  }

  virtual void operator--() override {
    if (current == nullptr) {
      return;
    }

    if (current->left != nullptr) {
      current = set.maxValueNode(current->left);
    } else {
      node_only_key* parent = nullptr;
      node_only_key* temp = set.root;

      while (temp != nullptr && current == temp->left) {
        parent = temp;
        temp = temp->left;
      }
      current = parent;
    }
  }

  virtual T& operator*() const override {
    if (current == nullptr) {
      throw std::out_of_range("Iterator is out of bounds");
    }
    return current->value;
  }

  virtual T* operator->() const override {
    if (current == nullptr) {
      throw std::out_of_range("Iterator is out of bounds");
    }
    return &(current->value);
  }

  virtual bool operator!=(const Iterator<T>& other) const override {
    const SetIterator<T>& other_iterator =
        dynamic_cast<const SetIterator<T>&>(other);
    return (this->current != other_iterator.current);
  }

  virtual bool operator==(const Iterator<T>& other) const override {
    const SetIterator<T>& other_iterator =
        dynamic_cast<const SetIterator<T>&>(other);
    return (this->current == other_iterator.current);
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_SET_ITERATOR_TPP_
