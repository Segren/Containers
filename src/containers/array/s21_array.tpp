#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ARRAY_S21_ARRAY_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ARRAY_S21_ARRAY_TPP_

#include "s21_array.h"


namespace s21 {
template <typename T, std::size_t amount>
array<T, amount>::array() {
    amount_ = amount;
    if (amount_ == 0) {
        array_ = nullptr; // Защита от выделения памяти под нулевой аррей
    } else {
        array_ = new value_type[amount_];
        for (int i = 0; i < amount_; i++) { // Заполнение нулями
            array_[i] = 0;
        }
    }
}



}  // namespace s21
#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_ARRAY_S21_ARRAY_TPP_