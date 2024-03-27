// #ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_LIST_ITERATOR_H_
// #define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_LIST_ITERATOR_H_

// // #include "../list/s21_list.h"

// #include <cstdio>
// namespace s21 {
// template <typename T>
// class ListIterator {
//  public:
//   using Node = typename s21::list<T>::Node;

//   ListIterator();
//   ListIterator& operator++();
//   ListIterator operator++(int);
//   ListIterator& operator--();
//   ListIterator operator--(int);
//   ListIterator operator+(std::size_t value) const;
//   ListIterator operator-(std::size_t value) const;
//   T& operator*();
//   bool operator!=(const ListIterator& other);
//   bool operator==(const ListIterator& other);

//  private:
//   // struct Node {
//   //   T value_;
//   //   Node* prev_;
//   //   Node* next_;

//   //   Node(const T& value) : value_(value), prev_(nullptr), next_(nullptr)
//   {}
//   // };

//   Node* ptr_;
// };

// template <typename T>
// class ListConstIterator : public ListIterator<T> {
//  public:
//   ListConstIterator(const ListIterator<T>& other) : ListIterator<T>(other) {}

//   const T& operator*() const { return ListIterator<T>::operator*(); }
// };
// }  // namespace s21

// #endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_LIST_ITERATOR_H_
