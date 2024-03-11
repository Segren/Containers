#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_SET_CONST_ITERATOR_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_SET_CONST_ITERATOR_TPP_

#include "../tree/binary_tree.h"
#include "const_iterator.h"

namespace s21 {

template <typename T>
class SetConstIterator : public ConstIterator<T> {
  using Key = T;
  using tree_only_key = BinaryTree<Key, nullptr_t>;
  using node_only_key = TreeNode<Key, nullptr_t>;

 private:
  const tree_only_key& set;
  node_only_key* current;

 public:
  SetConstIterator(const tree_only_key& set,
                   node_only_key* start_node = nullptr)
      : set(set), current(start_node) {}

  // SetConstIterator(const SetConstIterator& other) { operator=(other); }

  virtual ~SetConstIterator() = default;

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

  virtual ConstIterator<Key>& operator=(
      const ConstIterator<Key>& other) override {
    const SetConstIterator<Key>& other_iterator =
        dynamic_cast<const SetConstIterator<Key>&>(other);
    this->set = other_iterator.set;
    this->current = other_iterator.current;
    return *this;
  }

  virtual const Key& operator*() const override {
    if (current == nullptr) {
      throw std::out_of_range("Iterator is out of bounds");
    }
    return current->value;
  }

  virtual const Key* operator->() const override {
    if (current == nullptr) {
      throw std::out_of_range("Iterator is out of bounds");
    }
    return &(current->value);
  }

  virtual bool operator!=(const ConstIterator<Key>& other) const override {
    const SetConstIterator<Key>& other_iterator =
        dynamic_cast<const SetConstIterator<Key>&>(other);
    return (this->current != other_iterator.current);
  }

  virtual bool operator==(const ConstIterator<Key>& other) const override {
    const SetConstIterator<Key>& other_iterator =
        dynamic_cast<const SetConstIterator<Key>&>(other);
    return (this->current == other_iterator.current);
  }

  virtual ConstIterator<Key> begin() const override {
    return SetConstIterator<Key>(set, set.minValueNode(set.root));
  }

  virtual ConstIterator<Key> end() const override {
    return SetConstIterator<Key>(set, nullptr);
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_SET_CONST_ITERATOR_TPP_
