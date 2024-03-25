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
    list<value_type>::list(const list &l)
        : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0){
            end_= new Node(size_);
            this->copy(l);
        }
    }

    template <typename value_type>
    list<value_type>::list(list &&l)
        : head_(nullptr), tail_(nullptr), end_(nullptr), size_(0){
            swap(l);
        }
    

    template <typename value_type>
    list<value_type>::~list(){
        clear();
        delete(end_);
    }

    template <typename value_type>
    typename list<value_type>::list& list<value_type>::operator=(list &&l){
        if (this != &l){
            clear();
            swap(l);
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
    void list<value_type>::clear(){
        while(!empty()){
            pop_back();
        }
    }

    template <typename value_type>
    typename list<value_type>::iterator list<value_type>::insert(
        iterator pos, const_reference value){
            Node* current = pos.ptr_;
            Node* add = new Node(value);

            if (empty()){
                add->next_=end_;
                add->prev=end_;
                head_ = add;
                tail_ = add;
            } else {
                if (current == head_){
                    head_ = add;
                } else if (current == end_) {
                    tail_ = add;
                }
                
                add->next_=current;
                add->prev=current->prev_;
                current->prev_->next_ = add;
                current->prev_ = add;
            }
            size++;
            change_end();
            return iterator(add);s
    }

    template <typename value_type>
    void list<value_type>::erase(iterator pos){
        Node* current = pos.prt_;
        if (!empty() && current!=end_){
            if (current==head_){
                if (current->next_ && current->next_ != end_){
                    head_ = current->next_;
                } else {
                    head_ = end_;
                }
            } else if (current==tail_) {
                if (current->prev_ && current->prev_!= end_) {
                    tail_ = current->prev_;
                } else {
                    tail_ = end_;
                }
            }
            current->prev_->next_=current->next_;
            current->next_->prev_=current->prev_;
            delete current;
            this->size_--;
        } else {
            throw std::invalid_argument("Invalid argument");
        }
        change_end();
    }


    template <typename value_type>
    void list<value_type>::push_back(const_reference value) {
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
    void list<value_type>::pop_back() {
        if (empty()){
            throw std::out_of_range("list is empty");
        } 
        Node* last_node = tail_;
        if (size_ == 1){
            head_ = nullptr;
            tail_ = nullptr;
        } else {
            tail_ = last_node->prev_;
            tail_->next_ = nullptr;
        }
        delete last_node;
        size_--;
        change_end();
    }

    template <typename value_type>
    void list<value_type>::push_front(const_reference value){
        Node* new_node = new Node(value);
        if (empty()){
            head_ = new_node;
            tail_ = new_node;
        } else {
            new_node->prev_ = head_;
            head_->prev_ = new_node;
            head_ = new_node;
        }
        size++;
        change_end();
    }

    template <typename value_type>
    void list<value_type>::pop_front(){
        if (empty()){
            throw std::out_of_range("list is empty");
        } 
        Node* first_node = head_;
        if (size_ == 1){
            head_ = nullptr;
            tail_ = nullptr;
        } else {
            head_ = first_node->next_;
            head_->prev_ = nullptr;
        }
        delete first_node;
        size_--;
        change_end();
    }

    template <typename value_type>
    void list<value_type>::swap(list& other){
        using std::swap;
        swap(this->head_, other.head_);
        swap(this->tail_, other.tail_);
        swap(this->size_, other.size_);
        swap(this->end_, other.end_);
    }

    template <typename value_type>
    void list<value_type>::merge(list& other){
        if (!this->empty() && !other.empty()) {
            iterator iter_this = this->begin();
            iterator iter_other = other.begin();
            wheli (iter_this != this->end()) {

            }
        }
    }


    template <typename value_type>
    void list<value_type>::splice(const_iterator pos, list& other){
        if (!other.empty()){
            for (iteraror i=other.begin(); i != other.end(); i++){
                this->insert(pos, i);
            }
            other.clear();
        }
    }


    template <typename value_type>
    void list<value_type>::reverse(){
        if (!this->empty()){
            size_type step = 0;
            for (iterator i = this-> begin(); step <= this->size(); i++){
                step++;
                std::swap(i.ptr_->prev_, i.ptr_->next_);
            }
            std::swap(head_, tail_);
        }
    }


    template <typename value_type>
    void list<value_type>::unique(){
        if (!this->empty()){
            for (iterator i = this->begin(); i != this->end(); i++){
                if (i.ptr_->value_ == i.ptr_->prev_->value_){
                    iterator del_it = (i-1);
                    this -> erase(del_it)
                }
            }
        }
    }



    template <typename value_type>
    void list<value_type>::sort(){
        if (size_>1){
            quick_sort(begin(), --end())
        }
    }



    template <typename value_type>
    list<value_type>::change_end() {
        if (end_){

        }
    }
} // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_LIST_S21_LIST_TPP_