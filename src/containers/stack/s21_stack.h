#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_STACK_S21_STACK_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_STACK_S21_STACK_H_

// #include "../list/s21_list.tpp"

namespace s21 {
template <class T, class Container = s21::list<T>>
class stack {
 public:
  //  Stack Member type
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

 public:
  //  Stack Member functions
  stack() : cont() {}
  stack(std::initializer_list<value_type> const &items) : cont(items) {}
  stack(const stack &s) : cont(s.cont) {}
  stack(stack &&s) : cont(std::move(s.cont)) {}
  ~stack() {}
  stack &operator=(stack &&s) {
    this->cont = std::move(s.cont);
    return *this;
  }

  // Stack Element access
  // const_reference top() { return cont.back(); }
  const_reference top();

  // Stack Capacity
  bool empty() { return cont.empty(); }
  size_type size() { return cont.size(); }

  // Stack Modifiers
  void push(const_reference value) { this->cont.push_back(value); }
  // void pop() { this->cont.pop_back(); }
  void pop();
  void swap(stack &other) { this->cont.swap(other.cont); }
  template <class... Args>
  void insert_many_front(Args &&...args);  // дополнительно

 private:
  Container cont;
};
#include "../list/s21_list.tpp"
#include "s21_stack.tpp"
}  //  namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_STACK_S21_STACK_H_
