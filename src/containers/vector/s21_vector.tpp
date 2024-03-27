#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_VECTOR_S21_VECTOR_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_VECTOR_S21_VECTOR_TPP_

#include "s21_vector.h"

template <typename T>
s21_vector<T>::s21_vector() : _size(0), _capacity(0), elements(nullptr) {}

template <typename T>
s21_vector<T>::s21_vector(size_type n)
    : _size(n), _capacity(n), elements(new value_type[n]) {
  for (size_type i = 0; i < n; ++i) {
    elements[i] = value_type();
  }
}

template <typename T>
s21_vector<T>::s21_vector(std::initializer_list<value_type> const &items)
    : _size(0), _capacity(items.size()), elements(nullptr) {
  // выделение памяти на элементы
  elements = new value_type[_capacity];

  // копируем элементы из initializer_list в наш вектор
  for (const auto &item : items) {
    elements[_size++] = item;
  }
}

template <typename T>
s21_vector<T>::s21_vector(const s21_vector &v)
    : _size(v._size), _capacity(v._capacity) {
  elements = new value_type[_capacity];
  for (size_type i = 0; i < _size; ++i) {
    elements[i] = v.elements[i];
  }
}

template <typename T>
s21_vector<T>::s21_vector(s21_vector &&v) noexcept
    : _size(v._size), _capacity(v._capacity), elements(v.elements) {
  v.elements = nullptr;
  v._size = 0;
  v._capacity = 0;
}

template <typename T>
s21_vector<T>::~s21_vector() {
  delete[] elements;
  elements = nullptr;
  _size = 0;
  _capacity = 0;
}

template <typename T>
s21_vector<T> &s21_vector<T>::operator=(s21_vector<T> &&v) noexcept {
  // проверка на самоприсваивание
  if (this != &v) {
    delete[] elements;

    elements = v.elements;
    _size = v._size;
    _capacity = v._capacity;

    v.elements = nullptr;
    v._size = 0;
    v._capacity = 0;
  }
  return *this;
}

template <typename T>
s21_vector<T> &s21_vector<T>::operator=(const s21_vector<T> &v) {
  if (this != &v) {
    delete[] elements;
    _size = v._size;
    _capacity = v._capacity;

    elements = new value_type[_capacity];
    for (size_type i = 0; i < _size; ++i) {
      elements[i] = v.elements[i];
    }
  }
  return *this;
}

template <typename T>
T &s21_vector<T>::at(size_t pos) {
  if (pos >= _size) {
    throw std::out_of_range("Index out of range");
  }
  return elements[pos];
}

template <typename T>
T &s21_vector<T>::operator[](size_t pos) {
  if (pos >= _size) {
    throw std::out_of_range("Index out of range");
  }
  return elements[pos];
}

template <typename T>
const T &s21_vector<T>::operator[](size_t pos) const {
  if (pos >= _size) {
    throw std::out_of_range("Index out of range");
  }
  return elements[pos];
}

template <typename T>
const T &s21_vector<T>::front() const {
  if (_size == 0) {
    throw std::out_of_range("Vector is empty");
  }
  return elements[0];
}

template <typename T>
const T &s21_vector<T>::back() const {
  if (_size == 0) {
    throw std::out_of_range("Vector is empty");
  }
  return elements[_size - 1];
}

template <typename T>
T *s21_vector<T>::data() {
  return elements;
}

template <typename T>
T *s21_vector<T>::begin() {
  return elements;
}

template <typename T>
T *s21_vector<T>::end() {
  return elements + _size;
}

template <typename T>
const T *s21_vector<T>::begin() const {
  return elements;
}

template <typename T>
const T *s21_vector<T>::end() const {
  return elements + _size;
}

template <typename T>
bool s21_vector<T>::empty() const {
  return _size == 0;
}

template <typename T>
size_t s21_vector<T>::size() const {
  return _size;
}

template <typename T>
size_t s21_vector<T>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(value_type);
}

template <typename T>
void s21_vector<T>::reserve(size_type new_cap) {
  if (new_cap > _capacity) {
    iterator new_elements = new value_type[new_cap];
    std::copy(elements, elements + _size, new_elements);
    delete[] elements;
    elements = new_elements;

    _capacity = new_cap;
  }
}

template <typename T>
size_t s21_vector<T>::capacity() const {
  return _capacity;
}

template <typename T>
void s21_vector<T>::shrink_to_fit() {
  if (_size < _capacity) {
    if (_size == 0) {
      delete[] elements;
      elements = nullptr;
      _capacity = 0;
    } else {
      iterator new_elements = new value_type[_size];
      std::copy(elements, elements + _size, new_elements);
      delete[] elements;
      elements = new_elements;
      _capacity = _size;
    }
  }
}

template <typename T>
void s21_vector<T>::clear() {
  // требуется только для объектов класса с деструктором
  //  for (size_type i = 0; i < _size; ++i)
  //  {
  //      elements[i].~value_type();
  //  }
  _size = 0;
}

template <typename T>
T *s21_vector<T>::insert(const_iterator pos, const_reference value) {
  size_type index = pos - begin();
  if (index > _size) {
    throw std::out_of_range("Insert position is out of range");
  }

  if (_size >= _capacity) {
    reserve(_capacity > 0 ? _capacity * 2 : 1);
  }

  for (size_type i = _size; i > index; --i) {
    elements[i] = elements[i - 1];
  }

  elements[index] = value;
  ++_size;

  return begin() + index;
}

template <typename T>
void s21_vector<T>::erase(const_iterator pos) {
  size_type index = pos - begin();
  if (index >= _size) {
    throw std::out_of_range("Erase position is out of range");
  }

  for (size_type i = index; i < _size - 1; ++i) {
    elements[i] = elements[i + 1];
  }
  elements[_size].~value_type();
  --_size;
}

template <typename T>
void s21_vector<T>::push_back(const_reference value) {
  if (_size >= _capacity) {
    reserve(_capacity > 0 ? _capacity * 2 : 1);
  }
  elements[_size] = value;
  ++_size;
}

template <typename T>
void s21_vector<T>::pop_back() {
  if (_size == 0) {
    throw std::out_of_range("pop_back error : empty vector");
  }
  elements[_size].~value_type();
  --_size;
}

template <typename T>
void s21_vector<T>::swap(s21_vector &other) {
  std::swap(elements, other.elements);
  std::swap(_size, other._size);
  std::swap(_capacity, other._capacity);
}

template <typename T>
template <typename... Args>
T *s21_vector<T>::insert_many(const_iterator pos, Args &&...args) {
  size_type num_new_elements = sizeof...(args);
  size_type insert_index = pos - begin();
  if (_size + num_new_elements > _capacity) {
    reserve(_size + num_new_elements);
  }
  std::move_backward(begin() + insert_index, end(), end() + num_new_elements);

  auto new_pos = begin() + insert_index;
  // fold expression для вставки аргументов
  (..., (void(*(new_pos++) = args)));

  _size += num_new_elements;
  return new_pos;
}

template <typename T>
template <typename... Args>
void s21_vector<T>::insert_many_back(Args &&...args) {
  size_type num_new_elements = sizeof...(args);
  if (_size + num_new_elements > _capacity) {
    reserve(_size + num_new_elements);
  }

  auto new_pos = end();
  // fold expression для вставки аргументов
  (..., (void(*(new_pos++) = args)));

  _size += num_new_elements;
}

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_VECTOR_S21_VECTOR_TPP_