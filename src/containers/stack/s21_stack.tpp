#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_QUEUE_S21_STACK_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_QUEUE_S21_STACK_TPP_

#include "s21_stack.h"

template <class T, class Container>
typename s21::stack<T, Container>::const_reference
s21::stack<T, Container>::top() {
  if (cont.empty()) {
    throw std::out_of_range("Stack is empty");
  }
  return cont.back();
}

template <class T, class Container>
void s21::stack<T, Container>::pop() {
  if (cont.empty()) {
    throw std::out_of_range("Stack is empty");
  }
  cont.pop_back();
}

template <class T, class Container>
template <class... Args>
void s21::stack<T, Container>::insert_many_front(Args&&... args) {
  for (const auto& arg : {args...}) {
    cont.push_back(arg);
  }
}

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_QUEUE_S21_STACK_TPP_
