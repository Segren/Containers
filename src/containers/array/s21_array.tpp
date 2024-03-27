#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ARRAY_S21_ARRAY_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ARRAY_S21_ARRAY_TPP_

#include "s21_array.h"

namespace s21 {

template <typename T, std::size_t amount>
array<T, amount>::array() {
  amount_ = amount;
  if (amount_ == 0) {
    array_ = nullptr;  // Защита от выделения памяти под нулевой аррей
  } else {
    array_ = new value_type[amount_];
    for (std::size_t i = 0; i < amount_; i++) {  // Заполнение нулями
      array_[i] = 0;
    }
  }
}
// Инициализация значениями
template <typename T, std::size_t amount>
array<T, amount>::array(std::initializer_list<T> const& items)
    : array<T, amount>() {
  if (items.size() > amount_)
    throw "List has more elements then array can contain\n";
  for (std::size_t i = 0; i < items.size(); i++)
    array_[i] = *(items.begin() + i);
}

// Конструктор копирования
template <typename T, std::size_t amount>
array<T, amount>::array(const array<T, amount>& other) : array<T, amount>() {
  for (std::size_t i = 0; i < amount; i++) array_[i] = other.array_[i];
}

// Конструктор перемещения
template <typename T, std::size_t amount>
array<T, amount>::array(array&& other) noexcept
    : amount_(other.amount_), array_(other.array_) {
  other.array_ = nullptr;
  other.amount_ = 0;
}

// Деструктор
template <typename T, std::size_t amount>
array<T, amount>::~array() {
  if (amount_ > 0) {
    amount_ = 0;
    delete[] array_;
  }
}

// Операторы перегрузки копирования и перемещения.
template <typename T, std::size_t amount>
array<T, amount>& array<T, amount>::operator=(const array& a) {
  for (std::size_t i = 0; i < amount; i++) array_[i] = a.array_[i];
  return *this;
}

template <typename T, std::size_t amount>
array<T, amount>& array<T, amount>::operator=(array&& a) noexcept {
  delete[] array_;
  array_ = a.array_;
  a.array_ = nullptr;
  amount_ = a.amount_;
  a.amount_ = 0;
  return *this;
}

// Доступ к массиву по индексу через ()
template <typename T, std::size_t amount>
typename array<T, amount>::reference array<T, amount>::at(size_type pos) {
  if (pos >= amount_) throw std::out_of_range("Index out of range");
  return array_[pos];
}

template <typename T, std::size_t amount>
typename array<T, amount>::const_reference array<T, amount>::at(
    array::size_type pos) const {
  if (pos >= amount_) throw std::out_of_range("Index out of range");
  return array_[pos];
}

// Перегрузка оператора что бы работал с []
template <typename T, std::size_t amount>
typename array<T, amount>::reference array<T, amount>::operator[](
    size_type pos) {
  if (pos >= amount_) throw std::out_of_range("Index out of range");
  return array_[pos];
}

template <typename T, std::size_t amount>
typename array<T, amount>::const_reference array<T, amount>::operator[](
    size_type pos) const {
  return array_[pos];
}

template <typename T, std::size_t amount>
typename array<T, amount>::const_reference array<T, amount>::front() {
  return array_[0];
}

template <typename T, std::size_t amount>
typename array<T, amount>::const_reference array<T, amount>::back() {
  return array_[amount_ - 1];
}

// Итераторы
template <typename T, std::size_t amount>
T* array<T, amount>::data() {
  return array_;
}

template <typename T, std::size_t amount>
typename array<T, amount>::iterator array<T, amount>::begin() noexcept {
  return array_;
}

template <typename T, std::size_t amount>
typename array<T, amount>::iterator array<T, amount>::end() noexcept {
  return array_ + amount_;
}

template <typename T, std::size_t amount>
const T* array<T, amount>::data() const {
  return array_;
}

template <typename T, std::size_t amount>
typename array<T, amount>::const_iterator array<T, amount>::cbegin()
    const noexcept {
  return array_;
}

template <typename T, std::size_t amount>
typename array<T, amount>::const_iterator array<T, amount>::cend()
    const noexcept {
  return array_ + amount_;
}

// Проверка что массив пуст
template <typename T, std::size_t amount>
bool array<T, amount>::empty() {
  return (*this).begin() == (*this).end();
}

// Количество заполненных слотов массива
template <typename T, std::size_t amount>
typename array<T, amount>::size_type array<T, amount>::size() {
  return amount_;
}

// Общий размер массива
template <typename T, std::size_t amount>
typename array<T, amount>::size_type array<T, amount>::max_size() {
  return amount;
}
// Заполняет массив переданным элементом
template <typename T, std::size_t amount>
void array<T, amount>::fill(const_reference value) {
  for (size_t i = 0; i < amount_; i++) {
    array_[i] = value;
  }
}
// Меняет элемент в массиве на переданный
template <typename T, std::size_t amount>
void array<T, amount>::swap(array& other) {
  for (size_t i = 0; i < amount_; i++) {
    value_type t = array_[i];
    array_[i] = other.array_[i];
    other.array_[i] = t;
  }
}
}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ARRAY_S21_ARRAY_TPP_