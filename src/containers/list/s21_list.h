#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_LIST_S21_LIST_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_LIST_S21_LIST_H_

#include <algorithm>        // Для std::copy
#include <cstddef>          // Для size_t
#include <initializer_list> // Для std::initializer_list
#include <stdexcept>        // Для std::out_of_range
#include <iostream>


#include "../iterator/list_iterator.h"

namespace s21 {
    template <typename T>
    class list {
        public: 
        //List Member type
            using value_type = T;
            using reference = T&; 
            using const_reference = const T&; 
            using size_type = std::size_t;

            private:
            struct Node_{
                value_type value_;
                Node_* prev_;
                Node_* next_;

                Node_(const value_type& value)
                    : value_(value), prev_(nullptr), next_(nullptr) {}
            };

            Node* head_; // указатель на первый элемент
            Node* tail_; // указатель на последний элемент
            Node* end_; // специальный узел, который используется для обеспечения цикличности списка
            size_type sise_; // размер списка


        public: 
            // CONSTRUCTORS
            list();
            list(size_type n);
            list(std::initializer_list<value_type> const &items);
            list(const list &l);
            list(list &&l);
            ~list();
            list& operator=(list &&l);

            // List Element access
            const_reference front(); // access the first element
            const_reference back(); //access the last element

            // List Capacity 
            bool empty();
            size_type size();
            size_type max_size();

            // List Modifiers
            void clear(); // +
            iterator insert(iterator pos, const_reference value); // +
            void erase(iterator pos); // +
            void push_back(const_reference value); // +
            void pop_back(); // +
            void push_front(const_reference value); // +
            void pop_front(); // + 
            void swap(list& other); // + 
            void merge(list& other); // не сделал 
            void splice(const_iterator pos, list& other); // +
            void reverse(); // +
            void unique(); // +
            void sort(); // +

            //  List Member type
            using iterator = ListIterator<T>;
            using const_iterator = ListConstIterator<T>;

            // ITERATORS
            iterator begin();
            iterator end();
            const_iterator begin();
            const_iterator end();

        private:
            // Support
            void change_end();
            void quick_sort(iterator left, iterator right);
            iterator split(iterator first, iterator last);
            void copy(const list& l);
            void print_list();
    }

} // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_LIST_S21_LIST_H_
