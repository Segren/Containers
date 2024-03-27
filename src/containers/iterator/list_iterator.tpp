// #ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_LIST_ITERATOR_TPP_
// #define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_LIST_ITERATOR_TPP_

// #include "list_iterator.h"

// namespace s21 {

// template <typename T>
// ListIterator<T>::ListIterator() : ptr_(nullptr) {}

// template <typename T>
// T& ListIterator<T>::operator*() {
//   if (!ptr_) {
//     throw std::invalid_argument("Value is nullptr");
//   }
//   return ptr_->value_;
// }

// template <typename T>
// ListIterator<T> ListIterator<T>::operator++(int) {
//   ListIterator temp(*this);
//   ptr_ = ptr_->next_;
//   return temp;
// }

// // Перегрузка постфиксного оператора --
// template <typename T>
// ListIterator<T> ListIterator<T>::operator--(int) {
//   ListIterator<T> temp(*this);
//   ptr_ = ptr_->prev_;
//   return temp;
// }

// // Перегрузка префиксного оператора ++
// template <typename T>
// ListIterator<T>& ListIterator<T>::operator++() {
//   ptr_ = ptr_->next_;
//   return *this;
// }

// // Перегрузка префиксного оператора --
// template <typename T>
// ListIterator<T>& ListIterator<T>::operator--() {
//   ptr_ = ptr_->prev_;
//   return *this;
// }

// template <typename T>
// ListIterator<T> ListIterator<T>::operator+(std::size_t value) const {
//   Node* tmp = ptr_;
//   for (std::size_t i = 0; i < value; ++i) {
//     if (tmp)
//       tmp = tmp->next_;
//     else
//       break;
//   }
//   return ListIterator(tmp);
// }

// template <typename T>
// ListIterator<T> ListIterator<T>::operator-(std::size_t value) const {
//   Node* tmp = ptr_;
//   for (std::size_t i = 0; i < value; ++i) {
//     if (tmp)
//       tmp = tmp->prev_;
//     else
//       break;
//   }
//   return ListIterator(tmp);
// }

// template <typename T>
// bool ListIterator<T>::operator==(const ListIterator<T>& other) {
//   return this->ptr_ == other.ptr_;
// }

// template <typename T>
// bool ListIterator<T>::operator!=(const ListIterator<T>& other) {
//   return this->ptr_ != other.ptr_;
// }

// }  // namespace s21

// #endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_LIST_ITERATOR_TPP_