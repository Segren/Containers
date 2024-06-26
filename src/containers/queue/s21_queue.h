#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_QUEUE_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_QUEUE_S21_QUEUE_H_

namespace s21 {

template <typename T, typename Container = s21::list<T>>
class queue {
 public:
  using value_type = typename Container::value_type;
  using reference = typename Container::reference;
  using const_reference = typename Container::const_reference;
  using size_type = typename Container::size_type;

 protected:
  Container cont;

 public:
  queue() : cont() {}
  queue(std::initializer_list<value_type> const &items) : cont(items) {}
  queue(const queue &s) : cont(s.cont) {}
  queue(queue &&s) : cont(std::move(s.cont)) {}
  ~queue() {}
  queue &operator=(queue &&s) {
    this->cont = std::move(s.cont);
    return *this;
  }

  const_reference front() { return cont.front(); }
  const_reference back() { return cont.back(); }

  bool empty() { return cont.empty(); }
  size_type size() { return cont.size(); }

  void push(const_reference value) { this->cont.push_back(value); }
  void pop() { this->cont.pop_front(); }
  void swap(queue &other) { this->cont.swap(other.cont); }

  template <class... Args>
  void insert_many_back(Args &&...args);
};
}  //  namespace s21

#include "../list/s21_list.tpp"
#include "s21_queue.tpp"
#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_QUEUE_S21_QUEUE_H_
