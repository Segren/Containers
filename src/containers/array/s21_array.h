#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ARRAY_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ARRAY_S21_ARRAY_H_

#include <iostream>

namespace s21 {
    template<typename T, std::size_t amount>
    class array {
    public:
        using key_type = T;
        using value_type = T;
        using reference = value_type &;
        using const_reference = const value_type &;
        using iterator = T *;
        using const_iterator = const T *;;
        using size_type = size_t;

        array();

        array(std::initializer_list<value_type> const &items);

        array(const array &a);

        array(array &&a) noexcept;

        ~array();
//            array &operator=(array &&a) noexcept;
//            array &operator=(array &a);
//
//            reference at(size_type pos);
//            reference operator[](size_type pos);
//            const_reference front();
//            const_reference back();
//            iterator data();
//
//            iterator begin();
//            iterator end();
//
//            bool empty();
//            size_type size();
//            size_type max_size();
//
//            void swap(array& other);
//            void fill(const_reference value);



    private:
        size_type amount_;
        value_type* array_;

    };

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ARRAY_S21_ARRAY_H_
