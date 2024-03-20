#ifndef CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MULTISET_S21_MULTISET_TPP_
#define CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MULTISET_S21_MULTISET_TPP_

#include "s21_multiset.h"

namespace s21 {

template <typename Key>
multiset<Key>::multiset(std::initializer_list<key_type> const& items) {
  for (const auto& item : items) {
    insert(item);  // Вставляем каждый элемент из списка
  }
}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(multiset&& ms) noexcept {
  if (this != &ms) {
    BinaryTree<Key, Key>::operator=(std::move(ms));
  }
  return *this;
}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(const multiset& ms) {
  if (this != &ms) {
    BinaryTree<Key, Key>::operator=(ms);
  }
  return *this;
}

// template <typename Key>
// multiset<Key> &multiset<Key>::operator=(multiset &&ms) noexcept {
//   if (this != &ms) {
//     // Очищаем текущее мультимножество
//     clear();
//
//     // Перемещаем ресурсы из ms в текущее мультимножество
//     this->root_ = ms.root_;
//     this->size_ = ms.size_;
//
//     // Сбрасываем ms, чтобы он больше не владел ресурсами
//     ms.root_ = nullptr;
//     ms.size_ = 0;
//   }
//   return *this;
// }
//
// template <typename Key>
// multiset<Key> &multiset<Key>::operator=(const multiset &ms) {
//   if (this != &ms) {
//     // Очищаем текущее мультимножество
//     clear();
//
//     // Копируем ресурсы из ms в текущее мультимножество
//     if (ms.root_ != nullptr) {
//       this->root_ = new TreeNode(ms.root_->key_, ms.root_->value_);
//       copy_helper(this->root_, ms.root_);
//     }
//     this->size_ = ms.size_;
//   }
//   return *this;
// }
//
//// Вспомогательная функция для рекурсивного копирования узлов
// template <typename Key>
// void multiset<Key>::copy_helper(typename BinaryTree<Key, Key>::TreeNode*
// dest, typename BinaryTree<Key, Key>::TreeNode* src) {
//   if (src->left_ != nullptr) {
//     dest->left_ = new TreeNode(src->left_->key_, src->left_->value_);
//     copy_helper(dest->left_, src->left_);
//   }
//   if (src->right_ != nullptr) {
//     dest->right_ = new TreeNode(src->right_->key_, src->right_->value_);
//     copy_helper(dest->right_, src->right_);
//   }
// }

template <typename Key>
typename BinaryTree<Key, Key>::SetIterator multiset<Key>::begin() {
  return
      typename BinaryTree<Key, Key>::SetIterator(this->GetMinNode(this->root_));
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::end() {
  if (this->root_ == nullptr) return begin();

  auto* last_node = this->GetMaxNode(this->root_);
  iterator last(nullptr, last_node);
  return last;
}

template <typename Key>
void multiset<Key>::merge(multiset<Key>& other) {
  if (&other == this) {
    // Нельзя объединять мультимножество с самим собой
    return;
  }
  // Обходим другое мультимножество и вставляем его элементы в текущее
  // мультимножество
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(*it);
  }
  // Очищаем другое мультимножество после объединения
  other.clear();
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::count(const key_type& key) {
  // Инициализируем счетчик количества вхождений ключа
  size_type count = 0;

  // Рекурсивно просматриваем дерево и считаем вхождения ключа
  count_helper(this->root_, key, count);

  return count;
}

// Вспомогательная функция для рекурсивного подсчета вхождений ключа
template <typename Key>
void multiset<Key>::count_helper(typename BinaryTree<Key, Key>::TreeNode* node,
                                 const Key& key, size_type& count) {
  if (node == nullptr) {
    return;
  }

  if (node->key_ == key) {
    ++count;  // Увеличиваем счетчик при обнаружении вхождения ключа
  }

  // Рекурсивно обходим левое и правое поддеревья
  count_helper(node->left_, key, count);
  count_helper(node->right_, key, count);
}

template <typename Key>
template <class... Args>
std::vector<std::pair<typename multiset<Key>::iterator, bool>>
multiset<Key>::insert_many(Args&&... args) {
  std::vector<std::pair<iterator, bool>> results;
  (results.push_back(insert(std::forward<Args>(args))), ...);
  return results;
}

template <typename Key>
std::pair<typename BinaryTree<Key, Key>::SetIterator, bool>
multiset<Key>::insert(const Key& key) {
  // Поиск места для вставки нового элемента
  typename BinaryTree<Key, Key>::TreeNode* current = this->root_;
  typename BinaryTree<Key, Key>::TreeNode* parent = nullptr;
  while (current != nullptr) {
    parent = current;
    if (key <= current->key_) {
      current = current->left_;
    } else {
      current = current->right_;
    }
  }

  // Создание нового узла и вставка его на место
  typename BinaryTree<Key, Key>::TreeNode* new_node =
      new typename BinaryTree<Key, Key>::TreeNode(key, key);
  if (parent == nullptr) {
    this->root_ = new_node;  // Дерево пустое, новый узел становится корнем
  } else if (key <= parent->key_) {
    parent->left_ = new_node;
  } else {
    parent->right_ = new_node;
  }

  // Увеличение размера мультимножества
  ++(this->size_);

  // Возвращение итератора на вставленный элемент и флага успешной вставки
  return std::make_pair(iterator(new_node), true);
}

template <typename Key>
void multiset<Key>::erase(iterator pos) {
  if (pos.curr_node_ == nullptr) {
    // Если позиция равна end(), ничего не делаем
    return;
  }

  // Удаление всех вхождений указанного ключа из мультимножества
  Key key = *pos;  // Ключ элемента, который нужно удалить
  erase_helper(this->root_, key);

  // Уменьшение размера мультимножества
  --(this->size_);
}

// Вспомогательная функция для рекурсивного удаления всех вхождений указанного
// ключа
template <typename Key>
typename BinaryTree<Key, Key>::TreeNode* multiset<Key>::erase_helper(
    typename BinaryTree<Key, Key>::TreeNode* node, const Key& key) {
  if (node == nullptr) {
    return nullptr;
  }

  if (key < node->key_) {
    node->left_ = erase_helper(node->left_, key);
  } else if (key > node->key_) {
    node->right_ = erase_helper(node->right_, key);
  } else {
    // Удаление текущего узла
    if (node->left_ == nullptr && node->right_ == nullptr) {
      delete node;
      return nullptr;
    } else if (node->left_ == nullptr) {
      typename BinaryTree<Key, Key>::TreeNode* temp = node->right_;
      delete node;
      return temp;
    } else if (node->right_ == nullptr) {
      typename BinaryTree<Key, Key>::TreeNode* temp = node->left_;
      delete node;
      return temp;
    } else {
      // Узел имеет двух детей
      typename BinaryTree<Key, Key>::TreeNode* min_right =
          this->GetMinNode(node->right_);
      node->key_ = min_right->key_;
      node->right_ = erase_helper(node->right_, min_right->key_);
    }
  }
  return node;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key& key) {
  typename BinaryTree<Key, Key>::TreeNode* current = this->root_;
  typename multiset<Key>::iterator result(nullptr);

  while (current != nullptr) {
    if (current->key_ >= key) {
      result = iterator(current);
      current = current->left_;
    } else {
      current = current->right_;
    }
  }
  return result;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key& key) {
  typename BinaryTree<Key, Key>::TreeNode* current = this->root_;
  typename multiset<Key>::iterator result(nullptr);

  while (current != nullptr) {
    if (current->key_ > key) {
      result = iterator(current);
      current = current->left_;
    } else {
      current = current->right_;
    }
  }
  return result;
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key& key) {
  // Находим lower_bound и upper_bound для ключа
  typename multiset<Key>::iterator lower = lower_bound(key);
  typename multiset<Key>::iterator upper = upper_bound(key);

  return std::make_pair(lower, upper);
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_SRC_CONTAINERS_MULTISET_S21_MULTISET_TPP_
