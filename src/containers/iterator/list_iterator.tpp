#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_LIST_ITERATOR_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_LIST_ITERATOR_TPP_

#include <algorithm>        // Для std::copy
#include <cstddef>          // Для size_t
#include <initializer_list> // Для std::initializer_list
#include <stdexcept>        // Для std::out_of_range
#include <iostream>

#include "list_iterator.h"

namespace s21 {
    template <typename T>
    class ListIterator : public Iterator<T> {
    public: 
        ListIterator() : ptr_(nullptr) {}
        explicit ListIterator(Node* ptr) : ptr_(ptr) {}

        T& operator*() override {
            if (!ptr_) {
                throw std::invalid_argument("Value is nullptr");
            }
            return ptr_->value_;
        }

        // Перегрузка постфиксного оператора ++
        ListIterator operator++(int) { 
            ListIterator temp(*this);
            ptr_ = ptr_->next_;
            return temp;
        }

        // Перегрузка постфиксного оператора --
        ListIterator operator--(int) { 
            ListIterator temp(*this);
            ptr_ = ptr_->prev_;
            return temp;
        }

        // Перегрузка префиксного оператора ++
        ListIterator& operator++() {
            ptr_ = ptr_->next_;
            return *this;
        }

        // Перегрузка префиксного оператора --
        ListIterator& operator--() {
            ptr_ = ptr_->prev_;
            return *this;
        }

        ListIterator operator+(std::size_t value) const {
            Node* tmp = ptr_;
            for (std::size_t i = 0; i < value; ++i) {
                if (tmp) tmp = tmp->next_;
                else break;
            }
            return ListIterator(tmp);
        }

        ListIterator operator-(std::size_t value) const {
            Node* tmp = ptr_;
            for (std::size_t i = 0; i < value; ++i) {
                if (tmp) tmp = tmp->prev_;
                else break;
            }
            return ListIterator(tmp);
        }

        bool operator==(const ListIterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const ListIterator& other) const { return ptr_ != other.ptr_; }

    private:
        Node* ptr_;
        friend class List<T>;
    };

    
} // namespace s21

namespace s21 {
    template <typename T>
    class ListConstIterator : public ListIterator<T> {
    public: 
        ListConstIterator(const ListIterator<T>& other) : ListIterator<T>(other) {}

        const T& operator*() const {
            return ListIterator<T>::operator*();
        }
    };
} // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ITERATOR_LIST_ITERATOR_TPP_