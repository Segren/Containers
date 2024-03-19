#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_ITERATOR_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_ITERATOR_H_

// #include "const_iterator.h"
#include "../list/s21_list.h"

namespace s21 {
    template <typename T>
    class Iterator {
    public:
        Iterator();
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
        T& operator*();
        bool operator!=(const Iterator& other);
        bool operator==(const Iterator& other);
    };
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_ITERATOR_H_
