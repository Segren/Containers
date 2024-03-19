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
    list<value_type>::list(std::initializer_list<value_type> const &items) :
        head_(nullptr), tail_(nullptr), end_(nullptr), size_(0){
            end_= new Node(size_);
            for (const auto& item : items){
                push_back(item);
                change_end();
            }
        }
        
    template <typename value_type>
    list<value_type>::list(const list &l){
        : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0){
            end_= new Node(size_);
            this->copy(1);
        }
    }

    template <typename value_type>
    list<value_type>::list(list &&l){
        : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0){
            swap(1);
        }
    }

    template <typename value_type>
    list<value_type>::~list(){
        clear();
        delete(end_);
    }

    template <typename value_type>
    typename list<value_type>::list& list<value_type>operator=(list &&l){
        if (this != &l){
            clear();
            swap(1);
        }
        return *this;
    }

    template <typename value_type>
    bool list<value_type>::empty() {
        return size_==0;     
    }

    template <typename value_type>
    typename list<value_type>::size_type list<value_type>::size(){
        return size_;
    }

    template <typename value_type>
    typename list<value_type>::size_type list<value_type>::max_size(){
        return (std::numeric_limits<size_type>::max()/sizeof(Node)/2);
    }

    // List Element access
    template <typename value_type>
    typename list <value_type>::const_reference list<value_type>::front(){
        return !head_ ? end_->value_ : head_->value_;
    } 

    template <typename value_type>
    typename list <value_type>::const_reference list<value_type>::back(){
        return !tail_ ? end_->value_ : tail_->value_;
    }

    // ITERATORS
    template <typename value_type>
    typename list <value_type>::iterator list<value_type>::begin(){
        return !head_ ? iterator(end_) : iterator(head_);
    }

    template <typename value_type>
    typename list<value_type>::iterator list<value_type>::end(){
        return iterator(end_);
    }

    template <typename value_type>
    typename list <value_type>::const_iterator list<value_type>::begin(){
        return !head_ ? iterator(end_) : iterator(head_);
    }

    template <typename value_type>
    typename list<value_type>::const_iterator list <value_type>::end(){
        return const_iterator(end_);
    }


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