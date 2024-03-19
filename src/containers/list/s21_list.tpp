#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_LIST_S21_LIST_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_LIST_S21_LIST_TPP_

#include "s21_list.h"

namespace s21 {
    // CONSTRUCTORS
    template <typename value_type> //объявление шаблона класса
    list<value_type>::list()
        : head_(nullptr), tail_(nullptr), end_(nullptr), size(0) {
            end_= new Node(size_);
    }

    template <typename value_type>
    list<value_type>::list(size_type n)
        : head_(nullptr), tail_(nullptr), end_(nullptr), size(n) {
            if (n>max_size()){
                throw std::out_of_range ("Limit of container is exceeded");
            } 
        end_= new Node(size_);

        for (size_type i=0;i<n;i++){
            push_back(value_type());
        }
        change_end();
    }

    template <typename value_type>
    bool list<value_type>::empty() {
        return size_==0;     
    }

    template <typename value_type>
    size_type list<value_type>::size(){
        
    }

    template <typename value_type>
    list<value_type>::size_type max_size(){}


    template <typename value_type>
    list<value_type>::push_back(const_reference value) {
        Node* new_node = new Node(value);
        if (empty()){
            head_ = new_node;
            tail_ = new_node;
        } else {
            new_node->prev_ = tail_;
            tail_->next_ = new_node;
            tail_ = new_node;
        }
        size++;
        change_end();
    }

    template <typename value_type>
    list<value_type>::change_end() {
        if (end_){

        }
    }




    
} // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_LIST_S21_LIST_TPP_