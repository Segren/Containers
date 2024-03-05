#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_ITERATOR_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_ITERATOR_H_

#include <limits>

namespace s21 {

template <typename T>
class Iterator {
 public:
  virtual ~Iterator() {}

  virtual void operator++() = 0;  // Переход к следующему элементу
  virtual void operator--() = 0;  // Переход к предыдущему элементу
  virtual Iterator& operator=(
      const Iterator& other) = 0;  // Оператор присваивания для итератора
  virtual bool operator!=(
      const Iterator& other) const = 0;  // Проверка на неравенство
  virtual bool operator==(
      const Iterator& other) const = 0;  // Проверка на равенство

  virtual T& getElement() const = 0;  // Получение ссылки на текущий элемент
  virtual T& operator*() const = 0;  // Получение ссылки на текущий элемент

  virtual bool isEmpty() const = 0;  // Проверка на пустоту контейнера
  virtual std::size_t size() const = 0;  // Количество элементов в контейнере

  virtual void insert(const T& value) = 0;  // Вставка нового элемента
  virtual void remove() = 0;  // Удаление текущего элемента
  virtual void clear() = 0;  // Очистка контейнера

  virtual Iterator<T> begin()
      const = 0;  // Получение итератора на начало контейнера
  virtual Iterator<T> end()
      const = 0;  // Получение итератора на конец контейнера
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_ITERATOR_H_
