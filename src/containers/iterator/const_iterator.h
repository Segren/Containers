#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_CONST_ITERATOR_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_CONST_ITERATOR_H_

namespace s21 {

template <typename T>
class ConstIterator {
 public:
  virtual ~ConstIterator() {}
  // Переход к следующему элементу
  virtual void operator++() = 0;
  // Переход к предыдущему элементу
  virtual void operator--() = 0;

  // Оператор присваивания для итератора
  virtual ConstIterator<T>& operator=(const ConstIterator<T>& other) = 0;
  // Получение константной ссылки на текущий элемент
  virtual const T& operator*() const = 0;
  // Получение константного указателя на текущий элемент
  virtual const T* operator->() const = 0;

  // Проверка на неравенство
  virtual bool operator!=(const ConstIterator<T>& other) const = 0;
  // Проверка на равенство
  virtual bool operator==(const ConstIterator<T>& other) const = 0;

  // Получение итератора на начало контейнера
  virtual ConstIterator<T> begin() const = 0;
  // Получение итератора на конец контейнера
  virtual ConstIterator<T> end() const = 0;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_CONST_ITERATOR_H_
