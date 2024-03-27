#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_VECTOR_S21_VECTOR_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_VECTOR_S21_VECTOR_TPP_

#include "s21_vector.h"

template <typename T>
vector<T>::vector() : size_(0), capacity_(0), elements_(nullptr) {}

template <typename T>
vector<T>::vector(size_type n)
    : size_(n), capacity_(n), elements_(new value_type[n]) {
  for (size_type i = 0; i < n; ++i) {
    elements_[i] = value_type();
  }
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : size_(0), capacity_(items.size()), elements_(nullptr) {
  // выделение памяти на элементы
  elements_ = new value_type[capacity_];

  // копируем элементы из initializer_list в наш вектор
  for (const auto &item : items) {
    elements_[size_++] = item;
  }
}

template <typename T>
vector<T>::vector(const vector &v) : size_(v.size_), capacity_(v.capacity_) {
  elements_ = new value_type[capacity_];
  for (size_type i = 0; i < size_; ++i) {
    elements_[i] = v.elements_[i];
  }
}

template <typename T>
vector<T>::vector(vector &&v) noexcept
    : size_(v.size_), capacity_(v.capacity_), elements_(v.elements_) {
  v.elements_ = nullptr;
  v.size_ = 0;
  v.capacity_ = 0;
}

template <typename T>
vector<T>::~vector() {
  delete[] elements_;
  elements_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <typename T>
vector<T> &vector<T>::operator=(vector<T> &&v) noexcept {
  // проверка на самоприсваивание
  if (this != &v) {
    delete[] elements_;

    elements_ = v.elements_;
    size_ = v.size_;
    capacity_ = v.capacity_;

    v.elements_ = nullptr;
    v.size_ = 0;
    v.capacity_ = 0;
  }
  return *this;
}

template <typename T>
vector<T> &vector<T>::operator=(const vector<T> &v) {
  if (this != &v) {
    delete[] elements_;
    size_ = v.size_;
    capacity_ = v.capacity_;

    elements_ = new value_type[capacity_];
    for (size_type i = 0; i < size_; ++i) {
      elements_[i] = v.elements_[i];
    }
  }
  return *this;
}

template <typename T>
T &vector<T>::at(size_t pos) {
  if (pos >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return elements_[pos];
}

template <typename T>
T &vector<T>::operator[](size_t pos) {
  if (pos >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return elements_[pos];
}

template <typename T>
const T &vector<T>::operator[](size_t pos) const {
  if (pos >= size_) {
    throw std::out_of_range("Index out of range");
  }
  return elements_[pos];
}

template <typename T>
const T &vector<T>::front() const {
  if (size_ == 0) {
    throw std::out_of_range("Vector is empty");
  }
  return elements_[0];
}

template <typename T>
const T &vector<T>::back() const {
  if (size_ == 0) {
    throw std::out_of_range("Vector is empty");
  }
  return elements_[size_ - 1];
}

template <typename T>
T *vector<T>::data() {
  return elements_;
}

template <typename T>
T *vector<T>::begin() {
  return elements_;
}

template <typename T>
T *vector<T>::end() {
  return elements_ + size_;
}

template <typename T>
const T *vector<T>::begin() const {
  return elements_;
}

template <typename T>
const T *vector<T>::end() const {
  return elements_ + size_;
}

template <typename T>
bool vector<T>::empty() const {
  return size_ == 0;
}

template <typename T>
size_t vector<T>::size() const {
  return size_;
}

template <typename T>
size_t vector<T>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template <typename T>
void vector<T>::reserve(size_type new_cap) {
  if (new_cap > capacity_) {
    iterator new_elements = new value_type[new_cap];
    std::copy(elements_, elements_ + size_, new_elements);
    delete[] elements_;
    elements_ = new_elements;

    capacity_ = new_cap;
  }
}

template <typename T>
size_t vector<T>::capacity() const {
  return capacity_;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (size_ < capacity_) {
    if (size_ == 0) {
      delete[] elements_;
      elements_ = nullptr;
      capacity_ = 0;
    } else {
      iterator new_elements = new value_type[size_];
      std::copy(elements_, elements_ + size_, new_elements);
      delete[] elements_;
      elements_ = new_elements;
      capacity_ = size_;
    }
  }
}

template <typename T>
void vector<T>::clear() {
  // требуется только для объектов класса с деструктором
  //  for (size_type i = 0; i < size_; ++i)
  //  {
  //      elements_[i].~value_type();
  //  }
  size_ = 0;
}

template <typename T>
T *vector<T>::insert(const_iterator pos, const_reference value) {
  size_type index = pos - begin();
  if (index > size_) {
    throw std::out_of_range("Insert position is out of range");
  }

  if (size_ >= capacity_) {
    reserve(capacity_ > 0 ? capacity_ * 2 : 1);
  }

  for (size_type i = size_; i > index; --i) {
    elements_[i] = elements_[i - 1];
  }

  elements_[index] = value;
  ++size_;

  return begin() + index;
}

template <typename T>
void vector<T>::erase(const_iterator pos) {
  size_type index = pos - begin();
  if (index >= size_) {
    throw std::out_of_range("Erase position is out of range");
  }

  for (size_type i = index; i < size_ - 1; ++i) {
    elements_[i] = elements_[i + 1];
  }
  elements_[size_].~value_type();
  --size_;
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (size_ >= capacity_) {
    reserve(capacity_ > 0 ? capacity_ * 2 : 1);
  }
  elements_[size_] = value;
  ++size_;
}

template <typename T>
void vector<T>::pop_back() {
  if (size_ == 0) {
    throw std::out_of_range("pop_back error : empty vector");
  }
  elements_[size_].~value_type();
  --size_;
}

template <typename T>
void vector<T>::swap(vector &other) {
  std::swap(elements_, other.elements_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

template <typename T>
template <typename... Args>
T *vector<T>::insert_many(const_iterator pos, Args &&...args) {
  size_type num_new_elements = sizeof...(args);
  size_type insert_index = pos - begin();
  if (size_ + num_new_elements > capacity_) {
    reserve(size_ + num_new_elements);
  }
  std::move_backward(begin() + insert_index, end(), end() + num_new_elements);

  auto new_pos = begin() + insert_index;
  // fold expression для вставки аргументов
  (..., (void(*(new_pos++) = args)));

  size_ += num_new_elements;
  return new_pos;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  size_type num_new_elements = sizeof...(args);
  if (size_ + num_new_elements > capacity_) {
    reserve(size_ + num_new_elements);
  }

  auto new_pos = end();
  // fold expression для вставки аргументов
  (..., (void(*(new_pos++) = args)));

  size_ += num_new_elements;
}

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_VECTOR_S21_VECTOR_TPP_