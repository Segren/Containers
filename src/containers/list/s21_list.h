#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_LIST_S21_LIST_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_LIST_S21_LIST_H_

#include <initializer_list>
#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

 private:
  struct Node {
    value_type value_;
    Node* prev_;
    Node* next_;

    Node(const value_type& value)
        : value_(value), prev_(nullptr), next_(nullptr) {}
  };

  Node* head_;
  Node* tail_;
  Node* end_;
  size_type size_;

 public:
  // CONSTRUCTORS
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const& items);
  list(const list& l);
  list(list&& l);
  ~list();
  list& operator=(list&& l) noexcept;

  // List Element access
  const_reference front();  // access the first element
  const_reference back();   // access the last element

  // List Capacity
  bool empty();
  size_type size();
  size_type max_size();

  // List Modifiers
  void clear();                            // +
  void push_back(const_reference value);   // +
  void pop_back();                         // +
  void push_front(const_reference value);  // +
  void pop_front();                        // +
  void swap(list& other);                  // +
  void merge(list& other);                 // +
  void reverse();                          // +
  void unique();                           // +
  void sort();                             // +

  template <typename value_type>
  class ListIterator {
   public:
    ListIterator() { ptr_ = nullptr; }
    ListIterator(Node* ptr) : ptr_(ptr){};

    reference operator*() {
      if (!this->ptr_) {
        throw std::invalid_argument("Value is nullptr");
      }
      return this->ptr_->value_;
    }

    ListIterator operator++(int) {
      ptr_ = ptr_->next_;
      return *this;
    }

    ListIterator operator--(int) {
      ptr_ = ptr_->prev_;
      return *this;
    }

    ListIterator& operator++() {
      ptr_ = ptr_->next_;
      return *this;
    }

    ListIterator& operator--() {
      ptr_ = ptr_->prev_;
      return *this;
    }

    ListIterator operator+(const size_type value) {
      Node* tmp = ptr_;
      for (size_type i = 0; i < value; i++) {
        tmp = tmp->next_;
      }

      ListIterator res(tmp);
      return res;
    }

    ListIterator operator-(const size_type value) {
      Node* tmp = ptr_;
      for (size_type i = 0; i < value; i++) {
        tmp = tmp->prev_;
      }
      ListIterator res(tmp);
      return res;
    }

    bool operator==(ListIterator other) { return this->ptr_ == other.ptr_; }
    bool operator!=(ListIterator other) { return this->ptr_ != other.ptr_; }

   private:
    Node* ptr_ = nullptr;
    friend class list<T>;
  };

  template <typename value_type>
  class ListConstIterator : public ListIterator<T> {
   public:
    ListConstIterator(ListIterator<T> other) : ListIterator<T>(other) {}
    const T& operator*() { return ListIterator<T>::operator*(); }
  };

  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;

  // ITERATORS
  iterator begin();
  iterator end();

  // List Modifiers
  iterator insert(iterator pos, const_reference value);  // +
  void erase(iterator pos);                              // +
  void splice(const_iterator pos, list& other);          // +

 private:
  // Support
  void change_end();
  void quick_sort(iterator left, iterator right);
  iterator partition(iterator first, iterator last);
  void copy(const list& l);
  void print_list();

 public:
  template <class... Args>
  iterator insert_many(const_iterator pos, Args&&... args);  // дополнительно
  template <class... Args>
  void insert_many_back(Args&&... args);  // дополнительно
  template <class... Args>
  void insert_many_front(Args&&... args);  // дополнительно
};

}  // namespace s21
#include "s21_list.tpp"
#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_LIST_S21_LIST_H_
