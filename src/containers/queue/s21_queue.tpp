#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_QUEUE_S21_QUEUE_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_QUEUE_S21_QUEUE_TPP_

#include "s21_queue.h"

template <class T, class Container>
template <class... Args>
void s21::queue<T, Container>::insert_many_back(Args&&... args) {
  for (const auto& arg : {args...}) {
    cont.push_back(arg);
  }
}

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_QUEUE_S21_QUEUE_TPP_
